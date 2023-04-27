#include "../inc/my_functions.h"

/**
 * main - Entry point of the program
 *
 * Return: 0 (Success)
 */
int main(void)
{
    int result;

    result = func1(5, 6);
    printf("Result of func1: %d\n", result);

    result = func2(10);
    printf("Result of func2: %d\n", result);

    return (0);
}
