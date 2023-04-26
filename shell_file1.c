#include "shell.h"

/**
 * _strcpy - copies a string from one pointer to another
 * @sorc: parameter 1
 * @dst: parameter 2
 * Return: pointer to dest input parameter
*/

char *_strcpy(char *dst, char *sorc)
{
	int a, b = 0;

	for (a = 0; sorc[a] != '\0'; ++a)
	{
		dst[b] = sorc[a];
		++b;
	}
	dst[b] = '\0';

	return (dst);
}

/**
 * _strdup - gets address of the of str.
 * @str: string to duplicate
 * Return: pointer to duplicate string
 */

char *_strdup(char *str)
{
	char *duplicate;
	int i;
	int l = 0;

	if (str == 0)
	{
		return ('\0');
	}
	for (i = 0; str[i]; i++)
	{
		l++;
	}

	duplicate = malloc(sizeof(char) * (l + 1));

	if (duplicate == NULL)
	{
		return ('\0');
	}
	for (i = 0; str[i]; i++)
	{
		duplicate[i] = str[i];
	}
	duplicate[l] = '\0';
	return (duplicate);
}

/**
 * _putchar - function that prints a character
 * @c: parameter
 * Return: 1 at success and -1 at error
 */

int _putchar(char c)
{
	int result;

	result = write(1, &c, 1);

	return (result);
}


/**
 * _puts - function that prints a string
 * @str: parameter
 * Return: Nothing
*/

void _puts(char *str)
{
	int i;

	for (i = 0; *str != '\0'; str++)
	{
		_putchar(*str + 0);
		i++;
	}
	_putchar('\n');
}
