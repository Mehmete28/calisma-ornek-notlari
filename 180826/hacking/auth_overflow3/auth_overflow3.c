#include <stdio.h>
#include <string.h>
#include <stdlib.h>


int inspect_input(const char *input)
{
    char note[12];
    int status = 0;

    strcpy(note, input);

    if(status != 0){
        printf("Durum: degisti (%d)\n", status);
    } else {
        printf("Durum: degismedi\n");
    }

    return status;  
}

int main(int argc, char *argv[])
{
    if(argc != 2){
        printf("Kullanim: %s <metin>\n",argv[0]);
        return 1;
    }

    inspect_input(argv[1]);
    return 0;
}