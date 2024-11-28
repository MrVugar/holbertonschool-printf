#include "main.h"
#include <stdarg.h>
#include <unistd.h>

/**
 * _printf - produces output according to a format
 * @format: format string
 *
 * Return: number of characters printed (excluding null byte)
 */
int _printf(const char *format, ...)
{
    va_list args;
    int i = 0, count = 0;

    if (!format)
        return (-1);

    va_start(args, format);
    while (format[i])
    {
        if (format[i] == '%')
        {
            i++;
            count += handle_specifier(format[i], args);
        }
        else
        {
            count += write(1, &format[i], 1);
        }
        i++;
    }
    va_end(args);
    return (count);
}

/**
 * handle_specifier - handles specifiers for _printf
 * @specifier: the format specifier
 * @args: arguments list
 *
 * Return: number of characters printed
 */
int handle_specifier(char specifier, va_list args)
{
    char ch, *str;
    int num;

    switch (specifier)
    {
        case 'c':
            ch = va_arg(args, int);
            return (write(1, &ch, 1));
        case 's':
            str = va_arg(args, char *);
            if (!str)
                str = "(null)";
            return (write(1, str, _strlen(str)));
        case '%':
            return (write(1, "%", 1));
        case 'd':
        case 'i':
            num = va_arg(args, int);
            return (print_number(num));
        default:
            write(1, "%", 1);
            return (write(1, &specifier, 1));
    }
}

/**
 * print_number - prints an integer
 * @n: integer to print
 *
 * Return: number of characters printed
 */
int print_number(int n)
{
    unsigned int num;
    int count = 0;
    char digit;

    if (n < 0)
    {
        count += write(1, "-", 1);
        num = -n;
    }
    else
    {
        num = n;
    }

    if (num / 10)
        count += print_number(num / 10);

    digit = (num % 10) + '0';
    count += write(1, &digit, 1);

    return (count);
}

/**
 * _strlen - calculates the length of a string
 * @str: the string
 *
 * Return: length of the string
 */
int _strlen(char *str)
{
    int len = 0;

    while (str[len])
        len++;
    return (len);
}

