#ifndef _SHELL_H_
#define _SHELL_H_

#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <limits.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

/* for read/write buffers */
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
    0, 0, 0}

/**
 * struct info - contains pseudo-arguments to pass into a function,
 * allowing a uniform prototype for a function pointer struct
 * @arg: a string generated from getline containing arguments
 * @env: environment variables
 */
typedef struct info
{
    char **arg;
    char **env;
} info_t;

/* loophsh.c */
ssize_t _getline(info_t *info, char **lineptr, size_t *n);

/* toem_errors.c */
void _puts(char *str);
int _putchar(char c);
char *_strcat(char *dest, const char *src);
void ffree(char **arr);

/* toem_execute.c */
void execute_command(info_t *info, char *line);
void execute_parent(char *path, char **args);
void execute_child(info_t *info, char *path, char **args);

/* toem_env_builtin.c */
int _env(info_t *info);

/* toem_exit_builtin.c */
void _exit_builtin(info_t *info);

/* toem_utils.c */
size_t _strlen(const char *str);
char *_strdup(const char *src);
void free_info(info_t *info, int free_env);
int _strncmp(const char *s1, const char *s2, size_t n);

/* my_getline.c */
void allocate_initial_buffer(char **lineptr, size_t *n);
void reallocate_buffer(char **lineptr, size_t *n);
ssize_t read_line(char **lineptr, size_t *n, FILE *stream);
ssize_t my_getline(char **lineptr, size_t *n, FILE *stream);

/* find_path */
char *find_path(char *cmd, char **env);
static char *check_absolute_path(char *cmd);
static char *search_executable_in_path(char *cmd, char **env);
/* _getenv */
char *_getenv(char **env, const char *name);

/*my_strtok.c */
char **split_string(char *str, char *delim);
char **split_string_single_delim(char *str, char delim);
int is_delim(char c, char *delim);

#endif

