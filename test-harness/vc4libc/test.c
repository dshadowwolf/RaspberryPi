#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void main() {
  int z = 127;
  char *y = "127", *x = y;
  int w = 0;

  /*
    char n = *(fmt+1);
    if(n >= '1' && n <= '9') {
    //field width
    fmt++;
    int p = -1;
    while(n >= '0' && n <= '9') {
    fmt_width = fmt_width + ((n - '0') * __exp10(++p));
    putc(n);
    n = *(fmt++);
    }
    fmt--;
    }
  */

  while(*x) {
    char n = *x, next = *(x+1);
    w += (n - '0');
    if(next >= '0' && next <= '9')
      w *= 10;
    x++;
  }

  printf("z == %u\ny == %s\nx == %p\nw == %u\n", z, y, x, w);

  char *t = "a%016xzb";
  while(*t) {
    if(*t != '%') {
      printf("%c\n", *t);
      t++;
    } else {
      int u = 0;
      char v;
      t++;
      switch(*t) {
      case '0':
	{
	  char n = *(t+1);
	  if(n >= '1' && n <= '9') {
	    printf("---\n");
	    t++;
	    while(n >= '0' && n <= '9') {
	      printf("n == %c (u == %u)\n", n, u);
	      u += (n - '0');
	      t++;
	      n = *t;
	      if(n >= '0' && n <= '9') u *= 10;
	    }
	    printf("---\n");
	    printf("width - %u - n is %c, t is %p (*t == \'%c\')\n", u, n, t, *t);
	  }
	}
	break;
      default:
	printf("char is %c\n", *t);
	t++;
      }
    }
  }
}
