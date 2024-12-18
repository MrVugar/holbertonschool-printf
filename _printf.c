#include "main.h"
#include <stdarg.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h> /* strlen funksiyası üçün */

/**
 * _printf - Custom printf function
 * @format: Format string
 *
 * Return: Number of characters printed
 */
int _printf(const char *format, ...)
{
    va_list args;
    int count = 0;

    if (!format)
        return (-1);

    va_start(args, format);
    while (*format)
    {
        if (*format == '%')
        {
            format++;
            switch (*format)
            {
            case 'c': /* Character */
            {
                char c = va_arg(args, int);
                count += write(1, &c, 1);
                break;
            }
            case 's': /* String */
            {
                char *str = va_arg(args, char *);
                if (!str)
                    str = "(null)";
                count += write(1, str, strlen(str));
                break;
            }
            case '%': /* Percent */
                count += write(1, "%", 1);
                break;
            case 'd':
            case 'i': /* Integer */
            {
                char buffer[50];
                int n = va_arg(args, int);
                snprintf(buffer, 50, "%d", n);
                count += write(1, buffer, strlen(buffer));
                break;
            }
            case 'u': /* Unsigned Integer */
            {
                char buffer[50];
                unsigned int n = va_arg(args, unsigned int);
                snprintf(buffer, 50, "%u", n);
                count += write(1, buffer, strlen(buffer));
                break;
            }
            case 'o': /* Octal */
            {
                char buffer[50];
                unsigned int n = va_arg(args, unsigned int);
                snprintf(buffer, 50, "%o", n);
                count += write(1, buffer, strlen(buffer));
                break;
            }
            case 'x': /* Hexadecimal (lowercase) */
            case 'X': /* Hexadecimal (uppercase) */
            {
                char buffer[50];
                unsigned int n = va_arg(args, unsigned int);
                snprintf(buffer, 50, (*format == 'x') ? "%x" : "%X", n);
                count += write(1, buffer, strlen(buffer));
                break;
            }
            case 'p': /* Pointer */
            {
                char buffer[50];
                void *ptr = va_arg(args, void *);
                snprintf(buffer, 50, "%p", ptr);
                count += write(1, buffer, strlen(buffer));
                break;
            }
            default: /* Unsupported format */
                count += write(1, "%", 1) + write(1, format, 1);
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
