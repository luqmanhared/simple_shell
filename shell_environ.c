#include "shell.h"

/**
 * get_environ - function that returns string array a copy of our environ
 * @info: Structure that contain potential arguments. 
 *         Used to maintain constant function prototype.
 *
 * Return: Return string array a copy of environment.
 */
char **get_environ(info_t *info)
{
	if (!info->environ || info->env_changed)
	{
		info->environ = convert_list_to_strings(info->env);
		info->env_changed = 0;
	}

	return (info->environ);
}

/**
 * _unsetenv - do away with environ variable
 * @info: parameter struct
 * @var: the string environment variable characterisitc
 *
 * Return: 1 on delete, 0 otherwise
 */
int _unsetenv(info_t *info, char *var)
{
	list_t *node = info->env;
	size_t k = 0;
	char *q;

	if (!node || !var)
		return (0);

	while (node)
	{
		q = start_with(node->str, var);
		if (q && *q == '=')
		{
			info->env_changed = delete_at_index(&(info->env), i);
			k = 0;
			node = info->env;
			continue;
		}
		node = node->next;
		i++;
	}
	return (info->env_changed);
}

/**
 * _setenv - modify existing one 
 *           or initialize a new environ
 * @info: Structure containing potential args
 *        Used to maintain constant function prototype.
 * @var: the string environment var property
 * @value: the string environment var value
 *
 * Return: success (0), failure (1)
 */
int _setenv(info_t *info, char *var, char *value)
{
	char *buf = NULL;
	list_t *node = NULL;
	char *q = NULL;

	if (!var || !value)
		return (1);

	buf = malloc(_strlen(var) + _strlen(value) + 2);
	if (!buf)
		return (1);

	_strcpy(buf, var);
	_strcat(buf, "=");
	_strcat(buf, value);

	node = info->env;
	while (node)
	{
		q = _strstr(node->str, var);
		if (q && q == node->str && *(q + _strlen(var)) == '=')
		{
			free(node->str);
			node->str = buf;
			return (0);
		}
		node = node->next;
	}

	add_node_end(&(info->env), buf, 0);
	free(buf);

	return (0);
}
