#include <stdio.h>
#include <stdlib.h>

// c dilinde bagli liste dugumleri hem data hemde gelecek dugumun bellekteki dugumun adresini ayni anda tutmak zoundadir

typedef struct Node {
    int data;           // Dugumde saklanan deger
    struct Node *next;  // Sonraki dugumun adresi
}Node;

// Listeyi ters cevirme fonksiyonu 

void reverse_list(Node **head) {
    Node *prev = NULL;      // Baslangicta arkasinda deger yok o yuzden null
    Node *current = *head;  // 0 noktasinda uzerinde oldugumuz dugum
    Node *next = NULL;      // Bir sonraki pointer dugumun adresini gecici saklayacak dugum

    while (current != NULL) {
        // 1. ADIM Gelecegi kaybetmemek icin yedekliyoruz
        next = current -> next;

        // 2. ADIM Bagi geriye cevirecegiz
        current ->next = prev;

        // 3. ADIM pointerlari birer birer ileri kaydirma
        prev = current;
        current = next; 

        // Dongu bittiginde prev listenin bas bolumu olmus olacak
        *head = prev;
    }

}

// Listeye bas taraftan eleman eklemek icin

void push(Node **head, int new_data) {
    Node *new_node = (Node*) malloc(sizeof(Node));
    new_node ->data = new_data;
    new_node ->next = *head;
    *head = new_node;
} 

//Bagli listeyi ekrana yazdirma fonskiyonu

void print_list(Node *head) {
    Node *temp = head;
    while (temp != NULL) {
        printf("%d ->", temp -> data);
        temp = temp ->next;
    }
    printf("NULL \n");
}

//Bellegi temizleme fonksiyonu (Memory leak onleme)

void free_list(Node *head) {
    Node *temp;
    while (head != NULL) {
        temp = head;
        head = head ->next;
        free(temp);
    }
}

int main () {
    Node *head = NULL;

    // ORNEK LISTE
    push(&head, 5);
    push(&head, 4);
    push(&head, 3);
    push(&head, 2);
    push(&head, 1);
    push(&head, 0);

    printf("Orjinal Bagli Liste: \n");
    print_list(head);

    // LISTEYI TERS CEVIRIYORUZ

    reverse_list(&head);

    printf("\n  Ters cevirilmis Bagli Liste");
    print_list(head);

    // BELLEGI TEMIZLIYORUZ

    free_list(head);

    return 0;

}