#include "stdint.h"
#include <hardware.h>
#include <bcm2708_chip/aux_io.h>

static void _putchar(int c) {
  if( c == '\n' )
    putchar('\r');

  HW_REGISTER_RW(AUX_MU_IO_REG) = c;
}

static void _puts(const char *s) {
  char *w = s;

  while(*w != '\0') {
    putchar(*w);
    w++;
  }
}

void putc(int c) {
  _putchar(c);
}

void write(const char *buff) {
  _puts(buff);
}

