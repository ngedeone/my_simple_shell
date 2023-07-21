#include "shell.h"

/**
 * _getenv - Get the value of a specific environment variable
 * @env: The environment variables array
 * @name: The name of the environment variable to find
 *
 * Return: Pointer to the value of the environment variable, or NULL if not found
 */
char *_getenv(char **env, const char *name)
{
	size_t name_len = 0;
	int i;

	if (!env || !name)
		return NULL;

	name_len = _strlen(name);

	for (i = 0; env[i] != NULL; i++)
	{
		if (_strncmp(env[i], name, name_len) == 0 && env[i][name_len] == '=')
			return &(env[i][name_len + 1]);
	}

	return NULL;
}

