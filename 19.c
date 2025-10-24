#include <stdio.h>

#define MAX_SIZE 100

void readMatrix(int matrix[][MAX_SIZE], int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &matrix[i][j]);
        }
    }
}

double calculateResultBelowDiagonal(int matrix[][MAX_SIZE], int n, char operation) {
    double sum = 0.0;
    int count = 0;

    for (int i = 1; i < n; i++) {
        for (int j = 0; j < i; j++) {
            sum += matrix[i][j];
            count++;
        }
    }

    if (operation == 'S') {
        return sum;
    } else {
        return sum / count;
    }
}

int main() {
    char operation;
    int n;
    int matrix[MAX_SIZE][MAX_SIZE];
    double result;

    scanf(" %c", &operation);
    scanf("%d", &n);

    readMatrix(matrix, n);

    result = calculateResultBelowDiagonal(matrix, n, operation);

    printf("%.1f\n", result);

    return 0;
}