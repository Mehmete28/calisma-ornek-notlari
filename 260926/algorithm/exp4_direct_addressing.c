#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


typedef struct{
    bool *present; // elemanin kumede olup olmadigini kontrol edecek
    int n;         // evsensel kume boyutu
}DirectDictionary;

// sozlugu olusturma ve ikilendirme 
DirectDictionary* create_dictionary(int n) {
    DirectDictionary *dict = (DirectDictionary*) malloc(sizeof(DirectDictionary));
    dict ->n = n;

    dict->present = (bool*) malloc(sizeof(bool) * (n + 1));

    for(int i = 1; i <= n; i++){
        dict->present[i] = false;
    }
    return dict;
}
// Elemanin olup olmadigini kontrol ediyor

bool search(DirectDictionary *dict, int x){
    if(x < 1 || x > dict->n) return false;
    return dict->present[x];
}

// Eleman Ekleme

void insert(DirectDictionary *dict, int x){
    if (x >= 1 && x <= dict ->n) {
        dict->present[x] = true;
    }
}

// Eleman Silme 

void delete_key(DirectDictionary *dict, int x){
    if(x >= 1 && x <= dict->n){
        dict->present[x] = false;
    }
}

// Bellegi temizleme

void free_dictionary(DirectDictionary *dict){
    free(dict->present);
    free(dict);
}

int main(){
    int n = 10; // Evrensel kume u
    printf("=== Problem 3-4: Direct Address Dictionary Test (n = %d) ===\n\n", n);

    DirectDictionary *dict = create_dictionary(n);

    printf("Elemanlar ekleniyor: 3, 7, 9\n");
    insert(dict, 3);
    insert(dict, 7);
    insert(dict, 9);

    printf("\nArama Sonuclari:\n");
    printf("Search(3) %s\n", search(dict, 3) ? "BULUNDU (true)" : "BULUNAMADI (false)");
    printf("Search(5) %s\n", search(dict, 5) ? "BULUNDU (true)" : "BULUNAMADI (false)");
    printf("Search(7) %s\n", search(dict, 7) ? "BULUNDU (true)" : "BULUNAMADI (false)");

    printf("\nDelete(7) uygulaniyor...\n");
    printf("\nDelete(7) uygulaniyor...\n");

    printf("Search(7) %s\n", search(dict, 7) ? "BULUNDU (true)" : "BULUNAMADI (false)");
    
    free_dictionary(dict);
    return 0;
}