#ifndef MAIN_H
#define MAIN_H
#include <stdarg.h>
#include <stdio.h>
#include <unistd.h>

#define OPEN(x) (void)(x)
#define BUFA_SIZE 1024

/* marks */
#define _MINUS 1
#define _PLUS 2
#define _ZERO 4
#define _HASH 8
#define _SPACE 16

/* SIZES */
#define LONG_SIZE 2
#define SHORT_SIZE 1

/**
 * struct form - Struct op
 *
 * @form: The format.
 * @func: The function associated.
 */
struct form
{
	char form;
	int (*func)(va_list, char[], int, int, int, int);
};


/**
 * typedef struct form form_t - Struct op
 *
 * @form: The format.
 * @fm_t: The function associated.
 */
typedef struct form form_t;

int _printf(const char *format, ...);
int con_out(const char *form, int *i, va_list list, char buffer[],
	int marks, int width, int accuraci, int size);

/****************** FUNCTIONS ******************/
/*print chars and strings*/
int output_characters(va_list types, char buffer[],
	int marks, int width, int accuraci, int size);
int output_string(va_list types, char buffer[],
	int marks, int width, int accuraci, int size);
int output_percent(va_list types, char buffer[],
	int marks, int width, int accuraci, int size);

/*print numbers in different format*/
int out_int(va_list types, char buffer[],
	int marks, int width, int accuraci, int size);
int out_bin(va_list types, char buffer[],
	int marks, int width, int accuraci, int size);
int out_unsign(va_list types, char buffer[],
	int marks, int width, int accuraci, int size);
int out_oct(va_list types, char buffer[],
	int marks, int width, int accuraci, int size);
int out_hexa(va_list types, char buffer[],
	int marks, int width, int accuraci, int size);
int out_hexa_upper(va_list types, char buffer[],
	int marks, int width, int accuraci, int size);

int print_hexa(va_list types, char hex_table[],
char buffer[], int marks, char flag_ch, int width, int accuraci, int size);

/*print non printable */
int out_unprintable(va_list types, char buffer[],
	int marks, int width, int accuraci, int size);

/*print memory address*/
int print_pointer(va_list types, char buffer[],
	int marks, int width, int accuraci, int size);

/*handle other specifiers*/
int _flags(const char *format, int *i);
int _width(const char *format, int *i, va_list list);
int _accuracy(const char *format, int *i, va_list list);
int _size(const char *format, int *i);

/*print string in reverse*/
int _reverse(va_list types, char buffer[],
	int marks, int width, int accuraci, int size);

/*print a string in rot 13*/
int _rot13(va_list types, char buffer[],
	int marks, int width, int accuraci, int size);

/* width handler*/
int handle_char(char c, char buffer[], int marks,
	int width, int accuraci, int size);
int handle_number(int _isPlus, int iNdex, char buffer[],
	int marks, int width, int accuraci, int size);
int handle_nums(int iNdex, char bff[], int marks,
	int width, int accuraci, int length, char padd, char extra_c);
int handle_pointer(char buffer[], int iNdex, int length,
	int width, int marks, char padd, char extra_c, int padd_start);
int handle_unsigned(int _isMinus, int iNdex, char buffer[],
	int marks, int width, int accuraci, int size);


int _isprintable(char);
int insert_hexa(char, char[], int);
int _isdigit(char);

long int change_size(long int num, int size);
long int size_converter(unsigned long int num, int size);

#endif /* MAIN_H */
