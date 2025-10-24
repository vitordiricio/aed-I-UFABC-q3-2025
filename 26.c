#include <stdio.h>

void printArray(int *v, int n) {
    for (int i = 0; i < n; i++) {
        printf("%d", v[i]);
        if (i < n - 1) {
            printf(" ");
        }
    }
    printf("\n");
}

void readArray(int *v, int n) {
    for (int i = 0; i < n; i++) {
        scanf("%d", &v[i]);
    }
}

void insertionSort(int *A, int n, int *displacements) {
    int j, i, key;
    *displacements = 0;

    for (j = 1; j < n; j++) {
        key = A[j];
        i = j - 1;

        while (i >= 0 && key < A[i]) {
            A[i + 1] = A[i];
            (*displacements)++;
            printArray(A, n);
            i = i - 1;
        }
        A[i + 1] = key;
        printArray(A, n);
    }
}

int main() {
    int n;
    int vector[10000];
    int totalDisplacements;

    scanf("%d", &n);

    readArray(vector, n);

    insertionSort(vector, n, &totalDisplacements);

    printf("Deslocamentos: %d\n", totalDisplacements);

    return 0;
}