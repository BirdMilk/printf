#include "main.h"
/**
 * _size - Calculates the size to cast the argument
 * @format: Formatted string in which to print the arguments
 * @i: List of arguments to be printed.
 *
 * Return: accuraci.
 */
int _size(const char *format, int *i)
{
	int current_index = *i + 1;
	int size = 0;

	if (format[current_index] == 'l')
		size = LONG_SIZE;
	else if (format[current_index] == 'h')
		size = SHORT_SIZE;

	size == 0 ? (*i = current_index - 1) : (*i = current_index);

	return (size);
}
/**
 * _width - Calculates the width for printing
 * @format: Formatted string in which to print the arguments.
 * @i: List of arguments to be printed.
 * @list: list of arguments.
 *
 * Return: width.
 */
int _width(const char *format, int *i, va_list list)
{
	int current_index;
	int width = 0;

	for (current_index = *i + 1; format[current_index] != '\0'; current_index++)
	{
		if (_isdigit(format[current_index]))
		{
			width *= 10;
			width += format[current_index] - '0';
		}
		else if (format[current_index] == '*')
		{
			current_index++;
			width = va_arg(list, int);
			break;
		}
		else
			break;
	}

	*i = current_index - 1;

	return (width);
}
/**
 * _accuracy  - Calculates the accuraci for printing
 * @format: Formatted string in which to print the arguments
 * @i: List of arguments to be printed.
 * @list: list of arguments.
 *
 * Return: accuraci.
 */
int _accuracy(const char *format, int *i, va_list list)
{
	int current_index = *i + 1;
	int accuraci = -1;

	if (format[current_index] != '.')
		return (accuraci);

	accuraci = 0;

	for (current_index += 1; format[current_index] != '\0'; current_index++)
	{
		if (_isdigit(format[current_index]))
		{
			accuraci *= 10;
			accuraci += format[current_index] - '0';
		}
		else if (format[current_index] == '*')
		{
			current_index++;
			accuraci = va_arg(list, int);
			break;
		}
		else
			break;
	}

	*i = current_index - 1;

	return (accuraci);
}
/**
 * _flags - Calculates active marks
 * @format: Formatted string in which to print the arguments
 * @i: take a parameter.
 * Return: marks:
 */
int _flags(const char *format, int *i)
{
	/* - + 0 # ' ' */
	/* 1 2 4 8  16 */
	int j, current_index;
	int marks = 0;
	const char FLAGS_CH[] = {'-', '+', '0', '#', ' ', '\0'};
	const int FLAGS_ARR[] = {_MINUS, _PLUS, _ZERO, _HASH, _SPACE, 0};

	current_index = *i + 1;
	while (format[current_index] != '\0')
	{
		for (j = 0; FLAGS_CH[j] != '\0'; j++)
			if (format[current_index] == FLAGS_CH[j])
			{
				marks |= FLAGS_ARR[j];
				break;
			}

		if (FLAGS_CH[j] == 0)
			break;
		current_index++;
	}
	*i = current_index - 1;

	return (marks);
}
