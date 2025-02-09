#ifndef FIND_FILES_H
#define FIND_FILES_H

#define _XOPEN_SOURCE 1          /* Required under GLIBC for nftw() */
#define _XOPEN_SOURCE_EXTENDED 1 /* Same */

#include <dirent.h>
#include <errno.h>
#include <ftw.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define SPARE_FDS 5

int file_info(const char *, const struct stat *, int flag, struct FTW *);

int init_nftw(int argc, char *argv[]);

#endif /* FIND_FILES_H */
/* EOF */
