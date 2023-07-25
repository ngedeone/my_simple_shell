#include "shell.h"

/**
 * main - Entry point for the shell program
 * @ac: Number of command-line arguments (unused)
 * @av: Array of command-line arguments (unused)
 *
 * Return: Always EXIT_SUCCESS
 */
int main(int ac __attribute__((unused)), char **av __attribute__((unused)))
{
<<<<<<< HEAD
char *line = NULL;      /* Pointer to store user input line */
size_t bufsize = 0;     /* Size of the buffer for getline */
info_t info = INFO_INIT; /* Structure to hold shell information */
int int_mode = 1;       /* Flag to check if running interactively */

while (int_mode)
{
int_mode = isatty(STDIN_FILENO);
if (int_mode == 1)
{
writePrompt(); /* Display the shell prompt */
}

/* Read the input command line from the user */
if (my_getline(&line, &bufsize, stdin) == -1)
{
if (int_mode)
putchar('\n');
break; /* Exit the loop on end-of-file (EOF) */
}

/* Remove the newline character from the input */
line[strcspn(line, "\n")] = '\0';

/* Execute the command */
execute_command(&info, line);

/* Free allocated memory for the line */
free(line);
line = NULL;
}

return (EXIT_SUCCESS);

    char *line = NULL;      /* Pointer to store user input line */
    size_t bufsize = 0;     /* Size of the buffer for getline */
    info_t info = INFO_INIT; /* Structure to hold shell information */
    int int_mode = 1;       /* Flag to check if running interactively */

    while (int_mode)
    {
        int_mode = isatty(STDIN_FILENO);
        if (int_mode == 1)
        {
            writePrompt(); /* Display the shell prompt */
        }

        /* Read the input command line from the user */
        if (my_getline(&line, &bufsize, stdin) == -1)
        {
            if (int_mode)
                putchar('\n');
            break; /* Exit the loop on end-of-file (EOF) */
        }

        /* Remove the newline character from the input */
        line[strcspn(line, "\n")] = '\0';

        /* Execute the command */
        execute_command(&info);

        /* Free allocated memory for the line */
        free(line);
        line = NULL;
    }

    return EXIT_SUCCESS;
}
