#include <stddef.h>

/**
 * _strmcpy - copies a string
 * @dst: the destination string to be copied to
 * @src: the source string
 * @n: the maximum number of characters to copy
 *
 * Return: pointer to the destination string
 */
char *_strmcpy(char *dst, const char *src, size_t n)
{
	size_t i;

	for (i = 0; i < n && src[i] != '\0'; i++)
		dst[i] = src[i];
	for (; i < n; i++)
		dst[i] = '\0';

	return (dst);
}

/**
 * _strmcat - combines two strings into a single string.
 * @dst: pointer to the destination string
 * @src: pointer to the source string
 * @n: highest number of characters that are to be appended
 *
 * Return: pointer to the resulting string
 */
char *_strmcat(char *dst, char *src, int n)
{
	char *start = dst;

	while (*dst != '\0')
		dst++;

	while (*src != '\0' && n--)
		*dst++ = *src++;

	*dst = '\0';

	return (start);
}

/**
 * _strchr - locates first occurrence of character in a string
 * @s: string to be searched
 * @c: character to be found
 *
 * Return: pointer of the first occurrence of the character c in the string s,
 * or NULL if the character is not found
 */
char *_strchr(char *s, char c)
{
	while (*s)
	{
		if (*s == c)
			return (s);
		s++;
	}

	if (c == '\0')
		return (s);

	return (NULL);
}
