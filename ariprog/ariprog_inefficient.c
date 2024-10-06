/*
ID: angelqu1
TASK: ariprog
LANG: C
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TRUE 1
#define FALSE 0
#define MAX 250

int compare(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

typedef struct res {
    int first_element;
    int diff_sequences;
} response;

response res[10000];
int res_counter = 0;
int bisq_exists[2*MAX*MAX+1] = {0};

int dfs(int arr[], int m, int n, int i_idx, int j_idx, int nseq, int curr_seq) {
    if (n == curr_seq)
        return TRUE;

    for (int i = i_idx; i < m; i++) {
        // if (0 == arr[i+1] - arr[i]) { // Avoid repeated values
        //     ++j_idx;
        //     continue;
        // }
        for (int j = j_idx; j < m; j++) {
            // if (0 == arr[j+1] - arr[j]) // Avoid repeated values
            //     continue;
            if (1 == curr_seq) // Sequence number is assigned if there's none
                nseq = arr[j] - arr[i];

            // Compare former and latter sequences
            int is_seq = FALSE;
            if (nseq > arr[j] - arr[i])
                continue;
            else if (nseq < arr[j] - arr[i])
                return FALSE;
            else
                is_seq = dfs(arr, m, n, j, j+1, nseq, curr_seq+1);

            // If it matched, then save values
            if (is_seq) {
                if (1 == curr_seq) {
                    res[res_counter].first_element = arr[i];
                    res[res_counter++].diff_sequences = nseq;
                    // printf("%d %d\n", arr[i], nseq);
                }
                else
                    return TRUE;
            }
        } // j loop
    } // i loop
    return FALSE; // Avoid returning trash when loop is completed
}

int main(void) {
    clock_t start_time = clock();
    FILE *fin = fopen("ariprog.in", "r");
    FILE *fout = fopen("ariprog.out", "w");

    int n, m;
    fscanf(fin, "%d %d\n", &n, &m);

    // Bisquares array
    ++m; // Perdóndame, Dios. No conozco mejor
    int bisq[m*m+1];
    int c = 0; // counter
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < m; j++) {
            int value = i*i + j*j;
            if (!bisq_exists[value] || 0 == value) {
                bisq[c++] = value;
                bisq_exists[value] = 1;
            }
        }
    }

    // Sort
    qsort(bisq, c-1, sizeof(bisq[0]), compare);

    // Sorcery
    dfs(bisq, c-1, n, 0, 1, 0, 1);

    // It was already solved, but it's asked to return the values in a specific format :p (skill issue ig)
    // Me when bubble sort
    res[res_counter].first_element = -1;
    res[res_counter].diff_sequences = -1;
    for (int i = 0; res[i].first_element != -1; i++) {
        for (int j = i+1; res[j].first_element != -1; j++) {
            if (res[i].diff_sequences > res[j].diff_sequences ||
                (res[i].diff_sequences == res[j].diff_sequences &&
                res[i].first_element > res[j].first_element)) 
            {
                response temp;
                temp.first_element = res[i].first_element;
                temp.diff_sequences = res[i].diff_sequences;
                res[i].first_element = res[j].first_element;
                res[i].diff_sequences = res[j].diff_sequences;
                res[j].first_element = temp.first_element;
                res[j].diff_sequences = temp.diff_sequences;
            }
        }
    }

    int i = 0;
    for (; res[i].first_element != -1; i++)
        fprintf(fout, "%d %d\n", res[i].first_element, res[i].diff_sequences);
        // printf("%d %d\n", res[i].first_element, res[i].diff_sequences);
    if (0 == i)
        fprintf(fout, "%s\n", "NONE");

    // Garbage collectors
    fclose(fin);
    fclose(fout);

    // Stop the clock
    clock_t end_time = clock();

    // Calculate the elapsed time in seconds
    double time_taken = (double)(end_time - start_time) / CLOCKS_PER_SEC;

    printf("Time taken: %f seconds\n", time_taken);

    return 0;
}
