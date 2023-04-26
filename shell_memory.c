#include "shell.h"

/**
 * free_p - frees pointer address
 * @temp: parameter
 * Return: Returns 1 on success or 0 on failure
 */

int free_p(void **temp)
{
	if (temp && *temp)
	{
		free(*temp);
		*temp = NULL;
		return (1);
	}

	return (0);
}
