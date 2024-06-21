/*
ID: angelqu1
LANG: C
TASK: milk2
*/

// errors found and fixed
  // bubble sort didn't exchange the whole struct, but the single element, hence mixing diff structs up
  // single element array created a non-continous value even tho there wasn't any, so added a condition that validated value existed
  // didn't assign values for the both values intervals, beggining and ending, which made calculations not add up

#include <stdio.h>

struct interval {
  int beg;
  int end;
};

void bubble_sort_intervals(struct interval *intervals, int size) {
  for (int i = 0; i < size-1; i++) {
    for (int j = i+1; j < size; j++) {
      if (intervals[i].beg > intervals[j].beg) {
        struct interval temp = intervals[i];
        intervals[i] = intervals[j];
        intervals[j] = temp;
      }
    }
  }
}

void print_out(struct interval *intervals, int size) {
  printf("===================\n");
  for (int i = 0; i < size; i++) 
    printf("%d %d\n", intervals[i].beg, intervals[i].end);
  printf("===================\n");
}

int main() {
  // file input and output declaration
  FILE *fin = fopen("milk2.in", "r");
  FILE *fout = fopen("milk2.out", "w");

  // obtain length
  int arr_size;
  fscanf(fin, "%d", &arr_size);

  // save all values from input file
  struct interval intervals[arr_size];
  for (int i = 0; i < arr_size; i++)
    fscanf(fin, "%d%d", &intervals[i].beg, &intervals[i].end);

  // sort elements
  bubble_sort_intervals(intervals, arr_size);
  // print_out(intervals, arr_size);

  // logic
  int curr_beg_continous = 0, curr_end_continous = 0;
  int largest_beg_continous = 0, largest_end_continous = 0;
  int largest_beg_not_continous = 0, largest_end_not_continous = 0;
  int reset = 0;

  int largest_continous_time = 0;
  int largest_not_continous_time = 0;

  for (int i = 0; i < arr_size; i++) {
    if (intervals[i].beg > curr_end_continous && curr_end_continous != 0) { // not continuity found
      reset = 1; // new continuity will come up
      largest_not_continous_time = largest_end_not_continous - largest_beg_not_continous;
      // printf("Not continuity found: %d\n", largest_not_continous_time);
      int current_not_continous_time = intervals[i].beg - curr_end_continous;
      if (current_not_continous_time > largest_not_continous_time) { // if new not continuity bigger than current largest, then replace
        largest_beg_not_continous = curr_end_continous;
        largest_end_not_continous = intervals[i].beg;
        largest_not_continous_time = current_not_continous_time;
      } 
    }
      
    if (curr_beg_continous == 0 || reset) {
      curr_beg_continous = intervals[i].beg; 
      curr_end_continous = intervals[i].end;
      reset = 0; // only first iteration of a continuity will be assigned to beg
    }
    if (intervals[i].end > curr_end_continous) // length is added
      curr_end_continous = intervals[i].end;


    // if current continous time bigger than largest, then replace
    int current_continous_time = curr_end_continous - curr_beg_continous;
    largest_continous_time = largest_end_continous - largest_beg_continous;
    if (current_continous_time > largest_continous_time) {
      largest_beg_continous = curr_beg_continous;
      largest_end_continous = curr_end_continous;
      largest_continous_time = current_continous_time;
    }
  }

  // print out results
  fprintf(fout, "%d %d\n", largest_continous_time, largest_not_continous_time);

  // close pointers
  fclose(fin);
  fclose(fout);
  return 0;
}
