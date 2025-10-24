#include <stdio.h>

#define MAX_SIZE 100

void readMatrix(int matrix[][MAX_SIZE], int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &matrix[i][j]);
        }
    }
}

void addMatrices(int a[][MAX_SIZE], int b[][MAX_SIZE], int result[][MAX_SIZE], int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            result[i][j] = a[i][j] + b[i][j];
        }
    }
}

void printMatrix(int matrix[][MAX_SIZE], int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d", matrix[i][j]);
            if (j < n - 1) {
                printf(" ");
            }
        }
        printf("\n");
    }
}

int main() {
    int n;
    int matrixA[MAX_SIZE][MAX_SIZE];
    int matrixB[MAX_SIZE][MAX_SIZE];
    int resultMatrix[MAX_SIZE][MAX_SIZE];

    scanf("%d", &n);

    readMatrix(matrixA, n);
    readMatrix(matrixB, n);

    addMatrices(matrixA, matrixB, resultMatrix, n);

    printMatrix(resultMatrix, n);

    return 0;
}