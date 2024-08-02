/*
ID: angelqu1
TASK: combo
LANG: C
*/

#include <stdio.h>
#include <assert.h>

#define TRUE 1
#define FALSE 0
#define COMBO_LENGTH 3

int mod (int a, int top) {
  int r = a % top;
  return r <= 0 ? r + top : r;
}
int modular_difference(int a, int b, unsigned int top) {
  int left = mod(a, top);
  int right = mod(a, top);
  int c = 0;

  if (a == b)
    return 0;

  for (int i = 0; i <= 3; i++) {
    if (left == b)
      return c;
    if (right == b)
      return c;
    left = mod(left - 1, top);
    right = mod(right + 1, top);
    ++c;
  }
  return 100;
}

int is_combination_valid(int *pass1, int *pass2, int *pass_tried, int top) {
  int flag_pass1 = TRUE;
  int flag_pass2 = TRUE;

  for (int i = 0; i < COMBO_LENGTH; i++) {
    if (modular_difference(pass_tried[i], pass1[i], top) > 2)
      flag_pass1 = FALSE;
    if (modular_difference(pass_tried[i], pass2[i], top) > 2)
      flag_pass2 = FALSE;
    // if (pass_tried[0] == 2)
    //   printf("a: %d\tb: %d\tc: %d\n", modular_difference(pass_tried[i], pass2[i], top), pass_tried[i], pass2[i]);
  }
  if (!flag_pass1 && !flag_pass2)
    return FALSE;
  // for (int i = 0; i < COMBO_LENGTH; i++)
  //   printf("%d,", pass_tried[i]);
  // printf("\n");
  // exit(0);
  return TRUE;
}

int main() {
  FILE *fin = fopen("combo.in", "r");
  FILE *fout = fopen("combo.out", "w");

  assert(fin != NULL && fout != NULL);

  int n = 0;
  int fc[COMBO_LENGTH]; // farmer combo
  int ac[COMBO_LENGTH]; // admin combo
  int combinations = 0;

  fscanf(fin, "%d\n", &n);
  fscanf(fin, "%d %d %d\n", &fc[0], &fc[1], &fc[2]);
  fscanf(fin, "%d %d %d\n", &ac[0], &ac[1], &ac[2]);

  int current_combination[COMBO_LENGTH];
  for (int i = n; i >= 1; i--) {
    current_combination[0] = i;
    for (int j = n; j >= 1; j--) {
      current_combination[1] = j;
      for (int k = n; k >= 1; k--) {
        current_combination[2] = k;
        if (is_combination_valid(fc, ac, current_combination, n))
          ++combinations;
      }
    }
  }

  printf("%d\n", combinations);
  fprintf(fout, "%d\n", combinations);

  fclose(fin);
  fclose(fout);
  return 0;
}
