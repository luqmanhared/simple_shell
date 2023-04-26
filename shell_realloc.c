#include "shell.h"
/**
 * _memset - Sets aside memory
 * @str: parameter 1
 * @byt: parameter 2
 * @size: parameter 3
 * Return: A pointer to the reserved memory
 */

char *_memset(char *str, char byt, int size)
{
	int ind;

	for (ind = 0; ind < size; ind++)
	{
		str[ind] = byt;
	}
	return (str);
}

/**
 * free_f - main function
 * @ss: parameter of function
 */

void free_f(char **ss)
{
	char **s = ss;

	if (!ss)
		return;

	while (*ss != NULL)
		free(*ss++);
	free(s);
}

/**
 * _relloc - main function
 * @addr: parameter 1
 * @size: parameter 2
 * @size_new: parameter 3
 * Return: The address of the reallocated memory
 */

void *_relloc(void *addr, int size, int size_new)
{
	char *temp;

	if (!addr)
		return (malloc(size_new));
	if (size_new == NULL)
		return (free(addr), NULL);
	if (size_new == size)
		return (addr);

	temp = malloc(size_new);
	if (temp == NULL)
		return (NULL);

	size = size < size_new ? size : size_new;

	while (size--)
		temp[size] = ((char *)addr)[size];
	free(adr);

	return (temp);
}
