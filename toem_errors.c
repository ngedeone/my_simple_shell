#include "shell.h"

void _puts(char *str)
{
    write(STDOUT_FILENO, str, _strlen(str));
}

int _putchar(char c)
{
    return write(STDOUT_FILENO, &c, 1);
}


/**
 * _strcat - Concatenate two strings
 * @dest: The destination buffer to store the concatenated string
 * @src: The source string to be concatenated to the destination
 *
 * Return: Pointer to the destination buffer (dest)
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

