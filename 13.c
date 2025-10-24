#include <stdio.h>

int countGreaterOrEqual(int array[], int size, int x) {
    int count = 0;
    for (int i = 0; i < size; i++) {
        if (array[i] >= x) {
            count++;
        }
    }
    return count;
}

int main() {
    int n;
    int vector[1000];
    int x;
    int result;

    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        scanf("%d", &vector[i]);
    }

    scanf("%d", &x);

    result = countGreaterOrEqual(vector, n, x);

    printf("%d\n", result);

    return 0;
}