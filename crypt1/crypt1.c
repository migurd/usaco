/*
ID: angelqu1
TASK: crypt1
LANG: C
*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#define TRUE 1
#define FALSE 0

typedef struct {
  int index;
  int value;
} factor;

int getnperms(int n[], int nlen, int nfields) { // overkill, simple mult could've been done here
  if (nfields == 0)
    return 1;
  return nlen * getnperms(n, nlen, nfields-1);
}

void increment_index(factor *s, int slen, int *arr, int nmax) {
  for (int i = slen-1; i >= 0; i--) {
    if (s[i].index == nmax - 1) {
      s[i].index = 0;
      s[i].value = arr[0];
      continue;
    }
    ++s[i].index;
    s[i].value = arr[s[i].index];
    return;
  }
}

int * inttoarr(int n) {
  int number = n;
  int c = 0;
  while (number != 0) {
    number /= 10;
    ++c; 
  }

  int * arr = (int *)malloc(c * sizeof(int));
  number = n;
  for (int i = c-1; number != 0; i--) {
    arr[i] = number % 10;
    number /= 10;
  }

  return arr;
}

int contains(int * narr, int narrlen, int res, int reslen) {
  int * resarr = inttoarr(res);

  for (int i = 0; i < reslen; i++) {
    int counter = 0;
    for (int j = 0; j < narrlen; j++) {
      if (resarr[i] != narr[j])
        ++counter;
      else
        break;
    }
    if (counter == narrlen) {
      free(resarr);
      return FALSE;
    }
  }
  free(resarr);
  return TRUE;
}

int main() {
  FILE * fin = fopen("crypt1.in", "r");
  FILE * fout = fopen("crypt1.out", "w");
  int sum = 0;

  assert(fin != NULL && fout != NULL);

  int nmax;
  fscanf(fin, "%d\n", &nmax);

  int narr[nmax];
  for (int i = 0; fscanf(fin, "%d\n", &narr[i]) != EOF; i++)
    ;

  int twoperm = getnperms(narr, nmax, 2);
  int threeperm = getnperms(narr, nmax, 3);
  
  // declaration and initialization for first factor
  factor f[3];
  for (int i = 0; i < 3; i++) {
    f[i].index = 0;
    f[i].value = narr[0];
  }

  // printf("%d", threeperm);
  for (int i = 0; i < threeperm; i++) {
    // declaration and initialization for second factor
    factor s[2];
    for (int j = 0; j < 2; j++) {
      s[j].index = 0;
      s[j].value = narr[0];
    }

    int p1, p2;
    p1 = f[0].value * 100 + f[1].value * 10 + f[2].value;
    for (int j = 0; j < twoperm; j++) {
      int flag = TRUE;
      p2 = s[0].value * 10 + s[1].value;

      int res1 = p1 * s[1].value;
      int res2 = p1 * s[0].value;
      int fres = res1 + res2 * 10;
      if (res1 >= 1000 || res2 >= 1000 || fres >= 10000) {
        flag = FALSE;
      } else if (!contains(narr, nmax, res1, 3) || !contains(narr, nmax, res2, 3) || !contains(narr, nmax, fres, 4)) {
        flag = FALSE;
      } else if (fres != (p1 * p2)) {
        flag = FALSE;
      }
      
      if (flag)
        ++sum;
      increment_index(s, 2, narr, nmax);
    }
    increment_index(f, 3, narr, nmax);
  }

  printf("%d\n", sum);
  fprintf(fout, "%d\n", sum);
  return 0;
}
