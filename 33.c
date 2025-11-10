#include <stdio.h>
#include <stdlib.h>

void printArray(int *v, int n) {
    for (int i = 0; i < n; i++) {
        printf("%d", v[i]);
        if (i < n - 1) {
            printf(" ");
        }
    }
    printf("\n");
}

void merge(int *v, int left, int middle, int right) {
    int size = right - left;
    int *aux = (int *) malloc(size * sizeof(int));
    if (aux == NULL) {
        return;
    }

    int i = left;
    int j = middle;
    int k = 0;

    while (i < middle && j < right) {
        if (v[i] <= v[j]) {
            aux[k] = v[i];
            i++;
        } else {
            aux[k] = v[j];
            j++;
        }
        k++;
    }

    while (i < middle) {
        aux[k] = v[i];
        i++;
        k++;
    }

    while (j < right) {
        aux[k] = v[j];
        j++;
        k++;
    }

    for (k = 0; k < size; k++) {
        v[left + k] = aux[k];
    }

    printArray(aux, size);

    free(aux);
}

void mergeSortRecursive(int *v, int left, int right) {
    if (right - left < 2) {
        return;
    }

    int middle = (left + right) / 2;
    
    mergeSortRecursive(v, left, middle);
    mergeSortRecursive(v, middle, right);
    merge(v, left, middle, right);
}

void mergeSort(int *v, int n) {
    mergeSortRecursive(v, 0, n);
}

int main() {
    int n, i;
    int *v;
    
    scanf("%d", &n);
    
    if (n <= 0) {
        return 0;
    }

    v = (int *) malloc(sizeof(int) * n);
    if (v == NULL) {
        return 1;
    }

    for (i = 0; i < n; i++) {
        scanf("%d", &v[i]);
    }

    mergeSort(v, n);
    
    free(v);
    return 0;
}