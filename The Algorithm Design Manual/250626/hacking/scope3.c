#include <stdio.h>

int j = 42; 

void func3(void);
void func2(void);
void func1(void);

void func3(void) {
    int i = 11, j = 999; 

    printf("\t\t\t[in func3] i @ %p = %d\n", (void*)&i, i);
    printf("\t\t\t[in func3] j @ %p = %d\n", (void*)&j, j);
}

void func2(void) {
    int i = 7;

    printf("\t\t[in func2] i @ %p = %d\n", (void*)&i, i);
    printf("\t\t[in func2] j @ %p = %d\n", (void*)&j, j);
    printf("\t\t[in func2] setting j = 1337\n");
    j = 1337;        
    func3();
    printf("\t\t[back in func2] i @ %p = %d\n", (void*)&i, i);
    printf("\t\t[back in func2] j @ %p = %d\n", (void*)&j, j);
}

void func1(void) {
    int i = 5;

    printf("\t[in func1] i @ %p = %d\n", (void*)&i, i);
    printf("\t[in func1] j @ %p = %d\n", (void*)&j, j);
    func2();
    printf("\t[back in func1] i @ %p = %d\n", (void*)&i, i);
    printf("\t[back in func1] j @ %p = %d\n", (void*)&j, j);
}

int main(void) {
    int i = 3;

    printf("[in main]  i @ %p = %d\n", (void*)&i, i);
    printf("[in main]  j @ %p = %d\n", (void*)&j, j);
    func1();
    printf("[back main] i @ %p = %d\n", (void*)&i, i);
    printf("[back main] j @ %p = %d\n", (void*)&j, j);
    return 0;
}