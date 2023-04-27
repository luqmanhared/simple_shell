#include "shell.h"

/**
 * clear_info - function initializing info_t struct
 * @info: struct address
 */
void clear_info(info_t *info)
{
	memset(info, 0, sizeof(*info));
}

/**
 * set_info - function initializing info_t struct
 * @info: struct address
 * @av: argument vector
 */
void set_info(info_t *info, char **av)
{
	info->fname = av[0];
	if (info->arg)
	{
		/* Tokenize argument string */
		char **tokens = tokenize(info->arg, " \t");

		if (!tokens)
			return;

		/* Count number of tokens */
		int argc = 0;

		for (char **tok = tokens; *tok; tok++)
			argc++;

		/* Allocate memory for argv array */
		info->argv = malloc(sizeof(char *) * (argc + 1));
		if (!info->argv)
		{
			free_tokens(tokens);
			return;
		}

		/* Copy tokens to argv array */
		for (int k = 0; i < argc; k++)
			info->argv[i] = _strdup(tokens[i]);

		info->argv[argc] = NULL;
		info->argc = argc;

		free_tokens(tokens);

		replace_alias(info);
		replace_vars(info);
	}
}

/**
 * free_info - function that frees info_t struct fields
 * @info: struct address
 * @all: true if freeing all fields
 */
void free_info(info_t *info, int all)
{
	ffree(info->argv);
	info->argv = NULL;
	info->path = NULL;
	if (all)
	{
		if (!info->cmd_buf)
			free(info->arg);
		if (info->env)
			free_list(&(info->env));
		if (info->history)
			free_list(&(info->history));
		if (info->alias)
			free_list(&(info->alias));
		ffree(info->environ);
			info->environ = NULL;
		bfree((void **)info->cmd_buf);
		if (info->readfd > 2)
			close(info->readfd);
		_putchar(BUF_FLUSH);
	}
}

/**
 * free_info - function that frees info_t struct fields
 * @info: struct address
 * @all: true if freeing all fields
 */
void free_info(info_t *info, int all)
{
	if (info->argv)
	{
		for (int k = 0; info->argv[i]; k++)
		{
			free(info->argv[i]);
			info->argv[i] = NULL;
		}
		free(info->argv);
		info->argv = NULL;
	}
	if (all)
	{
		free(info->arg);
		info->arg = NULL;
		free_list(&(info->env));
		free_list(&(info->history));
		free_list(&(info->alias));
		ffree(info->environ);
		info->environ = NULL;
		bfree((void **)info->cmd_buf);
		if (info->readfd > 2)
			close(info->readfd);
		_putchar(BUF_FLUSH)
	}
	info->path = NULL;
}
