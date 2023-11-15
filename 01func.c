#include "main.h"
/************************* PRINT UNSIGNED NUMBER *************************/
/**
 * out_unsign - Prints an unsigned number
 * @types: List a of arguments
 * @buffer: Buffer array to handle print
 * @marks:  Calculates active marks
 * @width: get width
 * @accuraci: accuraci specification
 * @size: Size specifier
 * Return: Number of chars printed.
 */
int out_unsign(va_list types, char buffer[], int marks,
	int width, int accuraci, int size)
{
	int c = 0;
	int i = BUFA_SIZE - 2;
	unsigned long int num = va_arg(types, unsigned long int);

	num = size_converter(num, size);
	if (num == 0)
		buffer[i--] = '0';

	buffer[BUFA_SIZE - 1] = '\0';
	for (c = 0; num > 0; c++)
	{
		buffer[i--] = (num % 10) + '0';
		num /= 10;
	}
	i++;
	return (handle_unsign(0, i, buffer, marks, width, accuraci, size));
}
/************* PRINT UNSIGNED NUMBER IN OCTAL  ****************/
/**
 * out_oct - Prints an unsigned number in octal notation
 * @types: Lista of arguments
 * @buffer: Buffer array to handle print
 * @marks:  Calculates active marks
 * @width: get width
 * @accuraci: accuraci specification
 * @size: Size specifier
 * Return: Number of chars printed
 */
int out_oct(va_list types, char buffer[], int marks,
	int width, int accuraci, int size)
{

	int i = BUFA_SIZE - 2;
	unsigned long int num = va_arg(types, unsigned long int);
	unsigned long int initial_number = num;

	OPEN(width);

	num = size_converter(num, size);

	if (num == 0)
		buffer[i--] = '0';

	buffer[BUFA_SIZE - 1] = '\0';

	do {
		buffer[i--] = (num % 8) + '0';
		num /= 8;
	} while (num > 0);

	if (marks & _HASH && initial_number != 0)
		buffer[i--] = '0';

	i++;

	return (handle_unsign(0, i, buffer, marks, width, accuraci, size));
}

/************** PRINT UNSIGNED NUMBER IN HEXADECIMAL **************/
/**
 * out_hexa - Prints an unsigned number in hexadecimal notation
 * @types: Lista of arguments
 * @buffer: Buffer array to handle print
 * @marks:  Calculates active marks
 * @width: get width
 * @accuraci: accuraci specification
 * @size: Size specifier
 * Return: Number of chars printed
 */
int out_hexa(va_list types, char buffer[], int marks,
	int width, int accuraci, int size)
{
	return (print_hexa(types, "0123456789abcdef", buffer,
		marks, 'x', width, accuraci, size));
}

/************* PRINT UNSIGNED NUMBER IN UPPER HEXADECIMAL **************/
/**
 * out_hexa_upper - Prints an unsigned number in upper hexadecimal notation
 * @types: Lista of arguments
 * @buffer: Buffer array to handle print
 * @marks:  Calculates active marks
 * @width: get width
 * @accuraci: accuraci specification
 * @size: Size specifier
 * Return: Number of chars printed
 */
int out_hexa_upper(va_list types, char buffer[], int marks,
	int width, int accuraci, int size)
{
	return (print_hexa(types, "0123456789ABCDEF", buffer,
		marks, 'X', width, accuraci, size));
}

/************** PRINT HEXX NUM IN LOWER OR UPPER **************/
/**
 * print_hexa - Prints a hexadecimal number in lower or upper
 * @types: Lista of arguments
 * @hex_table: Array of values to map the number to
 * @buffer: Buffer array to handle print
 * @marks:  Calculates active marks
 * @flag_ch: Calculates active marks
 * @width: get width
 * @accuraci: accuraci specification
 * @size: Size specifier
 * @size: Size specification
 * Return: Number of chars printed
 */
int print_hexa(va_list types, char hex_table[], char buffer[],
	int marks, char flag_ch, int width, int accuraci, int size)
{
	int i = BUFA_SIZE - 2;
	unsigned long int num = va_arg(types, unsigned long int);
	unsigned long int initial_number = num;

	OPEN(width);
	num = size_converter(num, size);
	if (num == 0)
		buffer[i--] = '0';

	buffer[BUFA_SIZE - 1] = '\0';
	do {
		buffer[i--] = hex_table[num % 16];
		num /= 16;
	} while (num > 0);
	if (marks & _HASH && initial_number != 0)
	{
		buffer[i--] = flag_ch;
		buffer[i--] = '0';
	}

	i++;
	return (handle_unsign(0, i, buffer, marks, width, accuraci, size));
}
