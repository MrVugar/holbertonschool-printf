#ifndef MAIN_H
#define MAIN_H

#include <stdarg.h>
#include <unistd.h>

int _printf(const char *format, ...);
void print_number(int n);
void print_unsigned(unsigned int n, int base, int uppercase);

#endif
