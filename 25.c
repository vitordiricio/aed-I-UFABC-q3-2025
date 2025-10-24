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

void bubbleSort(int *v, int n, int *ifExecutions, int *ifSatisfied) {
    int i, j, aux;
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - 1 - i; j++) {
            (*ifExecutions)++;
            
            if (v[j] > v[j + 1]) {
                (*ifSatisfied)++;
                
                aux = v[j];
                v[j] = v[j + 1];
                v[j + 1] = aux;
                
                printArray(v, n);
            }
        }
    }
}

int main() {
    int n;
    int vector[10000];
    int totalIfs = 0;
    int satisfiedIfs = 0;

    scanf("%d", &n);
    
    readArray(vector, n);

    bubbleSort(vector, n, &totalIfs, &satisfiedIfs);

    printf("Total de IFs executados: %d\n", totalIfs);
    printf("Total de IFs satisfeitos: %d\n", satisfiedIfs);

    return 0;
}