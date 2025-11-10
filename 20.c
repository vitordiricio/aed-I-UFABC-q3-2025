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
    int mdc;

    scanf("%d %d", &a, &b);

    mdc = findMDC(a, b);

    printf("%d\n", mdc);

    return 0;
}