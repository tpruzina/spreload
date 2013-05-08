/******************************************************************************
 *
 * Spreload header file
 *
 * This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 * WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 *
 ******************************************************************************/

#ifndef __SPRELOAD_H__
#define __SPRELOAD_H__

int preload_file(char* path);
int preload_dir(char *dir);
int parse_stdin();
void fatal_error(char const * emsg);

#endif /* __SPRELOAD_H__ */



