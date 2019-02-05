/*#include "include/stdint.h"
#include "include/stdlib.h"
#include "include/sys.h"*/
#include "include/stdargs.h"

extern int putchar(int);
extern int strlen(char *);

void putc(int c) {
  putchar(c);
}

void puts(char *ch) {
  while(*ch)
    putc(*(ch++));
}

#define PARSE_NTOA_UC      1
#define PARSE_RIGHT_ALIGN  2
#define PARSE_SIGN_BIT     4
#define PARSE_ONLY_ASCII   8

static void format_int(unsigned int val,
		       unsigned int radix,
		       unsigned int flags,
		       unsigned int prec) {
  char buffer[35];
  for(int c = 0; c < 35; c++) buffer[c] = 0;

  if(flags & PARSE_RIGHT_ALIGN)
    for(int a = 0; a < prec; a++) buffer[a] = '0';

  unsigned int work_val = val;
  unsigned int pos = 0;
  
  while(work_val > 0) {
    const unsigned char digit = work_val % radix;
    work_val /= radix;
    buffer[pos++] =  ((digit < 10)?(digit + '0'):(((flags & PARSE_NTOA_UC)?'A':'a') + digit - 10));
  }

  if(flags&PARSE_SIGN_BIT) {
    if(prec > 0 && prec < 31) {
      pos = prec+1;
    }
    buffer[pos] =  val < 0 ? '-' : '+';
  }

  if(flags&PARSE_RIGHT_ALIGN) pos = prec;
  
  for(int z = (pos-1); z >= 0 && buffer[z] != 0; z--) putc(buffer[z]);
}

static void format_string(const char *s, unsigned int flags, unsigned int width) {
  unsigned int len = strlen(s);
  if(flags&PARSE_RIGHT_ALIGN && width > len)
    for(int a = 0; a < (width - len); a++) putc(' ');
  
  puts(s);
}

static void format_char(const char ch, unsigned int flags, unsigned int width) {
  if(flags&PARSE_RIGHT_ALIGN && width > 1)
    for(int a = 0; a < (width - 1); a++) putc(' ');

  if((ch < ' ' || ch >= 127) && (flags&PARSE_ONLY_ASCII)) putc('?');
  else putc(ch);
}

static void format_pointer(const void *pointer, unsigned int flags, unsigned int width) {
  putc('0');
  putc('x');
  format_int((unsigned int)pointer, 16, PARSE_NTOA_UC, width);
}

void va_printf(const char *fmt, va_list args) {
  unsigned int flags, fmt_width, int_parm;
  char char_parm;
  char *str_parm;

  const char *save = fmt;

  while(*fmt) {
    if(*fmt != '%') {
      format_char(*fmt,0,0);
      fmt++;
      continue;
    } else {
      flags = 0;
      fmt_width = 0;
      int fmt_end = 0;
      while(!fmt_end && *fmt) {
	fmt++;
	switch(*fmt) {
	  // next char is '+', '0', a non-zero digit, or a format specifier
	  // each has different handling.
	case '+':
	  flags |= PARSE_SIGN_BIT;
	  break;
	case '0':
	  flags |= PARSE_RIGHT_ALIGN;
	  char n = *(fmt+1);
	  if(n >= '1' && n <= '9') {
	    fmt++;
	    //field width
	    int p = -1;
	    while(n >= '0' && n <= '9') {
	      fmt_width += (n - '0');
	      fmt++;
	      n = *fmt;
	      if(n >= '0' && n <= '9') fmt_width *= 10;
	    }
	    fmt--;
	  }
	  break;
	case 'X':
	  flags |= PARSE_NTOA_UC;
	case 'x':
	  format_int((unsigned int)va_arg(args, unsigned int), 16, flags, fmt_width);
	  fmt_end = 1;
	  fmt++;
	  break;
	case 'o':
	  format_int((unsigned int)va_arg(args, unsigned int),  8, flags, fmt_width);
	  fmt_end = 1;
	  fmt++;
	  break;
	case 'u':
	case 'd':
	  format_int((unsigned int)va_arg(args, unsigned int), 10, flags, fmt_width);
	  fmt_end = 1;
	  fmt++;
	  break;
	case 'b':
	  format_int((unsigned int)va_arg(args, unsigned int),  2, flags, fmt_width);
	  fmt_end = 1;
	  fmt++;
	  break;
	case 's':
	  format_string((char *)va_arg(args, char *), flags, fmt_width);
	  fmt_end = 1;
	  fmt++;
	  break;
	case 'c':
	  format_char((int)va_arg(args, int), flags, fmt_width);
	  fmt_end = 1;
	  fmt++;
	  break;
	case 'p':
	  format_pointer((void *)va_arg(args, void *), flags, fmt_width);
	  fmt_end = 1;
	  fmt++;
	  break;
	case 0:
	  puts("END OF STRING IN FORMAT SPECIFIER!");
	  fmt_end = 1;
	  fmt++;
	  return;
	default:
	  format_char(*fmt, flags, fmt_width);
	  fmt_end = 1;
	  fmt++;
	}
      }
    }
  }
}

void printf(const char *fmt, ...) {
  va_list ap;
  va_start(ap, fmt);
  va_printf(fmt, ap);
  va_end(ap);
}

void main() {
  printf("test (decimal)        %u == 65535\n", 65535);
  printf("test (hex, lowercase) %x == 7fff\n", 32767);
  printf("test (hex, uppercase) %X == 7FFF\n", 32767);
  printf("test (octal)          %o == 777\n", 511);
  printf("test (binary?)        10100101101001011010010110100101 == %b\n", 0xA5A5A5A5);
  printf("test field width      %016X == 00000000DEADBEEF\n", 0xDEADBEEF);
  printf("string test      \"Testing\" == \"%s\"\n", "Testing");
  printf("string, field  \"  Testing\" == \"%09s\"\n", "Testing");
  printf("pointer: %p\n", printf);
  printf("character  \'A\' == \'%c\'\n", 'A');
  printf("character, field '    A' == '%05c'\n", 'A');
}
