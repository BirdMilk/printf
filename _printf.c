#include "main.h"
/**
 * _buffer - renders the contents of the buffer
 * @buff: Array of characters
 * @buffer_index: Index at which to add next char
 */
void _buffer(char buff[], int *buffer_index)
{
	if (*buffer_index > 0)
		write(1, &buff[0], *buffer_index);

	*buffer_index = 0;
}
/**
 * _printf - close replica of Printf function
 * @style: style.
 * Return: Printed chars.
 */
int _printf(const char *style, ...)
{
	int i,  rendered = 0, rendered_characters = 0;
	int marks, width, accuraci, size, buffer_index = 0;
	va_list list;
	char buff[BUFA_SIZE];

	if (style == NULL)
		return (-1);

	va_start(list, style);

	i = 0;
	while (style && style[i] != '\0')
	{
		if (style[i] != '%')
		{
			buff[buffer_index++] = style[i];
			if (buffer_index == BUFA_SIZE)
				_buffer(buff, &buffer_index);
			rendered_characters++;
		}
		else
		{
			_buffer(buff, &buffer_index);
			marks = _flags(style, &i);
			width = _width(style, &i, list);
			accuraci = _accuracy(style, &i, list);
			size = _size(style, &i);
			++i;
			rendered = con_out(style, &i, list, buff,
				marks, width, accuraci, size);
			if (rendered == -1)
				return (-1);
			rendered_characters += rendered;
		}
		i++;
	}
	_buffer(buff, &buffer_index);
	va_end(list);
	return (rendered_characters);
}
