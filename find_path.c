#include "shell.h"

/**
 * find_path - Find the executable path using PATH
 * @cmd: The command to locate in PATH
 * @env: The environment variables containing PATH
 *
 * Return: Pointer to the executable path, or NULL if not found
 */
char *find_path(char *cmd, char **env)
{
	if (!cmd || !env)
		return NULL;

	/* Check if the command is an absolute path */
	char *path = check_absolute_path(cmd);
	if (path)
		return path;

	/* Search for the command in each path directory */
	return search_executable_in_path(cmd, env);
}

/**
 * check_absolute_path - Check if the command is an absolute path
 * @cmd: The command to check
 *
 * Return: Pointer to the executable path if found, NULL otherwise
 */
static char *check_absolute_path(char *cmd)
{
	if (!cmd)
		return NULL;

	struct stat st;
	if (cmd[0] == '/' && stat(cmd, &st) == 0 && S_ISREG(st.st_mode) && access(cmd, X_OK) == 0)
		return _strdup(cmd);

	return NULL;
}

/**
 * search_executable_in_path - Search for the command in each path directory
 * @cmd: The command to search for
 * @env: The environment variables containing PATH
 *
 * Return: Pointer to the executable path if found, NULL otherwise
 */
static char *search_executable_in_path(char *cmd, char **env)
{
	char *path = _getenv(env, "PATH");
	if (!path)
		return NULL;

	char *delims = ":";
	char *token = strtok(path, delims);
	char *tmp = NULL;
	struct stat st;

	while (token)
	{
		tmp = _strcat(_strdup(token), "/");
		tmp = _strcat(tmp, cmd);

		if (stat(tmp, &st) == 0 && S_ISREG(st.st_mode) && access(tmp, X_OK) == 0)
		{
			free(path);
			return tmp;
		}

		free(tmp);
		token = strtok(NULL, delims);
	}

	free(path);
	return NULL;
}

