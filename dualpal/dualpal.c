/*
ID: angelqu1
TASK: dualpal
LANG: C
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0

char* to_base(int n, int b) {
  char *v = (char *) malloc(33);
  int index = 32;

  v[--index] = '\0'; // EOF

  while (n > 0) {
    v[--index] = '0' + n % b; // int to char
    n /= b;
  }

  char *new_value = (char *) malloc(32 - index);
  for (int i = 0; i < 32 - index; i++)
    new_value[i] = v[index+i];
  free(v);

  return new_value; // from idx til EOF
}

int is_palindrome(char* word, int len) {
  for (int i = 0; i < len / 2; i++) {
    if (word[i] != word[len-i-1])
      return FALSE;
  }
  return TRUE;
}

int main() {
  FILE *fin = fopen("dualpal.in", "r");
  FILE *fout = fopen("dualpal.out", "w");

  int n, s;

  fscanf(fin, "%d %d", &n, &s);

  // from s+1 to s+n
  for (int i = s+1; n > 0; i++) {
    int counter = 0;
    for (int j = 2; j <= 10; j++) {
      char* bn = to_base(i, j); // based number :p
      // printf("%s\n", bn);
      if (is_palindrome(bn, strlen(bn)))
        ++counter;
      free(bn); // delete from start of mem address
      if (counter >= 2) { // if 2 or more bases of the same number are palindrome, then save number
        fprintf(fout, "%d\n", i);
        --n;
        break;
      }
    }
  }

  fclose(fin);
  fclose(fout);

  return 0;
}
