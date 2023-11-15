#include "main.h"
/**
 * handle_char - Prints a string
 * @c: char types.
 * @buffer: Buffer array to handle print
 * @marks:  Calculates active marks.
 * @width: get width.
 * @accuraci: accuraci specifier
 * @size: Size specifier
 *
 * Return: Number of chars printed.
 */
int handle_char(char c, char buffer[],
	int marks, int width, int accuraci, int size)
{ /* char is stored at left and paddind at buffer's right */
	int i = 0;
	char padd = ' ';

	OPEN(accuraci);
	OPEN(size);

	if (marks & _ZERO)
		padd = '0';

	buffer[i++] = c;
	buffer[i] = '\0';

	if (width > 1)
	{
		buffer[BUFA_SIZE - 1] = '\0';
		for (i = 0; i < width - 1; i++)
			buffer[BUFA_SIZE - i - 2] = padd;

		if (marks & _MINUS)
			return (write(1, &buffer[0], 1) +
					write(1, &buffer[BUFA_SIZE - i - 1], width - 1));
		else
			return (write(1, &buffer[BUFA_SIZE - i - 1], width - 1) +
					write(1, &buffer[0], 1));
	}

	return (write(1, &buffer[0], 1));
}
/************************* WRITE NUMBER *************************/
/**
 * handle_number - Prints a string
 * @iNdex: char types.
 * @buffer: Buffer array to handle print
 * @marks:  Calculates active marks
 * @width: get width.
 * @accuraci: accuraci specifier
 * @size: Size specifier
 * @_isPlus: indicates if it is a posotive number
 *
 * Return: Number of chars printed.
 */
int handle_number(int _isPlus, int iNdex, char buffer[],
	int marks, int width, int accuraci, int size)
{
	int length = BUFA_SIZE - iNdex - 1;
	char padd = ' ', extra_ch = 0;

	OPEN(size);

	if ((marks & _ZERO) && !(marks & _MINUS))
		padd = '0';
	if (_isPlus)
		extra_ch = '-';
	else if (marks & _PLUS)
		extra_ch = '+';
	else if (marks & _SPACE)
		extra_ch = ' ';

	return (handle_nums(iNdex, buffer, marks, width, accuraci,
		length, padd, extra_ch));
}
/**
 * handle_nums - Write a number using a bufffer
 * @iNdex: Index at which the number starts on the buffer
 * @buffer: Buffer
 * @marks: marks
 * @width: width
 * @prec: accuraci specifier
 * @length: Number length
 * @padd: Pading char
 * @extra_c: Extra char
 *
 * Return: Number of printed chars.
 */
int handle_nums(int iNdex, char buffer[], int marks,
	int width, int prec, int length, char padd, char extra_c)
{
	int i, padd_start = 1;

	if (prec == 0 && iNdex == BUFA_SIZE - 2 && buffer[iNdex] == '0' && width == 0)
		return (0); /* printf(".0d", 0)  no char is printed */
	if (prec == 0 && iNdex == BUFA_SIZE - 2 && buffer[iNdex] == '0')
		buffer[iNdex] = padd = ' '; /* width is displayed with padding ' ' */
	if (prec > 0 && prec < length)
		padd = ' ';
	while (prec > length)
		buffer[--iNdex] = '0', length++;
	if (extra_c != 0)
		length++;
	if (width > length)
	{
		for (i = 1; i < width - length + 1; i++)
			buffer[i] = padd;
		buffer[i] = '\0';
		if (marks & _MINUS && padd == ' ')/* Asign extra char to left of buffer */
		{
			if (extra_c)
				buffer[--iNdex] = extra_c;
			return (write(1, &buffer[iNdex], length) + write(1, &buffer[1], i - 1));
		}
		else if (!(marks & _MINUS) && padd == ' ')/* extra char to left of buff */
		{
			if (extra_c)
				buffer[--iNdex] = extra_c;
			return (write(1, &buffer[1], i - 1) + write(1, &buffer[iNdex], length));
		}
		else if (!(marks & _MINUS) && padd == '0')/* extra char to left of padd */
		{
			if (extra_c)
				buffer[--padd_start] = extra_c;
			return (write(1, &buffer[padd_start], i - padd_start) +
				write(1, &buffer[iNdex], length - (1 - padd_start)));
		}
	}
	if (extra_c)
		buffer[--iNdex] = extra_c;
	return (write(1, &buffer[iNdex], length));
}
/**
 * handle_unsigned - Writes an unsigned number
 * @: Number indicating if the num is negative
 * @iNdex: Index at which the number starts in the buffer
 * @buffer: Array of chars
 * @marks: marks specifiers
 * @width: Width specifier
 * @accuraci: accuraci specifier
 * @size: Size specifier
 * @_isMinus: negative integer
 *
 * Return: Number of written chars.
 */
