#include "shell.h"
/**
 * _myenv - current environment is printed
 * @info: pointer to struct containing potential arguments
 *
 * Return: Always returns 0
 */
int _myenv(info_t *info)
{
	list_t *env_node = info->env;

	while (env_node != NULL)
	{
		_puts(env_node->str);
		_putchar('\n');
		env_node = env_node->next;
	}
	return (0);
}

/**
 * _getenv - value of an environment variable is found
 * @info: pointer to struct containing environment variables
 * @name: environment variable name
 *
 * Return: The pointer refers to the value of an environment variable.
 * or NULL if not found
 */
char *_getenv(info_t *info, const char *name)
{
	char *value = NULL;

	if (info && name)
	{
		for (int i = 0; info->env[i]; i++)
		{
			if (_starts_with(info->env[i], name))
			{
				value = _strchr(info->env[i], '=') + 1;
				break;
			}
		}
	}

	return (value);
}

/**
 * _mysetenv -function creates new environment variable with initial value.,
 *            function changes the value of existing environment variable.
 * @info: Structure containing potential arguments
 *        It also maintain constant function prototype.
 *
 * Return: Always (0)
 */
int _mysetenv(info_t *info)
{
	if (info->argc != 3)
	{
		_eputs("Incorrect number of arguments\n");
		return (1);
	}

	if (_setenv(info, info->argv[1], info->argv[2]))
		return (0);

	return (1);
}

/**
 * _myunsetenv -The function deletes an environment variable.
 * @info: Structure stores and manages potential arguments.
 *        Also Structure maintains constant function prototype.
 *
 * Return: Always (0)
 */
int _myunsetenv(info_t *info)
{
	int i;

	if (info->argc == 1)
	{
		_eputs("Too few arguments.\n");
		return (1);
	}

	for (i = 1; i < info->argc; i++)
		_unsetenv(info, info->argv[i]);

	return (0);
}

/**
 * populate_env_list -The function fills an environment linked list with data.
 * @info: argument structure is used to store,manage potential arguments,
 *         constant function prototype is used to maintain immutability..
 *
 * Return: Always (0)
 */
int populate_env_list(info_t *info)
{
	size_t i = 0;
	char **envp = environ;

	while (envp[i])
	{
		if (add_node_end(&info->env, envp[i], 0) == NULL)
			return (1);
		i++;
	}

	return (0);
}
