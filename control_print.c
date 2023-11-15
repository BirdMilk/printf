#include "main.h"
/**
 * con_out - Prints an argument based on its type
 * @form: Formatted string in which to print the arguments.
 * @list: List of arguments to be printed.
 * @iNdex: iNdex.
 * @buffer: Buffer array to handle print.
 * @marks: Calculates active marks
 * @width: get width.
 * @accuraci: accuraci specification
 * @size: Size specifier
 * Return: 1 or 2;
 */
int con_out(const char *form, int *iNdex, va_list list, char buffer[],
	int marks, int width, int accuraci, int size)
{
	int i, unknown_length = 0, rendered_characters = -1;
	form_t form_types[] = {
		{'c', output_characters}, {'s', output_string}, {'%', output_percent},
		{'i', out_int}, {'d', out_int}, {'b', out_bin},
		{'u', out_unsign}, {'o', out_oct}, {'x', out_hexa},
		{'X', out_hexa_upper}, {'p', print_pointer}, {'S', out_unprintable},
		{'r', _reverse}, {'R', _rot13}, {'\0', NULL}
	};

	i = 0;
	while (form_types[i].form != '\0')
	{
		if (form[*iNdex] == form_types[i].form)
			return (form_types[i].func(list, buffer, marks, width, accuraci, size));

		i++;
	}
	if (form_types[i].form == '\0')
	{
		if (form[*iNdex] == '\0')
			return (-1);
		unknown_length += write(1, "%%", 1);
		if (form[*iNdex - 1] == ' ')
			unknown_length += write(1, " ", 1);
		else if (width)
		{
			--(*iNdex);
			while (form[*iNdex] != ' ' && form[*iNdex] != '%')
				--(*iNdex);
			if (form[*iNdex] == ' ')
				--(*iNdex);
			return (1);
		}
		unknown_length += write(1, &form[*iNdex], 1);
		return (unknown_length);
	}
	return (rendered_characters);
}
