/*
ID: angelqu1
LANG: C
TASK: namenum
*/

#include <stdio.h>
#include <string.h>

typedef struct {
  int num;
  char value[3];
} lookup_table;

lookup_table dictionary[] = {
  {2, "ABC"},
  {3, "DEF"},
  {4, "GHI"},
  {5, "JKL"},
  {6, "MNO"},
  {7, "PRS"},
  {8, "TUV"},
  {9, "WXY"},
};

int is_valid_name(char *name, char *number, int len) {
  for (int i = 0; i < len; i++) {
    int num = number[i] - '0'; // char to int
    int match_found = 0;

    for (int j = 0; j < 8; j++) {
      if (num == dictionary[j].num) {
        for (int k = 0; k < 3; k++) {
          if (name[i] == dictionary[j].value[k]) {
            match_found = 1;
            break;
          }
        }
        break;
      }
    }
    if (!match_found) return 0;
  }
  return 1;
}

int main() {
  FILE *dict = fopen("dict.txt", "r");
  FILE *fin = fopen("namenum.in", "r");
  FILE *fout = fopen("namenum.out", "w");

  char number[12];
  int len;

  // grab values from fin file
  fscanf(fin, "%s", number);
  len = strlen(number);

  // grab values from dict that are equal in length to nums
  char name[12];
  int flag = 0;
  while (fscanf(dict, "%s", name) != EOF)
  {
    if (strlen(name) == len)
    {
      if (is_valid_name(name, number, len)) {
        fprintf(fout, "%s\n", name);
        flag = 1;
      }
    }
  }

  // save none if it's empty
  if (!flag)
    fprintf(fout, "%s\n", "NONE");

  return 0;
}