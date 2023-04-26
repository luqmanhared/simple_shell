#include "shell.h"

/**
 * list_length - Checks the length of the list
 * @head: Address of the list
 * Return: Returns the size of the list
 */

size_t list_length(const list_t *head)
{
	size_t index;

	for (index = 0; head != NULL; index++)
	{
		head = head->next;
	}
	return (index);
}

/**
 * convert_list_to_string - converts a list to string
 * @first: Address of the first node of the list
 * Return: Returns an array of strings from list->str
 */

char **convert_list_to_string(list_t *first)
{
	list_t *temp;
	size_t len, x;
	char *text;
	char **stings;

	temp = first;
	len = list_length(first);

	if (!first || !len)
		return (NULL);
	strings = malloc(sizeof(char *) * (len + 1));
	if (strings == NULL)
		return (NULL);
	for (len = 0; temp; temp->next, len++)
	{
		text = malloc(_strlen(temp->str) + 1);
		if (text == NULL)
		{
			for (x = 0; x < len; x++)
				free(text[x]);
			free(text);
			return (NULL);
		}
		text = _strcpy(text, tem->str);
		strings[len] = text;
	}
	strings[len] = NULL;
	return (strings);
}

/**
 * list_printout - Prints out the elements of a list
 * @first: Address of the first node of the list
 * Return: Returns the size of the list
 */

size_t list_printout(const list_t *first)
{
	size_t index;

	for (index = 0; first != NULL; index++)
	{
		_puts(convert_number(first->num, 10, 0));
		_puts(':');
		_putchar(' ');
		_puts(first->str ? first->str : "(nil)");
		_puts("\n");
		first = first->next;
	}
	return (index);
}

/**
 * nodestrts_with - Searches a node that starts with a prefix
 * @head: Address of the list
 * @pref: The prefix to match
 * @text: The next string to match
 * Return: Returns the matching node or NULL is none.
 */

list_t *nodestrts_with(list_t *head, char *pref, char text)
{
	char *ptr = NULL;

	while (head)
	{
		ptr = start_with(head->str, pref);
		if (ptr && ((text == -1) || (*ptr == text)))
			return (head);
		head = head->next;
	}
	return (NULL);
}

/**
 * node_index - Gets the index of a node
 * @first: address of the list
 * @temp: Adress of the node
 * Return: Returns the node's index or -1
 */

ssize_t node_index(list_t *first, list_t *temp)
{
	size_t index = 0;

	while (first != NULL)
	{
		if (first == temp)
			return (index);
		index++;
	}
	return (-1);
}
