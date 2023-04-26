#include "shell.h"

/**
 * node_add_start - Adds a node to the beginning of list
 * @temp: Pointer to the first node
 * @text: body of the node
 * @ind: Index of the node
 * Return: Address to the new list
 */

list_t *node_add_start(list_t **temp, const char *text, int ind)
{
	list_t *new_list;

	if (temp == NULL)
		return (NULL);
	new_list = malloc(sizeof(new_list));
	if (new_list == NULL)
		return (NULL);
	_memset((void *)new_list, 0, sizeof(new_list));
	new_list->num = ind;
	if (text != NULL)
	{
		new_list->str = _strdup(text);
		if (!new_list->str)
		{
			free(new_list);
			return (NULL);
		}
	}
	new_list->next = *temp;
	*temp = new_list;
	return (new_list);
}

/**
 * node_add_end - Adds a node to the end of list
 * @temp: Address of the list
 * @text: content of node
 * @ind: Index of the node
 * Return: The new list address
 */

list_t node_add_end(list_t **temp, const char *text, int ind)
{
	list_t *new_list, *holder;

	if (temp == NULL)
		return (NULL);

	holder = *temp;
	new_list = malloc(sizeof(new_list));
	if (new_list == NULL)
		return (NULL);
	_memset((void *)new_list, 0, sizeof(new_list));
	new_list->num = ind;
	if (str != NULL)
	{
		new_list->str = _strdup(text);
		if (!new_list->str)
		{
			free(new_list);
			return (NULL);
		}
	}
	if (holder != NULL)
	{
		while (holder->next)
			holder = holder->next;
		holder->next = new_list;
	}
	else
		*temp = new_list;

	return (new_list);
}

/**
 * str_list_print - Prints the str element of a list
 * @text: address of the first node
 * Return: The list size
 */

size_t str_list_print(const list_t *text)
{
	size_t ind = 0;

	while (text != NULL)
	{
		_puts(text->str ? text->str : "(nil)");
		_puts("\n");
		text = text->next;
		ind++;
	}

	return (ind);
}

/**
 * delete_at_index - Delets a node at any given index
 * @temp: Address of the list
 * @ind: Node index to delete
 * Return: 1 on success or 0 on failure
 */

int delete_at_index(list_t **temp, int ind)
{
	list_t *holder, *last_node;
	int x;

	if (*temp == NULL || temp == NULL)
		return (0);
	if (!ind)
	{
		holder = *temp;
		*temp = (*temp)->next;
		free(holder->str);
		free(holder);
		return (1);
	}
	holder = *temp;
	while (holder != NULL)
	{
		if (x == ind)
		{
			last_node->next = holder->next;
			free(holder->str);
			free(holder);
			return (1);
		}
		x++;
		last_node = holder;
		holder = holder->next;
	}
	return (0);
}

/**
 * list_free - Fress the node of lists
 * @list_ptr: Address pointing to the first node
 */

void list_free(list_t **list_ptr)
{
	list_t *temp, *next, *first;

	if (!list_ptr || !*list_ptr)
		return;
	first = *list_ptr;
	temp = first;
	while (temp)
	{
		next = temp->next;
		free(temp->str);
		free(temp);
		temp = next;
	}
	*list_ptr = NULL;
}
