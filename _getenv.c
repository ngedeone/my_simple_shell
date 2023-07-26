#include "shell.h"

/**
 * _getenv - Get the value of a specific environment variable
 * @env: The environment variables array
 * @name: The name of the environment variable to find
 *
 * Return: Pointer to the value of the environment variable, or NULL if not found
 */
char *_getenv(list_t *env, const char *name)
{
    size_t name_len = _strlen(name);
    list_t *current = env;

    while (current != NULL)
    {
        if (_strncmp(current->str, name, name_len) == 0 && current->str[name_len] == '=')
            return &(current->str[name_len + 1]);

        current = current->next;
    }

    return NULL;
}

/**
 * writePrompt - Display the shell prompt
 */
void writePrompt(void)
{
	char prompt[] = "$ "; /* Shell prompt: "$ " */
	write(STDOUT_FILENO, prompt, sizeof(prompt) - 1);
}

/**
 * free_list - Frees a linked list.
 * @list: Pointer to the head of the list.
 */
void free_list(list_t *list)
{
    list_t *temp;

    while (list)
    {
        temp = list;
        list = list->next;
        free(temp->str);
        free(temp);
    }

}

/**
 * add_node_end - Add a new node at the end of the list.
 * @head: Pointer to the pointer of the head node.
 * @str: String to be stored in the new node.
 *
 * Return: Address of the new node, or NULL on failure.
 */
list_t *add_node_end(list_t **head, char *str)
{
	list_t *temp;
	list_t *new_node;

    if (!head || !str)
        return NULL;

    new_node = malloc(sizeof(list_t));
    if (!new_node)
        return NULL;

    new_node->str = strdup(str);
    if (!new_node->str)
    {
        free(new_node);
        return NULL;
    }

    new_node->next = NULL;

    if (*head == NULL)
    {
        *head = new_node;
    }
    else
    {
        temp = *head;
        while (temp->next != NULL)
        {
            temp = temp->next;
        }
        temp->next = new_node;
    }

    return new_node;
}

/**
 * free_str_array - Frees an array of strings.
 * @array: Pointer to the array of strings.
 *
 * Description: This function frees each string in the array and then frees the
 * array itself.
 */
void free_str_array(char **array)
{
	size_t i;

    if (array == NULL)
        return;

    for (i = 0; array[i] != NULL; i++)
    {
        free(array[i]);
        array[i] = NULL;
    }

    free(array);
}

