#include <stdio.h>
#include <stdlib.h>

void printArray(int *v, int e, int d) {
    for (int i = e; i < d; i++) {
        printf("%d", v[i]);
        if (i < d - 1) {
            printf(" ");
        }
    }
    printf("\n");
}

void swap(int *v, int i, int j) {
    int temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}

int partition(int *v, int e, int d) {
    int pivotValue = v[d - 1];
    int storeIndex = e;

    for (int j = e; j < d - 1; j++) {
        if (v[j] <= pivotValue) {
            swap(v, storeIndex, j);
            storeIndex++;
        }
    }
    swap(v, storeIndex, d - 1);
    return storeIndex;
}

void quickSortRecursive(int *v, int e, int d) {
    if (d - e < 2) {
        return;
    }

    int pivotIndex = partition(v, e, d);

    printf("Pivo: [%d] %d\n", pivotIndex, v[pivotIndex]);
    printArray(v, e, d);

    quickSortRecursive(v, e, pivotIndex);
    quickSortRecursive(v, pivotIndex + 1, d);
}

void quickSort(int *v, int n) {
    quickSortRecursive(v, 0, n);
}

int main() {
    int n, i;
    scanf("%d", &n);
    
    int *v = malloc(sizeof(int) * n);
    
    if (v == NULL && n > 0) {
        return 1;
    }

    for (i = 0; i < n; i++) {
        scanf("%d", &v[i]);
    }
    
    quickSort(v, n);
    
    printArray(v, 0, n);
    
    free(v);
    return 0;
}