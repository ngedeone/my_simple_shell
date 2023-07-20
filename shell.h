#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <limits.h>
#include <errno.h>

/* for read/write buffers */
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
    0, 0, 0}

/**
 * struct passinfo - contains pseudo-arguments to pass into a function,
 * allowing a uniform prototype for a function pointer struct
 * @arg: a string generated from getline containing arguments
 * @env: environment variables
 */
typedef struct passinfo
{
    char *arg;
    char **env;
} info_t;

/* loophsh.c */
ssize_t _getline(info_t *info, char **lineptr, size_t *n);

/* toem_errors.c */
void _puts(char *str);
int _putchar(char c);

/* toem_execute.c */
void execute_command(info_t *info, char *line);

/* toem_env_builtin.c */
int _env(info_t *info);

/* toem_exit_builtin.c */
void _exit_builtin(info_t *info);

/* toem_utils.c */
int _strlen(char *str);
char *_strdup(const char *src);
void free_info(info_t *info, int free_env);

#endif

