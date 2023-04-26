#include "shell.h"

/**
 * interactive - will returns true to confirm shell is in interactive mode
 * @info: The struct address refers to the memory location of a struct.
 *
 * Return: interactive mode (1), 0 otherwise
 */
int interactive(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * is_delim - The function tests if a character is a delimiter
 * @c: The function takes a character as input to be checked.
 * @delim: string of the delimiter
 * Return: true (1), false (0)
 */
int is_delim(char c, char *delim)
{
	int i;

	for (i = 0; delim[i] != '\0'; i++)
	{
		if (c == delim[i])
		{
			return (1);
		}
	}

	return (0);
}

/**
 * _isalpha - The function determines if a character is alphabetic.
 * @c: The function takes a character as input to check.
 *
 * Return: if alphabetic (1), otherwise (0)
 */
int _isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * _atoi - The function converts a string to an integer.
 *
 * @s: String to be converted
 *
 * Return:The function returns the integer representation of the string.
 * if no numbers in string (0)
 */
int _atoi(char *s)
{
	int i = 0, sign = 1, flag = 0, output = 0;
	unsigned int result = 0;

	while (s[i])
	{
		if (s[i] == '-')
			sign *= -1;
		if (s[i] >= '0' && s[i] <= '9')
		{
			flag = 1;
			result = result * 10 + (s[i] - '0');
		}
		else if (flag == 1)
			break;
		i++;
	}
	if (sign == -1)
		output = -result;
	else
		output = result;
	return (output);
}
