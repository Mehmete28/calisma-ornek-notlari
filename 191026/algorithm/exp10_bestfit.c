#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// ===========================================================================

// PROBLEM 3-10 : BEST PACKING 

// ===========================================================================

typedef struct Node {
    int bin_id;             //KUTU NUMARASI
    int rem_capacity;       //KALAN KAPASİTE
    struct Node *left;
    struct Node *right;
} Node;

//YENI KUTU DUGUMU OLSUTURMA

Node* create_node(int bin_id, int rem_capacity){
    Node *node =(Node*) malloc(sizeof(Node));
    if (!node) return NULL;
    node ->bin_id = bin_id;
    node ->rem_capacity = rem_capacity;
    node ->left = node ->right = NULL;
    return node;
}

// KARSILASTIRMA MANTIGI

int compare_bins(int cap1, int id1, int cap2 , int id2){
    if(cap1 != cap2) return cap1 - cap2;
    return id1 - id2;
}


// AGACA KUTU EKLEME

Node* insert_bin(Node *root, int bin_id, int rem_capacity){
    if(root == NULL) return create_node(bin_id, rem_capacity);

    if(compare_bins(rem_capacity, bin_id, root->rem_capacity, root->bin_id) < 0){
        root ->left = insert_bin(root->left,bin_id, rem_capacity);
    }
    else{
        root ->right = insert_bin(root->right,bin_id, rem_capacity);
    }
    return root;
}

//KAPASITE GUNCELLENECEGI ZAMAN  AGACTAN KUTU SILME

Node* delete_bin(Node *root, int bin_id, int rem_capacity){
    if(root == NULL) return NULL;

    int cmp = compare_bins(rem_capacity, bin_id, root->rem_capacity, root->bin_id);

    if(cmp < 0){
        root ->left = delete_bin(root->left, bin_id, rem_capacity);
    }
    else if (cmp > 0){
        root ->right = delete_bin(root->right, bin_id, rem_capacity);
    }
    else{
        if(root->left == NULL){
            Node *temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL){
            Node *temp = root->left;
            free(root);
            return temp;
        }

        Node *succ = root->right;
        while(succ->left != NULL) succ = succ->left;

        root->bin_id = succ->bin_id;
        root->rem_capacity = succ->rem_capacity;

        root->right = delete_bin(root->right, succ->bin_id, succ->rem_capacity);
    }
    return root;
}

Node* find_best_fit(Node *root, int item_size){
    Node *best = NULL;
    Node *current = root;

    while(current != NULL){
        if(current->rem_capacity >= item_size){
            best = current;
            current = current->left;
        }
        else{
            current = current->right;
        }
    }

    return best;
}

void free_tree(Node *root){
    if(root == NULL) return;
    free_tree(root->left);
    free_tree(root->right);
    free(root);
}

void best_fit_pack(int items[], int n, int bin_capacity){
    Node *tree_root = NULL;
    int total_bins = 0;

    printf(" ---Best Fit Yerleştirme Adimlari---\n\n");

    for (int i = 0; i < n; i++) {
        int item_size = items[i];
        Node *best_bin = find_best_fit(tree_root, item_size);

        if (best_bin != NULL) {
            int chosen_id = best_bin->bin_id;
            int old_cap = best_bin->rem_capacity;
            int new_cap = old_cap - item_size;

            printf("Nesne %d (Boyut: %d) -> Kutu %d ye eklendi (Kalan kapasite: %d -> %d)\n",
                   i + 1, item_size, chosen_id, old_cap, new_cap);

            tree_root = delete_bin(tree_root, chosen_id, old_cap);
            if (new_cap > 0) {
                tree_root = insert_bin(tree_root, chosen_id, new_cap);
            }
        }
        else {
            total_bins++;
            int chosen_id = total_bins;
            int old_cap = bin_capacity;
            int new_cap = old_cap - item_size;

            printf("Nesne %d (Boyut: %d) -> Yeni Kutu %d acildi (Kalan kapasite: %d -> %d)\n",
                   i + 1, item_size, chosen_id, old_cap, new_cap);

            tree_root = insert_bin(tree_root, chosen_id, new_cap);
        }

        printf("Toplam kullanilan kutu sayisi: %d\n", total_bins);
    }

    free_tree(tree_root);
}

// MAIN FONKSIYONU

int main(){
    printf("=== Problem 3-10: Best Fit Packing Algritmasi ===\n\n");

    int items[] = {4, 8, 1, 4, 2, 5, 6};
    int n = sizeof(items) / sizeof(items[0]);
    int bin_capacity = 10;

    printf("Nesneler: ");
    for(int i = 0; i < n; i++) {
        printf("%d ", items[i]);
    }
    printf("\n\n");

    best_fit_pack(items, n, bin_capacity);
    return 0;
}
