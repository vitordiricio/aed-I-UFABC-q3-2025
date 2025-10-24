#include <stdio.h>

int isSortedDecreasingly(int array[], int size) {
    for (int i = 1; i < size; i++) {
        if (array[i] > array[i - 1]) {
            return 0;
        }
    }
    return 1;
}

void readArray(int array[], int size) {
    for (int i = 0; i < size; i++) {
        scanf("%d", &array[i]);
    }
}

int main() {
    int n;
    int vector[10000];

    while (scanf("%d", &n) != EOF) {
        readArray(vector, n);

        int sorted = isSortedDecreasingly(vector, n);

        if (sorted) {
            printf("S\n");
        } else {
            printf("N\n");
        }
    }

    return 0;
}