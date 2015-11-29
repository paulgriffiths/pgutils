#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include "unix_wrappers.h"

pid_t wrapper_fork(const char * file, const int line)
{
    pid_t pid = fork();
    if ( pid == -1 ) {
        fprintf(stderr, "Error: couldn't fork process: "
                "%s, line %d\n    %s (%d)\n",
                __FILE__, __LINE__, strerror(errno), errno);
        exit(EXIT_FAILURE);
    }
    return pid;
}

