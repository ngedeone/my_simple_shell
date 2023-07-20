#include "shell.h"

void _puts(char *str)
{
    write(STDOUT_FILENO, str, _strlen(str));
}

int _putchar(char c)
{
    return write(STDOUT_FILENO, &c, 1);
}

