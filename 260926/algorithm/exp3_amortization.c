#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *array;     
    int  size;      // mevcut eleman sayisi n
    int  capacity;  // dizinin toplam bellek kapasitesi
}DynamicArray;

// Dinamik Dizi Olusturma

DynamicArray* create_array(int initial_capacity) {
    DynamicArray *da = (DynamicArray*) malloc(sizeof(DynamicArray));
    da -> size = 0;
    da -> capacity = initial_capacity > 0 ? initial_capacity : 1;
    da -> array = (int*) malloc(sizeof(int) * da->capacity);
    
    return da;
}

//Diziyi tekrardan resizelama

void resize(DynamicArray *da, int new_capacity) {
    if (new_capacity < 1) new_capacity = 1;
    printf("--> Bellek yeniden boutlandiriliyor : %d -> %d\n", da->capacity, new_capacity);
    int *new_array = (int*) realloc(da->array, sizeof(int) * new_capacity);
   if (new_array != NULL) {
    da ->array = new_array;
    da ->capacity = new_capacity;
   }
}

// Eleman ekleme void push ile

void push(DynamicArray *da, int value){
    // Kural depolama %100 doldugunda kapasiteyi iki katina cikaracak
    if(da -> size == da -> capacity){
        resize(da, da ->capacity * 2);
    }
    da->array[da->size++] = value;
}

// Eleman silme pop ile

int pop(DynamicArray *da){
    if(da ->size == 0) return -1;
    int value = da->array[--da->size];

    /* Eleman sayisi kapasitenin ceyregine ve ya altina dustugu ve kapasite minimumun uzerindeyse kapasiyeyi yariya indirme */
    if(da->size > 0 && da->size <= da->capacity / 4){
        resize(da, da->capacity / 2);
    }

    return value;

}

void free_array(DynamicArray *da){
    free(da->array);
    free(da);
}

int main(){

    printf("=== Problem 3-3: Dinamik Dizi Amortize Analiz Testi ===\n");

    //Baslangic kapasitesi iki olan dinamik bir dizi olusturuyoruz
    DynamicArray *da = create_array(2);

    printf("--- ELEMAN EKLEME (Genişleme Testi) ---");

    for(int i = 1; i <= 9; i++){
        push(da, i * 10);
    }

    printf("--- ELEMAN SİLME (Küçülme / Underflow Testi) ---");

    while(da -> size > 0){
        pop(da);
    }

    // Bellek temizleme

    free_array(da);

    return 0;

}

