#include <stdarg.h>
#include <unistd.h>

/**
 * _putchar - Writes a character to stdout
 * @c: The character to print
 * Return: On success 1, otherwise -1
 */
int _putchar(char c)
{
    return write(1, &c, 1);
}

/**
 * print_string - Prints a string to stdout
 * @str: The string to print
 * Return: Number of characters printed
 */
int print_string(char *str)
{
    int count = 0;

    if (!str)
        str = "(null)";
    while (*str)
    {
        _putchar(*str);
        str++;
        count++;
    }
    return count;
}

/**
 * print_number - Prints an integer to stdout
 * @n: The integer to print
 * Return: Number of characters printed
 */
int print_number(int n)
{
    unsigned int num;
    int count = 0;

    if (n < 0)
    {
        _putchar('-');
        count++;
        num = -n;
    }
    else
    {
        num = n;
    }
    if (num / 10)
        count += print_number(num / 10);
    _putchar((num % 10) + '0');
    count++;
    return count;
}

/**
 * _printf - Produces output according to a format
 * @format: Format string containing directives
 * Return: Number of characters printed
 */
int _printf(const char *format, ...)
{
    va_list args;
    int i, count = 0;

    if (!format)
        return (-1);

    va_start(args, format);
    for (i = 0; format[i]; i++)
    {
        if (format[i] == '%')
        {
            i++;
            if (format[i] == 'c')
                count += _putchar(va_arg(args, int));
            else if (format[i] == 's')
                count += print_string(va_arg(args, char *));
            else if (format[i] == 'd' || format[i] == 'i')
                count += print_number(va_arg(args, int));
            else if (format[i] == '%')
                count += _putchar('%');
            else
                count += _putchar(format[i]);
        }
        else
        {
            count += _putchar(format[i]);
        }
    }
    va_end(args);
    return count;
}
