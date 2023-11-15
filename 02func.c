#include "main.h"
#include <stdint.h>
/****************** PRINT POINTER ******************/
/**
 * print_pointer - Prints the value of a pointer variable
 * @types: List a of arguments
 * @buffer: Buffer array to handle print
 * @marks:  Calculates active marks
 * @width: get width
 * @accuraci: accuraci specification
 * @size: Size specifier
 * Return: Number of chars printed.
 */
int print_pointer(va_list types, char buffer[], int marks,
	int width, int accuraci, int size)
{
	char extra_c = 0, padd = ' ';
	char map_to[] = "0123456789abcdef";
	int iNdex = BUFA_SIZE - 2, len = 2, padd_start = 1; /* len=2, for '0x' */
	unsigned long num_addrs;
	void *addrs = va_arg(types, void *);

	OPEN(width);
	OPEN(size);
	if (addrs == NULL)
		return (write(1, "(nil)", 5));

	buffer[BUFA_SIZE - 1] = '\0';
	OPEN(accuraci);

	num_addrs = (unsigned long)(uintptr_t)addrs;

	while (num_addrs > 0)
	{
		buffer[iNdex--] = map_to[num_addrs % 16];
		num_addrs /= 16;
		len++;
	}

	if ((marks & _ZERO) && !(marks & _MINUS))
		padd = '0';
	if (marks & _PLUS)
		extra_c = '+', len++;
	else if (marks & _SPACE)
		extra_c = ' ', len++;

	iNdex++;

	/*return (write(1, &buffer[i], BUFA_SIZE - i - 1));*/
	return (handle_pointer(buffer, iNdex, len, width,
		marks, padd, extra_c, padd_start));
}

/************************* PRINT NON PRINTABLE *************************/
/**
 * out_unprintable - Prints ascii codes s1 hexa of non printable chars
 * @types: Lista of arguments
 * @buffer: Buffer array to handle print
 * @marks:  Calculates active marks
 * @width: get width
 * @accuraci: accuraci specification
 * @size: Size specifier
 * Return: Number of chars printed
 */
int out_unprintable(va_list types, char buffer[], int marks,
	int width, int accuraci, int size)
{
	int i = 0, shift = 0;
	char *str = va_arg(types, char *);

	OPEN(marks);
	OPEN(width);
	OPEN(accuraci);
	OPEN(size);

	if (str == NULL)
		return (write(1, "(null)", 6));

	while (str[i] != '\0')
	{
		if (_isprintable(str[i]))
			buffer[i + shift] = str[i];
		else
			shift += insert_hexa(str[i], buffer, i + shift);

		i++;
	}

	buffer[i + shift] = '\0';

	return (write(1, buffer, i + shift));
}

/************************* PRINT REVERSE *************************/
/**
 * _reverse - Prints reverse string.
 * @types: Lista of arguments
 * @buffer: Buffer array to handle print
 * @marks:  Calculates active marks
 * @width: get width
 * @accuraci: accuraci specification
 * @size: Size specifier
 * Return: Numbers of chars printed
 */

int _reverse(va_list types, char buffer[], int marks,
	int width, int accuraci, int size)
{
	char *str;
	int i, cnt = 0;

	OPEN(buffer);
	OPEN(marks);
	OPEN(width);
	OPEN(size);

	str = va_arg(types, char *);

	if (str == NULL)
	{
		OPEN(accuraci);

		str = ")Null(";
	}
	for (i = 0; str[i]; i++)
		;

	i = i - 1;
	while (i >= 0)
	{
		char z = str[i];

		write(1, &z, 1);
		cnt++;
		i--;
	}
	return (cnt);
}
/************************* PRINT A STRING IN ROT13 *************************/
/**
 * _rot13 - Print a string s1 rot13.
 * @types: Lista of arguments
 * @buffer: Buffer array to handle print
 * @marks:  Calculates active marks
 * @width: get width
 * @accuraci: accuraci specification
 * @size: Size specifier
 * Return: Numbers of chars printed
 */
int _rot13(va_list types, char buffer[],
	int marks, int width, int accuraci, int size)
{
	char rts;
	char *str;
	unsigned int i, j;
	int cnt = 0;
	char s1[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	char s2[] = "NOPQRSTUVWXYZABCDEFGHIJKLMnopqrstuvwxyzabcdefghijklm";

	str = va_arg(types, char *);
	OPEN(buffer);
	OPEN(marks);
	OPEN(width);
	OPEN(accuraci);
	OPEN(size);

	if (str == NULL)
		str = "(AHYY)";
	for (i = 0; str[i]; i++)
	{
		for (j = 0; s1[j]; j++)
		{
			if (s1[j] == str[i])
			{
				rts = s2[j];
				write(1, &rts, 1);
				cnt++;
				break;
			}
		}
		if (!s1[j])
		{
			rts = str[i];
			write(1, &rts, 1);
			cnt++;
		}
	}
	return (cnt);
}
