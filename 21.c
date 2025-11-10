#include <stdio.h>

int findMDC(int a, int b) {
    int aux;
    while (b != 0) {
        aux = a % b;
        a = b;
        b = aux;
    }
    return a;
}

int findMMC(int a, int b) {
    if (a == 0 || b == 0) {
        return 0;
    }
    
    return (a / findMDC(a, b)) * b;
}

int main() {
    int a, b;
    int mmc;

    scanf("%d %d", &a, &b);

    mmc = findMMC(a, b);

    printf("%d\n", mmc);

    return 0;
}