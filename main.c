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

#include <assert.h>

#define NUM_FILES	1
#define BUFFER_SIZE	1024

char * test = "/home/tomas/projects/lictp/test";
void *buf=NULL;
struct stat *st;


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

int main( int argc, char** argv )
{
	int ret = 0;
	buf = malloc(BUFFER_SIZE);	
	st = malloc(sizeof(struct stat));
	if(!buf || !st)
		return -1;
	load_file(test);

	return ret;
}


