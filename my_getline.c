#include "shell.h"

/**
 * allocate_initial_buffer - Allocate the initial buffer for my_getline.
 * @lineptr: A pointer to a pointer that will store the address of the allocated buffer.
 * @n: A pointer to a size_t variable that will store the size of the allocated buffer.
 */
void allocate_initial_buffer(char **lineptr, size_t *n)
{
	free(*lineptr); /* Free previously allocated memory */

	if (*lineptr == NULL || *n == 0)
	{
		*n = 128;
		*lineptr = (char *)malloc(*n);
		if (*lineptr == NULL)
		{
			perror("Error: Failed to allocate memory");
			exit(EXIT_FAILURE); /* Handle memory allocation error */
		}
	}
}

/**
 * reallocate_buffer - Reallocate the buffer for my_getline when it becomes full.
 * @lineptr: A pointer to a pointer that holds the address of the current buffer.
 * @n: A pointer to a size_t variable that holds the current size of the buffer.
 */
void reallocate_buffer(char **lineptr, size_t *n)
{
	char *newLineptr;

	free(*lineptr); /* Free previously allocated memory */

	*n *= 2;
	newLineptr = (char *)realloc(*lineptr, *n);
	if (newLineptr == NULL)
	{
		perror("Error: Failed to reallocate memory");
		exit(EXIT_FAILURE); /* Handle memory reallocation error...*/
	}
	*lineptr = newLineptr;
}

/**
 * read_line - Read characters from the input stream and store them in the buffer.
 * @lineptr: A pointer to a pointer that holds the address of the buffer.
 * @n: A pointer to a size_t variable that holds the size of the buffer.
 * @stream: A pointer to a FILE structure representing the input stream.
 *
 * Return: The number of characters read (excluding the null terminator).
 */
ssize_t read_line(char **lineptr, size_t *n, FILE *stream)
{
	size_t i = 0;
	int c;

	while ((c = fgetc(stream)) != EOF)
	{
		if (i >= *n - 2) /* Perform bounds checking to prevent buffer overflow */
		{
			reallocate_buffer(lineptr, n);
		}

		(*lineptr)[i++] = (char)c;

		if (c == '\n')
		{
			break;
		}
	}

	(*lineptr)[i] = '\0';

	return ((ssize_t)i);
}

/**
 * my_getline - Read a line from a file stream and store it in a dynamically allocated buffer.
 * @lineptr: A pointer to a pointer that will store the address of the allocated buffer.
 * @n: A pointer to a size_t variable that will store the size of the allocated buffer.
 * @stream: A pointer to a FILE structure representing the input stream.
 *
 * Return: The number of characters read (excluding the null terminator) on success.
 *         -1 if any of the arguments is NULL or if there was an error during memory allocation or reallocation.
 */
ssize_t my_getline(char **lineptr, size_t *n, FILE *stream)
{
	ssize_t result;

	if (lineptr == NULL || n == NULL || stream == NULL)
	{
		errno = EINVAL; /* Invalid arguments */
		return -1;
	}

	allocate_initial_buffer(lineptr, n);

	result = read_line(lineptr, n, stream);
	if (result == 0 || result == -1)
	{
		perror("Error: Failed to read line");
	}

	return result;
}

