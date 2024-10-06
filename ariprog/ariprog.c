/*
TASK: ariprog
ID: angelqu1
LANG: C
*/

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>

#define TRUE 1
#define FALSE 0
#define MAX_BISQ 250

typedef struct node Node;
struct node {
    Node* left;
    Node* right;
    int value;
    int height;
};

int flag_empty = TRUE;
int values_table[2*MAX_BISQ*MAX_BISQ+1];

int max(int a, int b) {
    return a > b ? a : b;
}

int height(Node* node) {
    if (NULL == node)
        return 0;
    return node->height;
}

int get_balance(Node* node) {
    if (NULL == node)
        return 0;
    return 0;
    return height(node->left) - height(node->right);
}

Node* right_rotate(Node* node) {
    Node* left = node->left;
    Node* left_right = left->right;

    left->right = node;
    node->left = left_right;

    node->height = 1 + max(
        height(node->left),
        height(node->right));
    left->height = 1 + max(
        height(left->left),
        height(left->right));

    return left;
}

Node* left_rotate(Node* node) {
    Node *right = node->right;
    Node *right_left = right->left;

    right->left = node;
    node->right = right_left;

    node->height = 1 + max(
        height(node->left),
        height(node->right));
    right->height = 1 + max(
        height(right->left),
        height(right->right));

    return right;
}

Node* create_node(int value) {
    Node* node = (Node*)malloc(sizeof(Node));

    node->left = NULL;
    node->right = NULL;
    node->value = value;
    node->height = 1;

    values_table[value] = 1;

    return node;
}

Node* insert_node(Node* node, int value) {
    if (NULL == node)
        return create_node(value);

    if (value < node->value)
        node->left = insert_node(node->left, value);
    else if (value > node->value)
        node->right = insert_node(node->right, value);
    else
        return node;

    node->height = 1 + max(
                    height(node->left),
                    height(node->right));

    int balance = get_balance(node);

    // Left Left Case
    if (balance > 1 && value < node->left->value)
        return right_rotate(node);
    // Right Right Case
    if (balance < -1 && value > node->right->value)
        return left_rotate(node);
    // Left Right Case
    if (balance > 1 && value < node->left->value)
    {
        node->left = left_rotate(node->left);
        return right_rotate(node);
    }
    // Right Left Case
    if (balance < -1 && value < node->right->value)
    {
        node->right = right_rotate(node->right);
        return left_rotate(node);
    }

    return node;
}

int find_value(Node* node, int value) {
    if (NULL == node)
        return FALSE;

    if (value < node->value)
        return find_value(node->left, value);
    else if (value > node->value)
        return find_value(node->right, value);
    else
        return TRUE;

    return FALSE;
}

void dfs(FILE *fout, Node* root, Node* node, int max_value, int n, int seq) {
    if (NULL == node)
        return;

    if (max_value < (n-1) * seq)
        return;
    if (NULL != node->left)
        dfs(fout, root, node->left, max_value, n, seq);

    if (max_value < node->value + (n-1) * seq)
        return;

    int flag = TRUE;
    for (int i = 1; i < n; i++) {
        // if (!find_value(root, node->value + i * seq)) {
        if (0 == values_table[node->value + i * seq]) {
            flag = FALSE;
            break;
        }
    }
    if (flag) {
        fprintf(fout, "%d %d\n", node->value, seq);
        flag_empty = FALSE;
    }

    if (NULL != node->right)
        dfs(fout, root, node->right, max_value, n, seq);

    // free(node);
    return;
}

int main(void) {
    FILE *fin = fopen("ariprog.in", "r");
    FILE *fout = fopen("ariprog.out", "w");

    // clock_t start_time = clock();

    // n = sequence length expected
    // m = pair bisquares max value 
    int n, m = 0;
    int max_value = 0;
    fscanf(fin, "%d\n%d\n", &n, &m);

    Node* root = NULL;
    for (int i = 0; i <= m; i++) {
        for (int j = 0; j <= m; j++) {
            int bisquare_result = i*i + j*j;
            max_value = max(bisquare_result, max_value);
            root = insert_node(root, bisquare_result);
        }
    }
    
    // Max
    for (int i = 1; i <= max_value / (n-1); i++)
        dfs(fout, root, root, max_value, n, i); // Didn't free the values, but :p

    if (flag_empty)
        fprintf(fout, "%s\n", "NONE");

    // End time
    // clock_t end_time = clock();

    // Calculate the elapsed time in seconds
    // double time_taken = (double)(end_time - start_time) / CLOCKS_PER_SEC;

    // printf("The program took %f seconds to run.\n", time_taken); 

    fclose(fin);
    fclose(fout);
    return 0;
}
