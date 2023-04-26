#include "shell.h"

/**
 * _myhistory -function displays history list one command per line,preceded
 *              by line numbers starting at 0.
 * @info: The argument structure is used to store,manage potential arguments.
 *        Constant function prototype maintains immutability.
 *
 * Return: Always 0.
 */
int _myhistory(info_t *info)
{
	str_print_list(info->history);
	return (0);
}

/**
 * unset_alias - The function removes an alias from the list.
 * @info: parameter struct
 * @str: string alias
 *
 * Return: success (0), error (1)
 */
int unset_alias(info_t *info, char *str)
{
	char *eq_pos;
	int ret;

	eq_pos = _strchr(str, '=');

	if (!eq_pos)
	{
		return (1);
	}

	*eq_pos = '\0';

	ret = delete_at_index(&info->alias,
				    node_index(info->alias,
						   nodestrts_with(info->alias,
								    str, -1)));


	*eq_pos = '=';

	return (ret);
}

/**
 * set_alias - The function assigns an alias to a string.
 * @info: parameter struct
 * @str: alias of the string
 *
 * Return: success (1), error (1)
 */
int set_alias(info_t *info, char *str)
{
	char *value_start = _strchr(str, '=');
	char *alias_name, *alias_value;
	int ret;

	if (!value_start)
		return (1);


	*value_start = '\0';
	alias_name = str;
	alias_value = value_start + 1;

	if (!*alias_value)
		return (unset_alias(info, alias_name));

	unset_alias(info, alias_name);

	ret = add_node_end(&(info->alias), str, 0) == NULL;

	*value_start = '=';
	return (ret);
}

/**
 * print_alias - The function displays an alias string
 * @node: the alias node
 *
 * Return: success (0), error (1)
 */
int print_alias(list_t *node)
{
	char *alias, *value, *equal_sign;

	if (!node)
		return (1);

	alias = node->str;
	equal_sign = _strchr(alias, '=');
	if (!equal_sign)
		return (1);

	value = equal_sign + 1;

	_putchar('\'');
	for (; alias < equal_sign; alias++)
		_putchar(*alias);
	_putchar('\'');

	_puts(value);
	_putchar('\n');

	return (0);
}

/**
 * _myalias - Function mimics alias built-in command (man alias).
 * @info: The argument structure stores and manages potential arguments and is
 *        used to maintain a constant function prototype.
 * Return: Always 0
 */
int _myalias(info_t *info)
{
	int i;
	char *p;
	list_t *node;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}

	for (i = 1; i < info->argc; i++)
	{
		p = _strchr(info->argv[i], '=');
		if (p)
			set_alias(info, info->argv[i]);
		else
		{
			node = nodestrts_with(info->alias, info->argv[i], '=');
			if (node)
				print_alias(node);
		}
	}

	return (0);
}
