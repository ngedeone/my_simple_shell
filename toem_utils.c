#include "shell.h"

int _strlen(char *str)
{
    int len = 0;
    while (str[len] != '\0')
        len++;
    return len;
}

char *_strdup(const char *src)
{
    int len = _strlen(src);
    char *dup = malloc(len + 1);
    if (dup)
        return memcpy(dup, src, len + 1);
    return NULL;
}

void free_info(info_t *info, int free_env)
{
    if (info->arg)
        free(info->arg);
    if (free_env && info->env)
    {
        char **env = info->env;
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
 * _strncmp - Compare two strings up to n bytes
 * @s1: The first string
 * @s2: The second string
 * @n: The maximum number of bytes to compare
 *
 * Return: 0 if strings are equal, < 0 if s1 < s2, > 0 if s1 > s2
 */
int _strncmp(const char *s1, const char *s2, size_t n)
{
    unsigned char c1, c2;

    while (n--)
    {
        c1 = (unsigned char)*s1++;
        c2 = (unsigned char)*s2++;

        if (c1 != c2)
            return (int)c1 - (int)c2;

        if (c1 == '\0')
            break;
    }

    return 0;
}

