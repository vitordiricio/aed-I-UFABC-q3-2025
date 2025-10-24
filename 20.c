#include <stdio.h>

int findMDC(int a, int b) {
    int remainder;
    while (b != 0) {
        remainder = a % b;
        a = b;
        b = remainder;
    }
    return a;
}

int main() {
    int a, b;
    int gcd;

    scanf("%d %d", &a, &b);

    gcd = findMDC(a, b);

    printf("%d\n", gcd);

    return 0;
}