/*
ID: angelqu1
TASK: milk3
LANG: C
*/

#include <stdio.h>
#include <stdlib.h>

#define MAX 21
#define LEN_RES 100

int bitmap[MAX][MAX][MAX];
int A, B, C;
int results[LEN_RES];
int counter = 0;

int cmp(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

int min(int a, int b) {
    return (a < b) ? a : b;
}

void dfs(int a, int b, int c) {
    if (bitmap[a][b][c]) {
        return;
    }
    bitmap[a][b][c] = 1;
    
    if (0 == a)
        results[counter++] = c;

    // a -> b
    dfs(a-min(a, B-b), b+min(a, B-b), c);
    // a -> c
    dfs(a-min(a, C-c), b, c+min(a, C-c));

    // b -> a
    dfs(a+min(b, A-a), b-min(b, A-a), c);
    // b -> c
    dfs(a, b-min(b, C-c), c+min(b, C-c));

    // c -> a
    dfs(a+min(c, A-a), b, c-min(c, A-a));
    // c -> b
    dfs(a, b+min(c, B-b), c-min(c, B-b));

    return;
}

int main(void) {
    FILE *fin = fopen("milk3.in", "r");
    FILE *fout = fopen("milk3.out", "w");

    fscanf(fin, "%d %d %d\n", &A, &B, &C);

    dfs(0, 0, C);

    qsort(results, counter, sizeof(results[0]), cmp);

    int i = 0;
    for (; i < counter-1; i++)
        fprintf(fout, "%d ", results[i]);
    fprintf(fout, "%d\n", results[i]);
    

    fclose(fin);
    fclose(fout);
    return 0;
}
