#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

// stacklerin veri tipini int tanimlayarak hatali olan parantezin metindeki indeksini direkt bulabilmemiz icin int tanimladik.

typedef struct {
    int *data;      // indeks tutacak
    int top;        // en ust indeks
    int capacity;   // stackin alabilecegi total alan 
}Stack;

// bellekten dizenin uzunlugu kadar yer ayiriyoruz

Stack* create_stack(int capacity) {
    Stack *stack = (Stack*) malloc(sizeof(Stack));
    stack -> capacity = capacity;
    stack -> top = -1;
    stack -> data = (int*) malloc(sizeof(int) * capacity);
    return stack;
}

void free_stack(Stack *stack) {
    free(stack -> data); // dinamik dizi serbest kaliyor
    free(stack);        // sonra da yapinin kendisi
}

// yigin bos mu diye kontrol ediyor

bool is_empty(Stack *stack) {
    return stack -> top == -1;
}
// yigina eleman ekliyor

void push(Stack *stack, int index){
    stack ->data[++stack -> top] = index;
}

// yigindan eleman cikariyor

int pop(Stack *stack){
    if(is_empty(stack)) return -1;
    return stack -> data[stack ->top--]; 
}

/** 
    parantez dengesinin kontrol edildigi kisim
    parametre s : incelenecek metin dizisi
    parametre error_index: hata olustugunda ilk bozan parantezin indeksi buraya yazilacak
    return da dengeli ise true degilse false dondurecek
*/

bool check_balanced_parantheses(const char *s, int *error_index) {
    int len = strlen(s);
    Stack *stack = create_stack(len);

    for(int i = 0; i < len; i++){
        if(s[i] == '('){ // parantez acildiginda konumunu i stackine atiyor
            push(stack ,i);
        }else if(s[i] == ')') { // yigin bosken kapanma paranteso gelirse false dondurecek

            if(is_empty(stack)){

                *error_index = 1;
                free_stack(stack);
                return(false);
            }
            // yigin bos degilse en son acilan ile eslesme var demek olacak
            pop(stack);
        }
    }

    if (!is_empty(stack)){
        // yiginin en altinda kalan elaman (data[0]) kapatilmayan , en soldaki parantezin indeksi olacak

        *error_index = stack ->data[0];
        free_stack(stack);
        return false;
    }

    free_stack(stack);
        *error_index = -1; // hata yoksa
         return true;
}

// MAIN FONKSIYONU

int main (){
    const char *tests[] = {
        "((())())()", // Beklenen: DENGELİ 
        ")()(", // Beklenen: HATALI (0\. indeksteki ')') 
        "())", // Beklenen: HATALI (2\. indeksteki ')') 
        "((()" // Beklenen: HATALI (0\. indeksteki '(')
    };
    int num_tests = sizeof(tests) / sizeof(tests);

    for (int i = 0 ; i < num_tests; i++){
        int error_idx = -1;
        bool is_balanced = check_balanced_parantheses(tests[i], &error_idx);

        printf("Girdi : \"%s\"\n", tests[i]);
        if(is_balanced){
            printf(" -> Sonuc : Dengeli\n\n");
        }else {
            printf(" -> Sonuc : Hatali (Ilk bozan parantez indeksi : %d, Karakter '%c')\n\n", error_idx, tests[i][error_idx]);
        }
    }

    return 0;
}