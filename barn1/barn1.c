/*
TASK: barn1
ID: angelqu1
LANG: C
*/

#include <stdio.h>

typedef struct {
  int index;
  int value;
} stall;

int main() {
  int m, s, c;
  FILE * fin = fopen("barn1.in", "r");
  FILE * fout = fopen("barn1.out", "w");

  fscanf(fin, "%d %d %d\n", &m, &s, &c);

  int sa[c]; // stalls array
  for (int i = 0; fscanf(fin, "%d\n", &sa[i]) != EOF; i++)
    ;

  // sort values received because for some DAMN reason some of them are not already sorted
  for (int i = 0; i < c; i++) {
    for (int j = i+1; j < c; j++) {
      if (sa[i] > sa[j]) {
        // will start using a temp var instead of this next time. XD
        sa[i] += sa[j]; // i = i+j
        sa[j] = sa[i] - sa[j]; // j = i+j-j = i
        sa[i] = sa[i] - sa[j]; // i = i+j-i = j
      }
    }
  }
  // for (int i = 0; i < c; i++)
  //   printf("%d\n", sa[i]);

  stall intervals[c-1];
  for (int i = 0; i < c-1; i++) {
    intervals[i].index = i;
    intervals[i].value = sa[i+1] - sa[i];
  }

  // sort intervals by biggest to smallest
  for (int i = 0; i < c-1; i++) {
    for (int j = i+1; j < c-1; j++) {
      if (intervals[i].value < intervals[j].value) {
        intervals[i].value += intervals[j].value; // i = i+j
        intervals[j].value = intervals[i].value - intervals[j].value; // j = i+j-j = i
        intervals[i].value = intervals[i].value - intervals[j].value; // i = i+j-i = j

        intervals[i].index += intervals[j].index; // i = i+j
        intervals[j].index = intervals[i].index - intervals[j].index; // j = i+j-j = i
        intervals[i].index = intervals[i].index - intervals[j].index; // i = i+j-i = j
      }
    }
  }

  // sort first m (maximum number of boards) indexes
  if (m > c) m = c;
  for (int i = 0; i < m-1; i++) {
    for (int j = i+1; j < m-1; j++) {
      if (intervals[i].index > intervals[j].index) {
        intervals[i].value += intervals[j].value; // i = i+j
        intervals[j].value = intervals[i].value - intervals[j].value; // j = i+j-j = i
        intervals[i].value = intervals[i].value - intervals[j].value; // i = i+j-i = j

        intervals[i].index += intervals[j].index; // i = i+j
        intervals[j].index = intervals[i].index - intervals[j].index; // j = i+j-j = i
        intervals[i].index = intervals[i].index - intervals[j].index; // i = i+j-i = j
      }
    }
  }

  // for (int i = 0; i < c-1; i++) {
  //   printf("\t%d\t%d\t%d\n", i, intervals[i].index, intervals[i].value);
  // }

  int sum = 0;
  int current_index = 0;
  // printf("**************\n");
  for (int i = 0; i < m-1; i++) {
    // printf("\t%d\t%d-%d\n", sum, sa[current_index], sa[intervals[i].index]);
    sum += sa[intervals[i].index] - sa[current_index];
    current_index = intervals[i].index + 1;
  }
  sum += sa[c-1] - sa[current_index];
  sum += m; // since it's an interval, take into account the borders

  // printf("%d\n", sum);
  fprintf(fout, "%d\n", sum);

  return 0;
}
