#include <stdio.h>
#include <stdlib.h>
#include <limits.h>


// Sorgu Matrisi olusturma

typedef struct  {
    int **matrix;
    int n;
}RMQ_Matrix;

RMQ_Matrix* create_matrix_rmq(int arr[], int n){
    RMQ_Matrix *rmq = (RMQ_Matrix*) malloc(sizeof(RMQ_Matrix));
    rmq->n = n;
    rmq->matrix = (int **) malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++){
        rmq->matrix[i] = (int *) malloc(n * sizeof(int));
    }

    for(int i = 0; i < n; i++){
        int min_val = arr[i];
        for(int j = 0; j < n; j++){
            if(arr[j] < min_val){
               min_val = arr[j];
         }
         rmq->matrix[i][j] = min_val;
        }
    }
    return rmq;
}

int query_matrix(RMQ_Matrix *rmq, int i, int j){
    return rmq->matrix[i][j];
}

typedef struct {
    int *tree;
    int n;
}SegmentTree;

int min_val(int a, int b) {return (a < b) ? a : b;}

void free_matrix(RMQ_Matrix *rmq) {
    if (rmq == NULL) return;
    for (int i = 0; i < rmq->n; i++) {
        free(rmq->matrix[i]);
    }
    free(rmq->matrix);
    free(rmq);
}

static void build_segment_tree_recursive(int arr[], int *tree, int node, int start, int end){
    if(start == end){
        tree[node] = arr[start];
        return;
    }

    int mid = start + (end - start) / 2;
    build_segment_tree_recursive(arr, tree, 2 * node + 1, start, mid);
    build_segment_tree_recursive(arr, tree, 2 * node + 2, mid + 1, end);
    tree[node] = min_val(tree[2 * node + 1], tree[2 * node + 2]);
}

SegmentTree *build_segment_tree(int arr[], int n){
    SegmentTree *st = (SegmentTree *) malloc(sizeof(SegmentTree));
    if (st == NULL) return NULL;

    st->n = n;
    st->tree = (int *) malloc(sizeof(int) * (4 * n));
    if (st->tree == NULL) {
        free(st);
        return NULL;
    }

    for (int i = 0; i < 4 * n; i++) st->tree[i] = INT_MAX;
    build_segment_tree_recursive(arr, st->tree, 0, 0, n - 1);
    return st;
}

int query_st_until(int *tree, int node, int start, int end, int l, int r){
    if (l > r || start > end) return INT_MAX;
    if (r < start || end < l) return INT_MAX;
    if (l <= start && end <= r) return tree[node];

    int mid = start + (end - start) / 2;
    int left_min = query_st_until(tree, 2 * node + 1, start, mid, l, r);
    int right_min = query_st_until(tree, 2 * node + 2, mid + 1, end, l, r);
    return min_val(left_min, right_min);
}

int query_segment_tree(SegmentTree *st, int l, int r){
    if (st == NULL || l < 0 || r >= st->n || l > r) return INT_MAX;
    return query_st_until(st->tree, 0, 0, st->n - 1, l, r);
}

void free_segment_tree(SegmentTree *st){
    if (st == NULL) return;
    free(st->tree);
    free(st);
}

int main(){
    printf("Problem 3 -11 Minimim Aralik Sorgulama (RMQ TESTI)\n\n");

    int arr[] = {2, 4, 3, 1, 6, 7, 8, 9};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("Dizi :");
    for(int i = 0; i < n; i++) printf("%d ", arr[i]);
    printf("\n\n");

    RMQ_Matrix *mat = create_matrix_rmq(arr, n);
    printf("1. Matris Sorgusu [1 ..4 arasi (4, 3, 1, 6)]-> Min: %d\n", query_matrix(mat, 1, 4));


    SegmentTree *st = build_segment_tree(arr, n);
    printf("2. Segment Tree Sorgusu [1 .. 4] arasi (4, 3, 1, 6) -> Min: %d\n", query_segment_tree(st, 1, 4));
 
    free_matrix(mat);
    free_segment_tree(st);

    return 0;
}

