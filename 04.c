#include <stdio.h>

int soma(int x, int y) {
    return x + y;
}

int main(void) {
    int a;
    int b;
    printf("Entrada: ");
    scanf("%d %d", &a, &b);
    printf("Saída: %d", soma(a, b));
    return 0;
}