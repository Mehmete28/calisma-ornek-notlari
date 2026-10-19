#include <stdlib.h>
#include <stdio.h>

typedef struct Node {
    int key;
    struct Node *left;
    struct Node *right;
}Node;

// YENI DUGUM OLSUTURMA

Node* create_node(int key){
    Node *node = (Node*) malloc(sizeof(Node));
    if (!node) return NULL;
    node->key = key;
    node->left = NULL;
    node->right = NULL;
    return node;
}

Node* insert(Node *root, int key){
    if(root == NULL) return create_node(key);
    if(key < root->key) root->left = insert(root->left,key);
    else if (key > root->key) root->right = insert(root->right ,key);

    return root;
}

// Agacin en buyuk elemanini (en sagdaki) elemanini ayirmak icin
Node* extract_max(Node *root, Node **max_node){
    if(root == NULL) return NULL;

    if(root->right == NULL){
        *max_node = root;
        return root->left;
    }

    root->right = extract_max(root->right, max_node);
    return root;
}

//Zaman karmasikliginda birlestirme (concatenate)
Node* concatenate_trees(Node *t1, Node *t2){
    if(t1 == NULL) return t2;
    if(t2 == NULL) return t1;

    // Agacin en buyuk elemanini O(h1)surede agatan sokme

    Node *max_t1 = NULL;
    t1 = extract_max(t1, &max_t1);

    // max_t1 kok yapip t1 ve t2 yi baglama

    max_t1->left = t1;
    max_t1->right = t2;

    return max_t1; // yeni birlestirilmis agac
}

// Sirali yazdirma (in order traversal)

void print_inorder(Node *root) {
    if(root == NULL) return;
    print_inorder(root->left);
    printf("%d" , root->key);
    print_inorder(root->right);
}

//Bellegi Temizleme

void free_tree(Node *root){
    if(root == NULL) return;
    free_tree(root->left);
    free_tree(root->right);
    free(root);
}

int main(){
    printf("=== Problem 3-9: İki Arama Ağacini Birleştirme (Concatenate) ===\n\n");

    Node *t1 = NULL;

    // T1 Agaci Elemanlari

    t1 = insert(t1, 10);
    t1 = insert(t1, 5);
    t1 = insert(t1, 15);
    t1 = insert(t1, 3);

    // T2 Agaci Elemanlari

    Node *t2 = NULL;

    t2 = insert(t2, 40);
    t2 = insert(t2, 25);
    t2 = insert(t2, 50);
    t2 = insert(t2, 30);

    printf("T1 Agaci (In-order): ");
    print_inorder(t1);
    printf("\n");

    printf("T2 Agaci (In-order): ");
    print_inorder(t2);
    printf("\n\n");

    printf("--> O(h) zamanda birleştirme uygulaniyor...\n");
    Node *merged_tree = concatenate_trees(t1, t2);

    printf("Birlesik Agac T (In-order): ");
    print_inorder(merged_tree);
    printf("\n");

    free_tree(merged_tree);
    return 0;
}