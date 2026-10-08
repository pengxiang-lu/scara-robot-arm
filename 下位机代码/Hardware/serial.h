#ifndef __SERIAL_H_
#define __SERIAL_H_
#include <stdio.h>
#include <stdarg.h>
#include <stdint.h>
void computer_serial_init(void);
int fputc(int ch, FILE *f);
#endif

