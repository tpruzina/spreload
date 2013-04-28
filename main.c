/******************************************************************************
 *
 * Load file into cache - lame preloader
 *
 * Copyright (C) 2003-2009 ascolab GmbH. All Rights Reserved.
 * Web: http://www.ascolab.com
 *
 * Author: Gerhard Gappmeier <gerhard.gappmeier@ascolab.com>
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

#include <assert.h>

struct stat *st = NULL;


int load_file(char* path)
{
	int fd = open(path, O_RDONLY|O_NOCTTY );
	if(fd == -1)
		return -1;
	// get file size (amongst other things)
	fstat(fd, st);
	// preload file
	readahead(fd,0, st->st_size);
	close(fd);
	return 0;
}

int list_dir(char *dir)
{
	DIR *d;
	struct dirent *dent;
	d = opendir(dir);
	
	if(!d)
		return -1;

	// skip ".." and "." , end on error
	readdir(d);
	readdir(d);
	
	while((dent = readdir(d)) != NULL)
	{
		// recurse if entry is directory, preload if file
		if(dent->d_type == DT_DIR)
			list_dir(dent->d_name);
		else if(dent->d_type == DT_REG)
			load_file(dent->d_name);
	}

	closedir(d);
	return 0;
}

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
		if(list_dir(line) == -1)
			if(load_file(line) == -1)
			{
				free(line);
				return -1;;
			}
	}
	free(line);
	return 0;
}


int main( int argc, char** argv )
{
	st = malloc(sizeof(struct stat));
	if(!st)
		return -1;
	
	if(argc == 1)
		return parse_stdin();
	else if (argc == 2)
	{

	}
	else
	{
		fprintf(stderr,"USAGE: <%s> <FILE/DIR>\n",argv[0]);
		return -1;
	}
	return 0;
}

