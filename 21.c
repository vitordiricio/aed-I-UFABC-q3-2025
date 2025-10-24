#include <stdio.h>

int findMMC(int a, int b) {
    int remainder;
    while (b != 0) {
        remainder = a % b;
        a = b;
        b = remainder;
    }
    return a;
}

int findLCM(int a, int b) {
    if (a == 0 || b == 0) {
        return 0;
    }
    
    return (a / findGCD(a, b)) * b;
}

int main() {
    int a, b;
    int lcm;

    scanf("%d %d", &a, &b);

    lcm = findMMC(a, b);

    printf("%d\n", lcm);

    return 0;
}