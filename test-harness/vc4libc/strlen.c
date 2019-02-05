unsigned int _strlen(const char *str) {
  int c = 0;
  char *w = str;
  for(;*w != 0; w++) c++;

  return c;
}
