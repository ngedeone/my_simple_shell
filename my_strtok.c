#include <stddef.h>
#include <stdlib.h>
#include "shell.h"

/**
* split_string - Splits a string into words using a set of delimiters.
* @str: The input string to split.
* @delim: The set of delimiters used to split the string.
*
* Return: A pointer to an array of strings (words), or NULL on failure.
*/
char **split_string(char *str, char *delim)
{
int i, j, k, m, numwords = 0;
char **s;

if (str == NULL || str[0] == '\0')
return (NULL);

if (delim == NULL || delim[0] == '\0')
delim = " \t\n"; /* Default delimiters*/

for (i = 0; str[i] != '\0'; i++)
{
if (!is_delim(str[i], delim) && (is_delim(str[i + 1], delim) || str[i + 1] == '\0'))
numwords++;
}

if (numwords == 0)
return (NULL);

s = malloc((1 + numwords) * sizeof(char *));
if (!s)
return (NULL);

for (i = 0, j = 0; j < numwords; j++)
{
while (is_delim(str[i], delim))
i++;

k = 0;
while (!is_delim(str[i + k], delim) && str[i + k] != '\0')
k++;

s[j] = malloc((k + 1) * sizeof(char));
if (!s[j])
{
for (m = 0; m < j; m++)
free(s[m]);
free(s);
return (NULL);
}

for (m = 0; m < k; m++)
s[j][m] = str[i++];

s[j][m] = '\0';
}

s[j] = NULL;
return (s);

    if (str == NULL || str[0] == '\0')
        return (NULL);

    if (delim == NULL || delim[0] == '\0')
        delim = " \t\n"; /* Default delimiters */

    for (i = 0; str[i] != '\0'; i++)
    {
        if (!is_delim(str[i], delim) && (is_delim(str[i + 1], delim) || str[i + 1] == '\0'))
            numwords++;
    }

    if (numwords == 0)
        return (NULL);

    s = malloc((1 + numwords) * sizeof(char *));
    if (!s)
        return (NULL);

    for (i = 0, j = 0; j < numwords; j++)
    {
        while (is_delim(str[i], delim))
            i++;

        k = 0;
        while (!is_delim(str[i + k], delim) && str[i + k] != '\0')
            k++;

        s[j] = malloc((k + 1) * sizeof(char));
        if (!s[j])
        {
            for (m = 0; m < j; m++)
                free(s[m]);
            free(s);
            return (NULL);
        }

        for (m = 0; m < k; m++)
            s[j][m] = str[i++];

        s[j][m] = '\0';
    }

    s[j] = NULL;
    return (s);
}

/**
* split_string_single_delim - Splits a string into words using a single delimiter.
* @str: The input string to split.
* @delim: The delimiter character used to split the string.
*
* Return: A pointer to an array of strings (words), or NULL on failure.
*/
char **split_string_single_delim(char *str, char delim)
{
int i, j, k, m, numwords = 0;
char **s;

if (str == NULL || str[0] == '\0')
return (NULL);

for (i = 0; str[i] != '\0'; i++)
{
if ((str[i] != delim && str[i + 1] == delim) ||
(str[i] != delim && str[i + 1] == '\0') || str[i + 1] == delim)
numwords++;
}

if (numwords == 0)
return (NULL);

s = malloc((1 + numwords) * sizeof(char *));
if (!s)
return (NULL);

for (i = 0, j = 0; j < numwords; j++)
{
while (str[i] == delim)
i++;

k = 0;
while (str[i + k] != delim && str[i + k] != '\0')
k++;

s[j] = malloc((k + 1) * sizeof(char));
if (!s[j])
{
for (m = 0; m < j; m++)
free(s[m]);
free(s);
return (NULL);
}

for (m = 0; m < k; m++)
s[j][m] = str[i++];

s[j][m] = '\0';
}

s[j] = NULL;
return (s);
}

/**
* is_delim - checks if character is a delimeter
* @c: the char to check
* @delim: the delimeter string
* Return: 1 if true, 0 if false
*/
int is_delim(char c, char *delim)
{
	while (*delim)
		if (*delim++ == c)
			return (1);
	return (0);
}
