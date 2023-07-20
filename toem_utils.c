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

