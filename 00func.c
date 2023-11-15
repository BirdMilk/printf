#include "main.h"
#include <stdint.h>
/*PRINT CHAR*/
/**
 * output_characters - this function prints a char
 * @types: List a of arguments
 * @buffer: Buffer array to handle print
 * @marks:  Calculates active marks
 * @width: Width
 * @accuraci: accuraci specification
 * @size: the size specifier
 * Return: the number of chars printed
 */
int output_characters(va_list types, char buffer[], int marks,
	int width, int accuraci, int size)
{
	char c = va_arg(types, int);

	return (handle_char(c, buffer, marks, width, accuraci, size));
}
/*PRINT STRING*/
/**
 * output_string - Prints a string
 * @types: List a of arguments
 * @buffer: Buffer array to handle print
 * @marks:  Calculates active marks
 * @width: get width.
 * @accuraci: accuraci specification
 * @size: Size specifier
 * Return: Number of chars printed
 */
int output_string(va_list types, char buffer[], int marks,
	int width, int accuraci, int size)
{
	int length = 0, i = 0, y;
	char *str = va_arg(types, char *);

	OPEN(width);
	OPEN(accuraci);
	OPEN(size);
	OPEN(buffer);
	OPEN(marks);
	if (str == NULL)
	{
		str = "(null)";
		if (accuraci >= 6)
			str = "      ";
	}
	for (y = 0; str[length] != '\0'; y++)
		length++;
	if (accuraci >= 0 && accuraci < length)
		length = accuraci;
	if (width > length)
	{
		if (marks & _MINUS)
		{
			write(1, &str[0], length);
			for (i = width - length; i > 0; i--)
			{
				write(1, " ", 1);
			}
			return (width);
		}
		else
		{
			for (int num_of_spac = width - length; num_of_spac > 0; num_of_spac--)
			{
				write(1, " ", 1);
			}
			write(1, &str[0], length);
			return (width);
		}
	}
	return (write(1, str, length));
}
/*PRINT PERCENT SIGN*/
/**
 * output_percent - Prints a percent sign
 * @types: Lista of arguments
 * @buffer: Buffer array to handle print
 * @marks:  Calculates active marks
 * @width: get width.
 * @accuraci: accuraci specification
 * @size: Size specifier
 * Return: Number of chars printed
 */
int output_percent(va_list types, char buffer[],
	int marks, int width, int accuraci, int size)
{
	OPEN(marks);
	OPEN(width);
	OPEN(accuraci);
	OPEN(size);
	OPEN(types);
	OPEN(buffer);
	return (write(1, "%%", 1));
}
/*PRINT INT*/
/**
 * out_int - Print int
 * @types: Lista of arguments
 * @buffer: Buffer array to handle print
 * @marks:  Calculates active marks
 * @width: get width.
 * @accuraci: accuraci specification
 * @size: Size specifier
 * Return: Number of chars printed
 */
int out_int(va_list types, char buffer[],
	int marks, int width, int accuraci, int size)
{
	int i = BUFA_SIZE - 2;
	int _isMinus = 0;
	long int n = va_arg(types, long int);
	unsigned long int num;

	n = change_size(n, size);

	if (n == 0)
		buffer[i--] = '0';

	buffer[BUFA_SIZE - 1] = '\0';
	num = (unsigned long int)n;

	if (n < 0)
	{
		num = (unsigned long int)((-1) * n);
		_isMinus = 1;
	}

	while (num > 0)
	{
		buffer[i--] = (num % 10) + '0';
		num /= 10;
	}

	i++;

	return (handle_number(_isMinus, i, buffer, marks, width, accuraci, size));
}
/*PRINT BINARY*/
/**
 * out_bin - Prints an unsigned number
 * @types: Lista of arguments
 * @buffer: Buffer array to handle print
 * @marks:  Calculates active marks
 * @width: get width.
 * @accuraci: accuraci specification
 * @size: Size specifier
 * Return: Numbers of char printed.
 */
int out_bin(va_list types, char buffer[], int marks,
	int width, int accuraci, int size)
{
	unsigned int n, i, sum;
	uint64_t m;
	unsigned int a[32];
	int count;

	OPEN(buffer);
	OPEN(marks);
	OPEN(width);
	OPEN(accuraci);
	OPEN(size);

	n = va_arg(types, unsigned int);
	m = 2147483648U; /* (2 ^ 31) */
	a[0] = n / m;
	for (i = 1; i < 32; i++)
	{
		m /= 2;
		a[i] = (n / m) % 2;
	}
	i = 0, sum = 0, count = 0;
	while (i < 32)
	{
		sum += a[i];
		if (sum || i == 31)
		{
			char z = '0' + a[i];

			write(1, &z, 1);
			count++;
		}
		i++;
	}

	return (count);
}
