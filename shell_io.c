#include "shell.h"

/**
 * _eputs - prints input string
 * @str: the string to be printed
 *
 * Return: Nothing
 */
void _eputs(char *str)
{
	if (!str)
		return;

	for (; *str; str++)
		_eputchar(*str);
}

/**
 * _eputchar - writes the character c to stderr
 * @c: character to print
 *
 * Return: success (1).
 * On error, return (-1), and errno is set appropriately.
 */
int _eputchar(char c)
{
	static int i;
	static char buf[WRITE_BUF_SIZE] = {0};

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(2, buf, i);
		i = 0;
	}

	if (c != BUF_FLUSH)
		buf[i++] = c;

	return (1);
}

/**
 * _putfile_descp - writes the character c to given file_descp
 * @c: The character to print
 * @file_descp: The file descriptor to write to
 *
 * Return: success (1).
 *         On error, return (-1), and errno is set appropriately.
 */
int _putfile_descp(char c, int file_descp)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(file_descp, buf, i);
		i = 0;
	}

	if (c != BUF_FLUSH)
		buf[i++] = c;

	return (1);
}

/**
 * _putsfile_descp - function writes a string to a specified file descriptor.
 * @str: string variable is the string to be printed.
 * @file_descp: file_descp to write to
 *
 * Return: number of characters written
 */
int _putsfile_descp(char *str, int file_descp)
{
	int i = 0;

	if (!str)
		return (0);

	while (*str)
	{
		i += _putfile_descp(*str++, file_descp);
	}
	return (i);
}
