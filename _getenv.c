#include "shell.h"

/**
 * _getenv - Get the value of a specific environment variable
 * @env: The environment variables array
 * @name: The name of the environment variable to find
 *
 * Return: Pointer to the value of the environment variable, or NULL if not found
 */
char *_getenv(list_t *env, const char *name)
{
    size_t name_len = _strlen(name);
    list_t *current = env;

    while (current != NULL)
    {
        if (_strncmp(current->str, name, name_len) == 0 && current->str[name_len] == '=')
            return &(current->str[name_len + 1]);

        current = current->next;
    }

    return NULL;
}

/**
 * writePrompt - Display the shell prompt
 */
void writePrompt(void)
{
	char prompt[] = "$ "; /* Shell prompt: "$ " */
	write(STDOUT_FILENO, prompt, sizeof(prompt) - 1);
}

