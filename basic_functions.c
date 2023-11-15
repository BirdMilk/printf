#include "main.h"
/**
 * _isprintable - checks if a character is printable or not
 * @s: the character to be checked.
 *
 * Return: returns 1 if s is printable, 0 if it isn't
 */
int _isprintable(char s)
{
	if (s >= 32 && s < 127)
	{
		return (1);
	}
	else
	{
		return (0);
	}
}

/**
 * insert_hexa - Append ascci in hexadecimal code to buffer
 * @buffer: Array of chars.
 * @i: Index at which to start appending.
 * @ascii: ASSCI CODE.
 * Return: Always 3
 */
int insert_hexa(char ascii, char buffer[], int i)
{
	char hex_table[] = "0123456789ABCDEF";

	if (ascii < 0)
	{
		ascii *= -1;
	}

	buffer[i++] = '\\';
	buffer[i++] = 'x';
	buffer[i++] = hex_table[ascii / 16];
	buffer[i] = hex_table[ascii % 16];

	return (3);
}
/**
 * _isdigit - Verifies if a char is a digit
 * @c: Char to be evaluated
 *
 * Return: 1 if c is a digit, 0 otherwise
 */
int _isdigit(char c)
{
	if (c >= '0' && c <= '9')
	{
		return (1);
	}
	else
	{
		return (0);
	}
}
/**
 * change_size - Casts a number to the specified size
 * @num: Number to be casted.
 * @size: Number indicating the type to be casted.
 *
 * Return: Casted value of num
 */
long int change_size(long int num, int size)
{
	if (size == LONG_SIZE)
	{
		return (num);
	}
	else if (size == SHORT_SIZE)
	{
		return ((short)num);
	}
	else
	{
		return ((int)num);
	}
}
/**
 * size_converter - Converts a number to the specified size
 * @num: Number to be converted
 * @size: Number indicating the type to be casted
 *
 * Return: returns the converted value of num
 */
long int size_converter(unsigned long int num, int size)
{
	if (size == LONG_SIZE)
		return (num);
	else if (size == SHORT_SIZE)
		return ((unsigned short)num);

	return ((unsigned int)num);
}
