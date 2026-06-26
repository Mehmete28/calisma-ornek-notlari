#include <stdio.h>

void function(){
    int var = 5; //ornek fonksiyon , kendi baglaminda
    static int static_var = 5; // statik deger baslatma

    printf("\t[in function] var @ %p = %d\n", &var, var);
    printf("\t[in function] static_var @ %p = %d\n", &static_var, static_var);
    var++; // Arttirma operatoru
    static_var++; // Arttirma operatoru
}

int main(){
    int i;
    static int static_var = 1337;
    
    for(i=0;i< 5; i++){ //5 kez doner
        printf("[in main] static_var @ %p = %d\n", &static_var, static_var);
        function(); // Fonsiyon cagirisi
    }
}