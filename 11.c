#include <stdio.h>

int getProperDivisorSum(int n) {
    int sum = 0;
    for (int i = 1; i < n; i++) {
        if (n % i == 0) {
            sum += i;
        }
    }
    return sum;
}

int main() {
    int n;
    int divisorSum;

    scanf("%d", &n);

    divisorSum = getProperDivisorSum(n);

    if (divisorSum == n) {
        printf("SIM\n");
    } else {
        printf("NAO\n");
    }

    return 0;
}