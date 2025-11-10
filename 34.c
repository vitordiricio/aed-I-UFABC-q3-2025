#include <stdio.h>
#include <stdlib.h>

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void readArray(int *v, int n) {
    for (int i = 0; i < n; i++) {
        scanf("%d", &v[i]);
    }
}

void printArray(int *v, int n) {
    for (int i = 0; i < n; i++) {
        printf("%d", v[i]);
        if (i < n - 1) {
            printf(" ");
        }
    }
    printf("\n");
}

int partitionArray(int *v, int n, int pivotIndex) {
    int pivotValue = v[pivotIndex];
    int storeIndex = 0;
    
    swap(&v[pivotIndex], &v[n - 1]);

    for (int i = 0; i < n - 1; i++) {
        if (v[i] <= pivotValue) {
            swap(&v[storeIndex], &v[i]);
            storeIndex++;
        }
    }

    swap(&v[storeIndex], &v[n - 1]);

    return storeIndex;
}

int main() {
    int n, p;
    int *v;
    int newPivotIndex;

    scanf("%d %d", &n, &p);

    v = (int *) malloc(n * sizeof(int));
    if (v == NULL) {
        return 1;
    }

    readArray(v, n);

    newPivotIndex = partitionArray(v, n, p);

    printf("%d\n", newPivotIndex);
    printArray(v, n);

    free(v);
    return 0;
}