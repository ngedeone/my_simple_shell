#include "shell.h"

/**
 * execute_command - Function to execute the command
 * @info: The passinfo structure containing shell information
 *
 * Return: void
 */
void execute_command(info_t *info)
{
    char *path = NULL;
    char **args = NULL;
    pid_t child_pid;

    /* Check if the command is provided */
    if (!info || !info->arg)
        return;

    /* Find the executable path using PATH */
    path = find_path(info->arg, info->env);

    if (!path)
    {
        /* Command not found */
        _puts("Command not found\n");
        return;
    }

    /* Tokenize the command line to separate the command and arguments */
    args = split_string(info->arg, " \t\n");

    if (!args)
    {
        /* Handle memory allocation error */
        perror("strtow");
        free(path); /* Don't forget to free the allocated memory */
        return;
    }

    child_pid = fork();
    if (child_pid == -1)
    {
        /* Handle fork error */
        perror("fork");
        free(path);
        free_str_array(args);
        return;
    }

    if (child_pid == 0)
    {
        /* Child process */
        execute_child(path, args, info->environ);

        /* If execve fails, we should exit the child process to avoid any unwanted behavior */
        perror("execve");
        exit(EXIT_FAILURE);
    }
    else
    {
        /* Parent process */
        execute_parent(path, args);
    }

    free(path);
    free_str_array(args);
}

/**
 * execute_parent - Execute the command in the parent process
 * @path: The executable path of the command
 * @args: The arguments passed to the command
 *
 * This function is called by the parent process after the child process completes.
 * It waits for the child process to finish and frees the memory after execution.
 */
void execute_parent(char *path, char **args)
{
    int status;
    pid_t pid;

    /* Wait for the child process to finish */
    pid = wait(&status);

    if (pid == -1)
    {
        perror("wait");
    }
    else
    {
        /* Check if args is not NULL before freeing */
        if (args)
            free_str_array(args);

        /* Free memory after execution */
        free(path);
    }
}

/**
 * execute_child - Execute the command in the child process
 * @path: The executable path of the command
 * @args: The arguments passed to the command
 * @env: The environment variables passed to the command
 *
 * This function is called by the child process to execute the command using execve.
 */
void execute_child(char *path, char **args, char **env)
{
    char *const *envp = list_to_char_array(env);

    execve(path, args, envp);

    perror("execve");

    /* Free memory and exit the child process with a failure code */
    free(path);
    free(envp);
    free_str_array(args);
    exit(EXIT_FAILURE);
}

/**
 * list_to_char_array - Convert a list of strings to a char array
 * @list: The list of strings
 *
 * Return: The char array containing the strings
 */
char **list_to_char_array(const list_t *list)
{
    size_t count = 0;
    const list_t *current = list;
    while (current != NULL)
    {
        count++;
        current = current->next;
    }

    char **result = malloc((count + 1) * sizeof(char *));
    if (result == NULL)
        return NULL;

    current = list;
    for (size_t i = 0; i < count; i++)
    {
        result[i] = current->str;
        current = current->next;
    }
    result[count] = NULL;
    return result;
}

