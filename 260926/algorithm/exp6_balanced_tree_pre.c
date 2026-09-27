#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int key;
    struct Node *left;
    struct Node *right;
    struct Node *parent;
    int height;

    struct Node *prev;
    struct Node *next;

} Node;

// 0(1) Surede Successor ve Predecessor
Node* successor(Node *node){
    return (node !=NULL) ? node->next : NULL;
}

Node* predecessor(Node *node){
    return (node !=NULL) ? node->prev : NULL;   
}

void link_in_list(Node *new_node, Node *pred, Node *succ) {
    new_node->prev = pred;
    new_node->next = succ;
    if(pred != NULL) pred->next = new_node;
    if(succ !=NULL) succ->prev = new_node;
}

void unlink_from_list(Node *node){
    if(node->prev != NULL) node->prev->next = node->next;
    if(node->next != NULL) node->next->prev = node->prev;
}

int main(){
    printf("=== Problem 3-6: O(1) Predecessor ve Successor ===\\n");

    Node n1 = {.key = 5, .left = NULL,.right = NULL ,.parent = NULL, .prev = NULL, .next = NULL};
    Node n2 = {.key = 10,.left = NULL , .right = NULL ,.parent = NULL, .prev = NULL, .next = NULL};

    link_in_list(&n2, &n1, NULL);

    printf("n1 (%d) -> Successor: %d\\n", n1.key, successor(&n1)->key);
    printf("n2 (%d) -> Predecessor: %d\\n", n2.key, predecessor(&n2)->key);

    return 0;
}