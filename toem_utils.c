#include "shell.h"

/**
 * _strlen - Calculate the length of a string.
 * @str: The input string.
 *
 * Return: The length of the string.
 */
size_t _strlen(const char *str)
{
    size_t len = 0;
    while (str[len] != '\0')
        len++;
    return len;
}

/**
 * _strdup - Duplicate a string.
 * @src: The source string to duplicate.
 *
 * Return: A pointer to the duplicated string, or NULL on failure.
 */
char *_strdup(const char *src)
{
    size_t len = _strlen(src);
    char *dup = malloc(len + 1);
    if (dup)
        return memcpy(dup, src, len + 1);
    return NULL;
}

/**
 * free_info - Function to free the info_t structure
 * @info: Pointer to the info_t structure
 *
 * Return: void
 */
void free_info(info_t *info)
{
	char *const *env = list_to_char_array(info->env);

	if (info->arg)
		free(info->arg);

	if (free_info && info->env)
	{
		char **env = (char **)info->env;
		int i = 0;
		while (env[i])
		{
			free(env[i]);
			i++;
		}
		free(env);
	}
}

/**
 * _strncmp - Compare two strings up to n bytes.
 * @s1: The first string.
 * @s2: The second string.
 * @n: The maximum number of bytes to compare.
 *
 * Return: 0 if strings are equal, < 0 if s1 < s2, > 0 if s1 > s2.
 */
int _strncmp(const char *s1, const char *s2, size_t n)
{
    while (n--)
    {
        if (*s1 != *s2)
            return *s1 - *s2;
        if (*s1 == '\0')
            return 0;
        s1++;
        s2++;
    }
    return 0;
}

/**
 * array_to_list - Converts an array of strings to a linked list of strings.
 * @array: The array of strings to convert.
 *
 * Return: A pointer to the head of the linked list, or NULL on failure.
 */
list_t *array_to_list(const char **array)
{
        list_t *list = NULL;
	int i = 0;

        if (!array)
                return NULL;

	while (array[i] != NULL) 
		i++;
	{
		if (array_to_list(&list, strdup(array[i])) == NULL)
			return NULL;
	}
    
	return list;
}
