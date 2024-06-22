/*
ID: angelqu1
LANG: C
TASK: transform
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

char** allocate_matrix(int n) {
  char **matrix = malloc(n * sizeof(char *));
  for (int i = 0; i < n; i++)
    matrix[i] = malloc(n * sizeof(char));
  return matrix;
}

void free_matrix(char **matrix, int n) {
  for (int i = 0; i < n; i++)
    free(matrix[i]);
  free(matrix);
}

void define_matrix_from_file(FILE *fin, char **matrix, int n) {
  for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++)
      fscanf(fin, " %c", &matrix[i][j]); // empty space before %c to avoid enters and blankspaces
}

void print_out_matrix(char **matrix, int n) {
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++)
      printf("%c", matrix[i][j]);
    printf("\n");
  }
}

bool is_matrix_equal(char **matrix, char **expected_matrix, int n) {
  for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++)
      if (matrix[i][j] != expected_matrix[i][j])
        return false;
  return true;
}

void rotate_matrix(char **matrix, int n) { // -90 degrees :p because we working with reflect
  char **rotated_matrix = allocate_matrix(n);
  for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++)
      rotated_matrix[j][n-1-i] = matrix[i][j];

  for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++)
      matrix[i][j] = rotated_matrix[i][j];
  free_matrix(rotated_matrix, n);
}

void reflect_matrix(char **matrix, int n) {
  char **reflected_matrix = allocate_matrix(n);
  for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++)
      reflected_matrix[i][n-1-j] = matrix[i][j];

  for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++)
      matrix[i][j] = reflected_matrix[i][j];
  free_matrix(reflected_matrix, n);
}

int get_transformation(char **matrix, char **expected_matrix, int n) {
  int lowest_tranformation = 7; // defualt value, value not found

  // if they're in the beggining, then 6
  if (is_matrix_equal(matrix, expected_matrix, n))
    lowest_tranformation = 6;

  int rotations = 0;
  for (int i = 0; i < n; i++) {
    reflect_matrix(matrix, n);
    if (is_matrix_equal(matrix, expected_matrix, n))
      if (lowest_tranformation > 4 && rotations == 0)
        lowest_tranformation = 4;
 
    rotate_matrix(matrix, n);
    ++rotations;
    if (is_matrix_equal(matrix, expected_matrix, n))
      if (lowest_tranformation > 5)
        lowest_tranformation = 5; // reflect and rotation applied, then combination

    reflect_matrix(matrix, n); // went back to normal, only rotation
    if (is_matrix_equal(matrix, expected_matrix, n))
      if (lowest_tranformation > rotations)
        lowest_tranformation = rotations; // reflect and rotation applied, then combination
  }
  return lowest_tranformation; // if lowst_tra is 0, then pattern not found
}

int main() {
  FILE *fin = fopen("transform.in", "r");
  FILE *fout = fopen("transform.out", "w");
  int n;

  // matrix n
  fscanf(fin, "%d", &n); 

  // matrix declaration and definition
  char **matrix = allocate_matrix(n);
  char **expected_matrix = allocate_matrix(n);
  define_matrix_from_file(fin, matrix, n);
  define_matrix_from_file(fin, expected_matrix, n);

  // debug
  // print_out_matrix(matrix, n);
  // printf("============\n");
  // print_out_matrix(expected_matrix, n);
  // printf("============\n");
  // reflect_matrix(matrix, n);
  // rotate_matrix(matrix, n);
  // print_out_matrix(matrix, n);

  // logic
  int transformation = get_transformation(matrix, expected_matrix, n);

  // output
  fprintf(fout, "%d\n", transformation);

  // free mem
  free_matrix(matrix, n);
  free_matrix(expected_matrix, n);

  // close vars
  fclose(fin);
  fclose(fout);
  return 0;
}
