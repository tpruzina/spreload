/******************************************************************************
 *
 * TODO: Project Title
 *
 * Author: Tomas Pruzina <pruzinat@gmail.com>
 *
 * This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 * WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 *
 ******************************************************************************/


#define _GNU_SOURCE
#include <dlfcn.h>
#define _FCNTL_H
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

#include "spreload.h"

#ifndef SPRELOAD_TMPFILE
#define SPRELOAD_TMPFILE "spreload_out"
#endif

int (*_open)(const char * pathname, int flags, ...);
int (*_open64)(const char * pathname, int flags, ...);

FILE *fd = NULL;
static void tmp_fopen(void);
void tmp_fclose(void);

// open .spreload_tmp file, else link FD to /dev/null
static void tmp_fopen(void)
{
	fd = fopen(SPRELOAD_TMPFILE,"a+");
	if(!fd)
		fd = fopen("/dev/null","w");
	atexit(tmp_fclose);
}

void tmp_fclose(void)
{
	if(fd)
		fclose(fd);
}

int open(const char * pathname, int flags, mode_t mode)
{
	char *absolute_path=NULL;
	if(unlikely(!fd))
		tmp_fopen();
	fprintf(fd,"%s\n",
		absolute_path = realpath(pathname,NULL));
	if(likely(absolute_path != NULL))
		free(absolute_path);
	_open = (int (*)(const char * pathname, int flags, ...)) dlsym(RTLD_NEXT, "open");
	return _open(pathname, flags, mode);
}

int open64(const char * pathname, int flags, mode_t mode)
{
	char *absolute_path=NULL;
	if(unlikely(!fd))
		 tmp_fopen();
	fprintf(fd,"%s\n",
		absolute_path = realpath(pathname,NULL));
	if(likely(absolute_path != NULL))
		free(absolute_path);
	_open64 = (int (*)(const char * pathname, int flags, ...)) dlsym(RTLD_NEXT, "open64");
	return _open64(pathname, flags, mode);
}

