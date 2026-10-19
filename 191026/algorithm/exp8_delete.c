#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node{
    int key;
    int size;
    struct Node *left;
    struct Node *right;

}Node;

int get_size(Node *node){
    return(node == NULL) ? 0 : node ->size;
}

void update_size(Node *node){
    if(node != NULL){
        node->size = 1 + get_size(node ->left) + get_size(node->right);
    }
}

bool member(Node *root, int x){
    if(root == NULL) return false;
    if(root ->key == x) return true;
    if(x < root->key) return member(root->left, x);
    return member(root->right, x);
}

Node* insert(Node *root, int x){
    if(root == NULL) {
        Node *n = (Node*) malloc(sizeof(Node));
        n->key = x; n ->size = 1; n->left = n->right = NULL;
        return n;
    }

    if(x < root->key) root->left =insert(root->left, x);
    else if (x > root->key) root->right = insert(root->right, x);

    update_size(root);
    return root;
}

Node* delete_kth(Node *root, int k, int *deleted_key){
    if(root == NULL) return NULL;

    int left_size = get_size(root->left);

    if(k == left_size + 1){
        if(deleted_key) *deleted_key = root->key;
        if(root->left == NULL) {Node *t = root->right; free(root); return t;}
        if(root->right == NULL) {Node *t = root->left; free(root); return t;}

        Node *min_right = root->right;
        while(min_right->left !=NULL) min_right = min_right->left;
        root->key = min_right->key;
        int dummy;
        root->right = delete_kth(root->right, 1, &dummy);
        } else if (k <= left_size) {
            root->left = delete_kth(root->left, k, deleted_key);
        } else {
            root->right = delete_kth(root->right, k - (left_size + 1), deleted_key);
        }

        update_size(root);
        return root;
}

int main(){
    Node *root = NULL;
    root = insert(root, 20);
    root = insert(root ,10);
    root = insert(root, 30);

    printf("Member(10): %s\n", member(root,10) ? "Bulundu" : "Bulunamadi");

    int deleted_key;
    root = delete_kth(root, 1, &deleted_key);
    printf("Silinen en kucuk eleman: %d\n", deleted_key);

    return 0;
}