#include "shell.h"

/**
 * execute_command - Execute the command entered by the user
 * @info: Pointer to the info_t structure
 * @line: The command line entered by the user
 *
 * This function executes the command by forking a child process and calling
 * the appropriate functions to execute the command in the child and parent processes.
 */
void execute_command(info_t *info, char *line)
{
	char *path = NULL;
	char **args = NULL;

	if (!line)
		return;

	/* Find the executable path using PATH */
	path = find_path(line, info->env);

	if (path)
	{
		/* Tokenize the command line to separate the command and arguments */
		args = strtow(line, " \t\n");

		if (args)
		{
			pid_t child_pid = fork();

			if (child_pid == -1)
			{
				/* Handle fork error */
				perror("fork");
			}
			else if (child_pid == 0)
			{
				/* Child process */
				execute_child(info, path, args);
			}
			else
			{
				/* Parent process */
				execute_parent(path, args);
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

	/* Wait for the child process to finish*/
	pid = wait(&status);

	if (pid == -1)
	{
		perror("wait");
	}
	else
	{
		/* Check if args is not NULL before freeing */
		if (args)
			ffree(args);

		/* Free memory after execution */
		free(path);
	}
}

/**
 * execute_child - Execute the command in the child process
 * @info: Pointer to the info_t structure
 * @path: The executable path of the command
 * @args: The arguments passed to the command
 *
 * This function is called by the child process to execute the command using execve.
 */
void execute_child(info_t *info, char *path, char **args)
{
	execve(path, args, info->env);
	perror("execve");

	/* Free memory and exit the child process with failure code */
	free(path);
	ffree(args);
	exit(EXIT_FAILURE);
}

