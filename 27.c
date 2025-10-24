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

void selectionSort(int *v, int n, int *ifExecutions) {
    int i, j, minIndex, tmp;
    *ifExecutions = 0;

    for (i = 0; i < n - 1; i++) {
        minIndex = i;
        for (j = i + 1; j < n; j++) {
            (*ifExecutions)++;
            if (v[j] < v[minIndex]) {
                minIndex = j;
            }
        }

        tmp = v[i];
        v[i] = v[minIndex];
        v[minIndex] = tmp;

        printArray(v, n);
    }
}

int main() {
    int n;
    int vector[10000];
    int totalIfs = 0;

    scanf("%d", &n);

    readArray(vector, n);

    selectionSort(vector, n, &totalIfs);

    printf("Total de IFs executados: %d\n", totalIfs);

    return 0;
}