int handle_unsigned(int _isMinus, int iNdex,
	char buffer[],
	int marks, int width, int accuraci, int size)
{
	int length = BUFA_SIZE - iNdex - 1, i = 0;
	char padd = ' ';

	OPEN(_isMinus);
	OPEN(size);

	if (accuraci == 0 && iNdex == BUFA_SIZE - 2 && buffer[iNdex] == '0')
		return (0); /* printf(".0d", 0)  no char is printed */
	if (accuraci > 0 && accuraci < length)
		padd = ' ';
	while (accuraci > length)
	{
		buffer[--iNdex] = '0';
		length++;
	}
	if ((marks & _ZERO) && !(marks & _MINUS))
		padd = '0';

	if (width > length)
	{
		for (i = 0; i < width - length; i++)
			buffer[i] = padd;

		buffer[i] = '\0';

		if (marks & _MINUS) /* Asign extra char to left of buffer [buffer>padd]*/
		{
			return (write(1, &buffer[iNdex], length) + write(1, &buffer[0], i));
		}
		else /* Asign extra char to left of padding [padd>buffer]*/
		{
			return (write(1, &buffer[0], i) + write(1, &buffer[iNdex], length));
		}
	}
	return (write(1, &buffer[iNdex], length));
}
/**
 * handle_pointer - Write a memory address
 * @buffer: Arrays of chars
 * @iNdex: Index at which the number starts in the buffer
 * @length: Length of number
 * @width: Width specifier
 * @marks: marks specifier
 * @padd: Char representing the padding
 * @extra_c: Char representing extra char
 * @padd_start: Index at which padding should start
 *
 * Return: Number of written chars.
 */
int handle_pointer(char buffer[], int iNdex, int length,
	int width, int marks, char padd, char extra_c, int padd_start)
{
	int i;

	if (width > length)
	{
		for (i = 3; i < width - length + 3; i++)
			buffer[i] = padd;
		buffer[i] = '\0';
		if (marks & _MINUS && padd == ' ')/* Asign extra char to left of buffer */
		{
			buffer[--iNdex] = 'x';
			buffer[--iNdex] = '0';
			if (extra_c)
				buffer[--iNdex] = extra_c;
			return (write(1, &buffer[iNdex], length) + write(1, &buffer[3], i - 3));
		}
		else if (!(marks & _MINUS) && padd == ' ')/* extra char to left of buffer */
		{
			buffer[--iNdex] = 'x';
			buffer[--iNdex] = '0';
			if (extra_c)
				buffer[--iNdex] = extra_c;
			return (write(1, &buffer[3], i - 3) + write(1, &buffer[iNdex], length));
		}
		else if (!(marks & _MINUS) && padd == '0')/* extra char to left of padd */
		{
			if (extra_c)
				buffer[--padd_start] = extra_c;
			buffer[1] = '0';
			buffer[2] = 'x';
			return (write(1, &buffer[padd_start], i - padd_start) +
				write(1, &buffer[iNdex], length - (1 - padd_start) - 2));
		}
	}
	buffer[--iNdex] = 'x';
	buffer[--iNdex] = '0';
	if (extra_c)
		buffer[--iNdex] = extra_c;
	return (write(1, &buffer[iNdex], BUFA_SIZE - iNdex - 1));
}
