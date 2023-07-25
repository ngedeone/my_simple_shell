#include "shell.h"

/**
 * _puts - Print a string to the standard output.
 * @str: The input string to be printed.
 */
void _puts(char *str)
{
    write(STDOUT_FILENO, str, _strlen(str));
}

/**
 * _putchar - Print a single character to the standard output.
 * @c: The character to be printed.
 *
 * Return: On success, return the number of characters written, otherwise -1.
 */
int _putchar(char c)
{
    return write(STDOUT_FILENO, &c, 1);
}

/**
 * _strcat - Concatenate two strings.
 * @dest: The destination buffer to store the concatenated string.
 * @src: The source string to be concatenated to the destination.
 *
 * Return: Pointer to the destination buffer (dest).
 */
char *_strcat(char *dest, const char *src)
{
    size_t dest_len = _strlen(dest);
    size_t i;

    for (i = 0; src[i] != '\0'; i++)
        dest[dest_len + i] = src[i];

    dest[dest_len + i] = '\0';
    return dest;
}

/**
 * ffree - Free the memory allocated for an array of strings.
 * @arr: The array of strings to free.
 */
void ffree(char **arr)
{
	int i;

	if (arr == NULL)
		return;

	for (i = 0; arr[i] != NULL; i++)
	{
		free(arr[i]);
	}

	free(arr);
}

