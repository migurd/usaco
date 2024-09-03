/*
LANG: C
ID: angelqu1
TASK: wormhole
*/

#include <stdio.h>

#define MAX_WORMHOLES 12
#define TRUE 1
#define FALSE 0

int nwormholes;
int X[MAX_WORMHOLES] = {0};
int Y[MAX_WORMHOLES] = {0};
// I HATE YOU C, WHAT DO YOU MEAN YOU CAN'T INITIALIZE ALL OF THE ELEMENTS TO THE SAME VALUE BY DEFAULT
int partner[MAX_WORMHOLES] = {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1};
int next_on_right[MAX_WORMHOLES] = {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1};
int x = 0;

int is_cycle() {
    // printf("%d\t%d\t%d\t%d\n", next_on_right[0], next_on_right[1], next_on_right[2], next_on_right[3]);
    // x++;
    // printf("%d\n", x);
    // printf("********\n");
    for (int start = 0; start < nwormholes; start++) {
        int pos = start;
        for (int count = 0; count < nwormholes; count++) {
            // printf("\t%d:%d\t", count, partner[count]);
            // printf("%d\n", pos);
            // printf("%d --> ", pos);
            pos = next_on_right[partner[pos]];
            // printf("%d\n", pos);
            if (pos == -1) break; // it doesn't cycle
        }
        // printf("\n");
        // printf("%d\n", pos);
        if (pos != -1) return TRUE; // it cycles
    }
    return FALSE;
}

int solve(void) {
    // define first available partner
    int i, total = 0;
    for (i = 0; i < nwormholes; i++)
        if (partner[i] == -1) break;

    // all paired
    //printf("hi %d\n", i);
    if (i == nwormholes) {
        //printf("hi2\n");
        if (is_cycle()) return 1;
        return 0;
    }

    // try pairing all i with all possible wormholes j
    for (int j = i+1; j < nwormholes; j++) {
        //printf("i: %d; j: %d\n", i, j);
        //printf("%d\n", partner[j]);
        if (partner[j] == -1) {
            //printf("hi3");
            partner[i] = j;
            partner[j] = i;
            total += solve();
            partner[i] = partner[j] = -1;
        }
    }
    return total;
}

int main(void) {
    FILE *fin = fopen("wormhole.in", "r");
    FILE *fout = fopen("wormhole.out", "w");

    // n wormholes
    fscanf(fin, "%d\n", &nwormholes);

    // x and y coords
    int i = 0;
    while (i < nwormholes) {
        fscanf(fin, "%d %d\n", &X[i], &Y[i]);
        // printf("%d %d\n", X[i], Y[i]);
        ++i;
    }
    
    // initialize next_on_right
    for (int i = 0; i < nwormholes; i++) {
        for (int j = 0; j < nwormholes; j++) {
            if (X[i] < X[j] && Y[i] == Y[j])
                if (next_on_right[i] == -1 ||
                    (X[j] - X[i]) < (X[next_on_right[i]] - X[i]))
                    next_on_right[i] = j;
        }
    }

    // magic
    int res = solve();
    fprintf(fout, "%d\n", res);

    // Garbage collectors
    fclose(fin);
    fclose(fout);

    return 0;
}
