#include <stdio.h>

int calculateSum(int array[], int size) {
    int sum = 0;
    for (int i = 0; i < size; i++) {
        sum += array[i];
    }
    return sum;
}

int main() {
    int n;
    int vector[1000];
    int totalSum;

    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        scanf("%d", &vector[i]);
    }

    totalSum = calculateSum(vector, n);

    printf("%d\n", totalSum);

    return 0;
}