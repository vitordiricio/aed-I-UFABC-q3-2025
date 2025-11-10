#include <stdio.h>

long long soma(long long x, long long y) {
    return x + y;
}

int main(void) {
    long long a;
    long long b;
    scanf("%lld %lld", &a, &b);
    printf("%lld", soma(a, b));
    return 0;
}