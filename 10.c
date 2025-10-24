#include <stdio.h>

int countEvenDivisors(int n) {
    int count = 0;
    
    if (n == 0) {
        return 0;
    }

    for (int i = 1; i <= n; i++) {
        if (n % i == 0) {
            if (i % 2 == 0) {
                count++;
            }
        }
    }
    return count;
}

int main() {
    int n;
    int evenDivisors;

    scanf("%d", &n);

    evenDivisors = countEvenDivisors(n);

    printf("%d\n", evenDivisors);

    return 0;
}