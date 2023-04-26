#include "shell.h"

/**
 * chain - function that checks if char is a chain delimeter
 * @infor: parameter 1
 * @buffer: parameter 2
 * @ptr: parameter 3
 * Return: Returns 1 if true or 0 if false
 */

int chain(info_t *infor, char *buffer, size_t *ptr)
{
	size_t pos = *ptr;

	if (buffer[pos] == '|' && buffer[pos + 1] == '|')
	{
		buffer[pos] = 0;
		pos++;
		infor->cmd_buf_type = CMD_OR;
	}
	else if (buffer[pos] == '&' && buffer[pos + 1] == '&')
	{
		buffer[pos] = 0;
		pos++;
		infor->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*ptr = pos;

	return (1);
}

/**
 * chain_checking - function that checks whether to continue chaining
 * @inform: parameter 1
 * @bff: parameter 2
 * @pt: parameter 3
 * @nd: parameter 4
 * @s: parameter 5
 * Return: Nothing
 */

void chain_checking(info_t *inform, char *bff, size_t *pt, size_t nd, size_t s)
{
	size_t pos = *pt;

	if (inform->cmd_buf_type == CMD_AND)
	{
		if (inform->status != NULL)
		{
			buffer[nd] = 0;
			pos = s;
		}
	}
	if (inform->cmd_buf_type == CMD_OR)
	{
		if (inform->status == NULL)
			bff[nd] = 0;
			pos = s;
	}
	*pt = pos;
}

/**
 * replacing_aliases - function that replaces alias
 * @inform: parameter 1
 * Return: 1 if successful or 0 if failed
 */

int replacing_aliases(info_t *inform)
{
	int ind;
	list_t *temp;
	char *ptr;

	for (ind = 0; ind < 10; ind++)
	{
		temp = nodestrts_with(inform->alias, inform->argv[0], '=');
		if (temp == NULL)
			return (0);
		free(inform->argv[0]);
		ptr = _strchr(temp->str, '=');
		if (prt == NULL)
			return (0);
		ptr = _strdup(ptr + 1);
		if (ptr == NULL)
			return (0);
		inform->argv[0] = ptr
	}
	return (1);
}

/**
 * variable_replace - function to replace variable
 * @inform: parameter of function
 * Return: 1 on success or 0 on failure
 */

int variable_replace(info_t *inform)
{
	int ind = 0;
	list_t *new_node;

	for (ind = 0; inform->argv[ind]; ind++)
	{
		if (inform->argv[ind][0] != '$' || !inform->argv[ind][1])
			continue;
		if (!_strcmp(inform->argv[ind], "$?"))
		{
			string_replacing(&(inform->argv[ind]), _strdup(_strchr(
							new_node->str, '=') + 1));
			continue;
		}
		string_replacing(&inform->argv[ind], _strdup(""));
	}
	return (0);
}

/**
 * string_replacing - function to replace strings
 * @former: parameter 1
 * @new_str: parameter 2
 * Return: 1 if successful or 0 on failure
 */

int string_replacing(char **former, char *new_str)
{
	free(*former);
	*former = new_str;
	return (1);
}
