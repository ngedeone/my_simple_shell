#include "shell.h"

void execute_command(info_t *info, char *line)
{
    pid_t child_pid;
    int status;
    char *path = NULL;
    char **args = NULL;

    if (!line)
        return;

    /* Find the executable path using PATH */
    /* Implement the function to search for the executable path */
    path = find_path(line, info->env);

    if (path)
    {
        /* Tokenize the command line to separate the command and arguments */
        /* Implement the function to tokenize the command line */
        args = strtow(line, " \t\n");

        if (args)
        {
            child_pid = fork();

            if (child_pid == -1)
            {
                /* Handle fork error */
                perror("fork");
            }
            else if (child_pid == 0)
            {
                /* Child process */
                execve(path, args, info->env);
                perror("execve");

                /* Free memory in the child process before exiting */
                free(path);
                ffree(args);

                exit(EXIT_FAILURE);
            }
            else
            {
                /* Parent process */
                wait(&status);

                /* Free memory after execution */
                free(path);
                ffree(args);
            }
        }
        else
        {
            /* Handle memory allocation error */
            perror("strtow");
        }
    }
    else
    {
        /* Command not found */
        _puts("Command not found\n");
    }
}

