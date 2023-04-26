#include "shell.h"

/**
 * _strlen - gets length of a string
 * @str: parameter 1
 * Return: length
 */

int _strlen(char *str)
{
	int len;

	if (str == NULL)
		return (NULL);

	for (len = 0; *str != '\0'; str++)
	{
		len++;
	}
	return (len);
}

/**
 * _strcmp - a function that compares strings
 * @str1: parameter 1
 * @str2: parameter 2
 * Return: 0 if str1 and str2 are equal
 * negative integer if the stopping character
 * in @str1 was less than the stopping
 * character in @str2
 * positive integer if the stopping character
 * in @str1 was greater than the stopping
 * character in @str2
*/

int _strcmp(char *str1, char *str2)
{
	int i = 0, r;

	while (str1[i] != '\0' && str2[i] != '\0')
	{
		if (str1[i] != str2[i])
		{
			r = str1[i] - str2[i];
			break;
		}
		else
		{
			r = str1[i] - str2[i];
		}
		i++;
	}

	return (r);
}

/**
 * start_with - main function
 * @pin: parameter 1
 * @stacking: parameter 2
 * Return: address
 */

char *start_with(const char *pin, const char *stacking)
{
	while (*pin != NULL)
		if (*pin++ != *stacking)
			return (NULL);
	return ((char *)stacking);
}


/**
 * _strcat - function to append string
 * @dst: parameter 1
 * @sorc: parameter 2
 * Return: A pointer to the destination string @dest
 */

char *_strcat(char *dst, char *sorc)
{
	int ind = 0;
	int len = 0;

	while (dst[ind++])
		len++;

	for (ind = 0; sorc[ind]; ind++)
		dst[len++] = sorc[ind];
	return (dst);
}
