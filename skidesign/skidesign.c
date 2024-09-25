/*
TASK: skidesign
ID: angelqu1
LANG: C
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define MAX_N 1000

int nhills;
int hills[MAX_N];
int hills_cost[MAX_N];
int min_cost = INT_MAX;
int counter = 0;

int compare(const void* a, const void* b) { // Oh, boy. I'd wish to understand qsort properly
    return (*(int*)a - *(int*)b);
}

int calculate_cost(int arr_cost[]) {
    int sum = 0;
    for (int i = 0; i < nhills; i++) {
        // printf("%d ", arr_cost[i]);
        sum += arr_cost[i] * arr_cost[i];
    }
    // printf("\n");

    return sum;
}

void dfs(int arr[], int arr_cost[]) {
    if (arr[nhills-1] - arr[0] > 17) {
        int arr_copy[nhills];
        int arr_cost_copy[nhills];
        memcpy(arr_copy, arr, sizeof(int) * nhills);
        memcpy(arr_cost_copy, arr_cost, sizeof(int) * nhills);

        int i = 0;
        while (1) {
            ++arr_copy[i];
            ++arr_cost_copy[i];
            // If iter got to the last iteration, finish cycle
            if (i == nhills-1)
                break;
            // If we surpassed the next value, we need to also bump it up too
            if (arr_copy[i] > arr_copy[i+1])
                ++i;
            else
                break;
        }

        // Epic recursive sht
        dfs(arr_copy, arr_cost_copy);

        // Advance x iteration in the right until the difference between nmax and nmin is at least 17
        while (arr[nhills-1] - arr[0] > 17) {
            int j = nhills-1;
            while (j >= 0) {
                --arr[j];
                ++arr_cost[j];
                if (arr[j-1] > arr[j])
                    --j;
                else
                    break;
            }
        }
    }

    // Smallest cost acquired
    int cost = calculate_cost(arr_cost);
    if (min_cost > cost)
        min_cost = cost;

    // Print debugging of historic costs
    // printf("***************\n");
    printf("%d\n", cost);
    // printf("***************\n");
    
    return;
}

int main(void) {
    FILE *fin = fopen("skidesign.in", "r");
    FILE *fout = fopen("skidesign.out", "w");

    // Extract values from fin
    fscanf(fin, "%d\n", &nhills);
    for (int i = 0; i < nhills; i++)
        fscanf(fin, "%d\n", &hills[i]);

    // Sort values
    qsort(hills, nhills, sizeof(hills[0]), compare);
    
    // for (int i = 0; i < nhills; i++)
    //     printf("%d\n", hills[i]);

    // Sorcery
    dfs(hills, hills_cost);

    // Save up value to output
    fprintf(fout, "%d\n", min_cost);

    // Garbage collectors
    fclose(fin);
    fclose(fout);
    return 0;
}

