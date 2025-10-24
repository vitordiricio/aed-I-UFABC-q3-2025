#include <stdio.h>


int main(void) {
    int a;
    int b;
    printf("Entrada: ");
    scanf("%d %d", &a, &b);
    printf("Saída: %d %d", a / b, a % b);
    return 0;
}