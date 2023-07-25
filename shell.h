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

#define INFO_INIT {NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, 0, 0, 0}

/**
 * struct liststr - singli linked list
 * @num: the nmber field
 * @str: a string
 * @next: points to the next node
 */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;

/**
 * struct passinfo - contains pseudo-arguements to pass into a function,
 * allowing uniform prototype for function pointer struct
 * @arg: a string generated from getline containing arguements
 * @argv:an array of strings generated from arg
 * @path: a string path for the current command
 * @argc: the argument count
 * @line_count: the error count
 * @err_num: the error code for exit()s
 * @linecount_flag: if on count this line of input
 * @fname: the program filename
 * @env: linked list local copy of environ
 * @environ: custom modified copy of environ from LL env
 * @history: the history node
 * @alias: the alias node
 * @env_changed: on if environ was changed
 * @status: the return status of the last exec'd command
 * @cmd_buf: address of pointer to cmd_buf, on if chaining
 * @cmd_buf_type: CMD_type ||, &&, ;
 * @readfd: the fd from which to read line input
 * @histcount: the history line number count
 */
typedef struct passinfo
{
    char *arg;
    char **argv;
    char *path;
    int argc;
    unsigned int line_count;
    int err_num;
    int linecount_flag;
    char *fname;
    list_t *env;
    list_t *history;
    list_t *alias;
    char **environ;
    int env_changed;
    int status;
    char **cmd_buf;
    int cmd_buf_type;
    int readfd;
    int histcount;
} info_t;

/* loophsh.c */
void free_str_array(char **array);
ssize_t _getline(info_t *info, char **lineptr, size_t *n);

/* toem_errors.c */
void _puts(char *str);
int _putchar(char c);
char *_strcat(char *dest, const char *src);
void ffree(char **arr);

/* toem_execute.c */
void execute_command(info_t *info);
void execute_parent(char *path, char **args);
void execute_child(char *path, char **args, char **env);

/* toem_env_builtin.c */
int _env(info_t *info);

/* toem_exit_builtin.c */
void _exit_builtin(info_t *info);

/* toem_utils.c */
list_t *array_to_list(const char **array);
size_t _strlen(const char *str);
char *_strdup(const char *src);
void free_info(info_t *info);
int _strncmp(const char *s1, const char *s2, size_t n);

/* my_getline.c */
void allocate_initial_buffer(char **lineptr, size_t *n);
void reallocate_buffer(char **lineptr, size_t *n);
ssize_t read_line(char **lineptr, size_t *n, FILE *stream);
ssize_t my_getline(char **lineptr, size_t *n, FILE *stream);

/* find_path */
char *find_path(char *cmd, list_t *env);
char *check_absolute_path(char *cmd);
char *search_executable_in_path(char *cmd, list_t *env);

/* _getenv */
char **list_to_char_array(const list_t *list);
char *_getenv(list_t *env, const char *name);
void writePrompt(void);

/*my_strtok.c */
char **split_string(char *str, char *delim);
char **split_string_single_delim(char *str, char delim);
int is_delim(char c, char *delim);

#endif

