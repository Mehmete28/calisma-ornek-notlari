#include <stdio.h>

void func3(void);
void func2(void);
void func1(void);

void func3(void) {
    int i = 11;
    printf("\t\t[in func3] i = %d\n", i);
}

void func2(void) {
    int i = 7;
    printf("\t\t[in func2] i = %d\n", i);
    func3();
    printf("\t\t[back in func2] i = %d\n", i);
}

void func1(void) {
    int i = 5;
    printf("\t[in func1] i = %d\n", i);
    func2();
    printf("\t[back in func1] i = %d\n", i);
}

int main(void) {
    int i = 3;
    printf("[in main] i = %d\n", i);
    func1();
    printf("[back in main] i = %d\n", i);
    return 0;
}