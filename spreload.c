/******************************************************************************
 *
 * Load files into cache - simple preloader
 *
 * Author: Tomas Pruzina <pruzinat@gmail.com>
 *
 * This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 * WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 *
 ******************************************************************************/

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <dirent.h> 

#define _GNU_SOURCE

#include "spreload.h"

/*
 * Preloads file into page cache
 */
int preload_file(char* path)
{
	struct stat st;
	int fd = open(path, O_RDONLY|O_NOCTTY );
	if(fd == -1)
		return -1;
	// get file size (amongst other things)
	fstat(fd, &st);
	// preload file
	if(unlikely(readahead(fd,0, &st.st_size) == -1))
		fatal_error("readahead() failed");
	close(fd);
	return 0;
}

/*
 * Recursively scan directory and preload files
 * return -1 if *dir aint directory
 */
int preload_dir(char *dir)
{
	DIR *d;
	struct dirent *dent;
	
	// open directory, return -1 on fail (file, other cause)
	d = opendir(dir);
	if(!d)
		return -1;

	// skip ".." and "." , end on error
	if(unlikely(!readdir(d) || !readdir(d)))
		return -1;

	while((dent = readdir(d)) != NULL)
	{
		// recurse if entry is directory, preload if file
		if(dent->d_type == DT_DIR)
			preload_dir(dent->d_name);
		else if(dent->d_type == DT_REG)
			preload_file(dent->d_name);
	}

	closedir(d);
	return 0;
}

/*
 * Parse stdin, file/directory per each line
 */
int parse_stdin()
{
	char *line = NULL;
	char *ptr = NULL;
	size_t n;
	while(getline(&line, &n, stdin) != -1)
	{
		if(!line)
			return -1;

		// todo: remove this thingy, removes newline char
		for(ptr=line; *ptr != '\n' && *ptr != '\0'; ptr++)
			;
		*ptr= '\0';
		
		// interpret line as 'directory', else read file
		if(preload_dir(line) == -1)
			if(preload_file(line) == -1)
			{
				free(line);
				fatal_error("Failed to parse input\n");
			}
	}
	free(line);
	return 0;
}

void fatal_error(char const * emsg)
{
	fprintf(stderr,"%s\n",emsg);
	exit(-1);
}

int main( int argc, char** argv )
{
	if(argc == 1)
	{
		if(parse_stdin() == -1)
			fatal_error("failed to parse stdin");
	}
	else if (argc >= 2)
	{
		while(*++argv)
			if(preload_dir(*argv) == -1)
				preload_file(*argv);
	}
	else
		printf("USAGE: <%s> <FILE/DIR> ..\n",argv[0]);
	return 0;
}

