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

char * test = "/home/tomas/projects/lictp/test";
struct stat *st = NULL;


void load_file(char* path)
{
	int fd = open(path, O_RDONLY|O_NOCTTY );
	if(fd == -1)
		return;
	// get file size (amongst other things)
	fstat(fd, st);
	// preload file
	readahead(fd,0, st->st_size);
	close(fd);
}

int list_dir(char *dir)
{
	DIR *d;
	struct dirent *dent;
	d = opendir(dir);
	
	if(!d)
		return -1;

	// skip ".." and "." , end on error
	if(!readdir(d) || !readdir(d))
		return -1;
	
	while((dent = readdir(d)) != NULL)
	{
		// recurse if entry is directory, preload if file
		if(dent->d_type == DT_DIR)
			list_dir(dent->d_name);
		else if(dent->d_type == DT_REG)
			load_file(dent->d_name);
	}
	closedir(d);
}

int main( int argc, char** argv )
{

	st = malloc(sizeof(struct stat));
	if(!st)
		return -1;
	
	if(argc == 1)
	{
		// read from pipe
		;
	}
	else if (argc == 2)
	{
		//parse file or directory
	}
	else
		return -1;

	list_dir(".");
	//load_file(test);
	return 0;
}

