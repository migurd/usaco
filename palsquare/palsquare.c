/*
ID: angelqu1
TASK: palsquare
LANG: C
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int integer_to_char(int n) {
  if (n < 10) return n + '0';
  else if (n <= 20) return 'A' + n - 10;
  return -1;
}

char* to_base(int n, int base) {
  char *res = (char*)malloc(33);

  res[32] = '\0'; // finish, str ends
  int index = 31;

  while(n >= base) {
    res[index--] = integer_to_char(n % base);
    n /= base;
  }
  res[index] = integer_to_char(n % base);

  return &res[index]; // pointer from idx + 1 is sent
}

int is_palindrome(char *word) {
  int size = 0;
  for (; word[size] != '\0'; size++) // word len
    ;

  for (int i = 0; i < size / 2; i++) {
    if (word[i] != word[size-i-1])
      return 0;
  }
  return 1;
}

int main() {
  FILE *fin = fopen("palsquare.in", "r");
  FILE *fout = fopen("palsquare.out", "w");
  int base;
  fscanf(fin, "%d", &base);

  for (int n = 1; n <= 300; n++)
  {
    char *result = to_base(n*n, base);
    if (is_palindrome(result))
      fprintf(fout, "%s %s\n", to_base(n, base), result);
    free(result - (32 - strlen(result)));
  }
  fclose(fin);
  fclose(fout);
}
