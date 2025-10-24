#include <stdio.h>

#define MAX_SIZE 100

void readMatrix(int matrix[][MAX_SIZE], int n, int m) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%d", &matrix[i][j]);
        }
    }
}

void findTranspose(int original[][MAX_SIZE], int transposed[][MAX_SIZE], int n, int m) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            transposed[j][i] = original[i][j];
        }
    }
}

void printTransposedMatrix(int matrix[][MAX_SIZE], int m, int n) {
    for (int i = 0; i < m; i++) {
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
    int n, m;
    int originalMatrix[MAX_SIZE][MAX_SIZE];
    int transposedMatrix[MAX_SIZE][MAX_SIZE];

    scanf("%d", &n);
    scanf("%d", &m);

    readMatrix(originalMatrix, n, m);

    findTranspose(originalMatrix, transposedMatrix, n, m);

    printTransposedMatrix(transposedMatrix, m, n);

    return 0;
}