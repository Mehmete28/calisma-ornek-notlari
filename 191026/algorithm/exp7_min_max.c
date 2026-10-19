#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct BSTNode {
    int key;
    struct BSTNode *left;
    struct BSTNode *right;
    struct BSTNode *parent;

}BSTNode;

typedef struct {
    BSTNode *root;
    BSTNode *min_node;
    BSTNode *max_node;

}FastMinMaxDict;

BSTNode* create_node(int key){
    BSTNode *node = (BSTNode*) malloc(sizeof(BSTNode));
    node->key =key;
    node->left = node->right = node->parent = NULL;
    return node;
}

int get_minimum(FastMinMaxDict *dict, bool *error){
    if(dict ->min_node == NULL){*error = true; return -1;}
    *error = false;
    return dict->min_node->key;
}


int get_maximum(FastMinMaxDict *dict, bool *error){
    if(dict->max_node == NULL){*error = true; return -1;}
    *error = false;
    return dict->max_node->key;
}

BSTNode* bst_minimum(BSTNode *node){
    while (node && node-> left !=NULL) node = node->left;
    return node;
}

BSTNode* bst_succesor(BSTNode *x){
    if(x->right != NULL) return bst_minimum(x->right);
    BSTNode *p = x->parent;
    while(p != NULL && x == p->right){
        x = p;
        p = p->parent;
    }
    return p;
}

BSTNode* bst_predecessor(BSTNode *x){
    if(x->left != NULL) return bst_minimum(x->left);
    BSTNode *p = x->parent;
    while(p != NULL && x == p->left){
        x = p;
        p = p->parent;
    }
    return p;
}

BSTNode* bst_search(BSTNode *root, int key) {
    if(root == NULL || root->key == key) return root;
    if(key < root->key) return bst_search(root->left, key);
    return bst_search(root->right, key);
}

void insert_key(FastMinMaxDict *dict, int key){
    BSTNode *new_node = create_node(key);
    BSTNode *y = NULL;
    BSTNode *x = dict->root;

    while(x != NULL){
        y = x;
        if(new_node->key <x->key)x = x->left;
        else x = x->right;
    }

    new_node->parent = y;

    if(y = NULL) dict->root - new_node;
    else if (new_node->key)  y->left = new_node;
    else y->right = new_node;

    if(dict->min_node == NULL || new_node ->key < dict->min_node->key) {
        dict->min_node = new_node;
    }
    if(dict->max_node == NULL || new_node->key > dict->max_node->key){
        dict->max_node = new_node;
    }
}

void delete_key(FastMinMaxDict *dict, int key){
    BSTNode *z = bst_search(dict->root, key);
        if(z = NULL) return;

        if(z == dict->min_node){
        dict->min_node = bst_succesor(z);
        }

         if(z == dict->max_node){
        dict->max_node = bst_succesor(z);
        }

        BSTNode *y = z, *x;
        if(z->left == NULL || z->right == NULL) y = z;
        else y = bst_succesor(z);

        if(x != NULL) x->parent = y->parent;

        if(y->parent == NULL) dict->root = x;
        else if (y == y->parent->left) y->parent->left = x;
        else y->parent->right = x;

        if(y != z) z->key = y->key;
        free(y);
}
 int main(){

    printf("=== Problem 3-7: O(1) Min/Max Destekli Sozluk Testi ===\\n\\n");

    FastMinMaxDict dict = {NULL, NULL, NULL};
    bool err;

    printf("Elemanlar ekleniyor: 15, 6, 18, 3, 7, 20\\n");
    insert_key(&dict, 15);
    insert_key(&dict, 6);
    insert_key(&dict, 18);
    insert_key(&dict, 3);
    insert_key(&dict, 7);
    insert_key(&dict, 20);

    printf("\\nO(1) Minimum : %d (Beklenen: 3)\\n", get_minimum(&dict, &err));
    printf("\\nO(1) Maximum : %d (Beklenen: 20)\\n", get_maximum(&dict, &err));

    printf("\\n--&gt; En kucuk eleman (3) siliniyor...\\n");
    delete_key(&dict, 3);
    printf("Yeni O(1) Minimum : %d (Beklenen: 6)\\n", get_minimum(&dict, &err));

    printf("\\n--> En buyuk eleman (20) siliniyor...\\n");
    delete_key(&dict, 20);
    printf("Yeni O(1) Maximum : %d (Beklenen: 18)\\n", get_maximum(&dict, &err));

    return 0;
 }



