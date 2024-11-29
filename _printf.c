#include "main.h"

void print_number(int n)
{
    char c;

    if (n < 0)
    {
        write(1, "-", 1);
        n = -n;
    }
    if (n / 10)
        print_number(n / 10);

    c = n % 10 + '0';
    write(1, &c, 1);
}

void print_unsigned(unsigned int n, int base, int uppercase)
{
    char *digits = uppercase ? "0123456789ABCDEF" : "0123456789abcdef";
    char c;

    if (n / base)
        print_unsigned(n / base, base, uppercase);

    c = digits[n % base];
    write(1, &c, 1);
}

int _printf(const char *format, ...)
{
    int count = 0;
    va_list args;

    if (!format)
        return (-1);

    va_start(args, format);

    while (*format)
    {
        if (*format == '%' && *(format + 1))
        {
            format++;
            if (*format == 'c')
            {
                char c = (char)va_arg(args, int);
                count += write(1, &c, 1);
            }
            else if (*format == 's')
            {
                char *str = va_arg(args, char *);
                if (!str)
                    str = "(null)";
                while (*str)
                    count += write(1, str++, 1);
            }
            else if (*format == 'd' || *format == 'i')
            {
                int n = va_arg(args, int);
                print_number(n);
            }
            else if (*format == 'u')
            {
                unsigned int n = va_arg(args, unsigned int);
                print_unsigned(n, 10, 0);
            }
            else if (*format == 'o')
            {
                unsigned int n = va_arg(args, unsigned int);
                print_unsigned(n, 8, 0);
            }
            else if (*format == 'x' || *format == 'X')
            {
                unsigned int n = va_arg(args, unsigned int);
                print_unsigned(n, 16, *format == 'X');
            }
            else if (*format == 'p')
            {
                void *addr = va_arg(args, void *);
                write(1, "0x", 2);
                print_unsigned((unsigned long)addr, 16, 0);
            }
            else if (*format == '%')
            {
                count += write(1, "%", 1);
            }
            else
            {
                write(1, "%", 1);
                write(1, format, 1);
            }
        }
        else
        {
            count += write(1, format, 1);
        }
        format++;
    }

    va_end(args);
    return (count);
}
