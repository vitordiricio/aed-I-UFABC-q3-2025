#include <stdio.h>
#include <stdlib.h>

void mergeBipartiteString(char *v, int n, int m) {
    int totalSize = n + m;
    char *aux = (char *) malloc(totalSize * sizeof(char));

    if (aux == NULL) {
        return;
    }

    int i = 0;
    int j = n;
    int k = 0;

    while (i < n && j < totalSize) {
        if (v[i] < v[j]) {
            aux[k] = v[i];
            i++;
        } else {
            aux[k] = v[j];
            j++;
        }
        k++;
    }

    while (i < n) {
        aux[k] = v[i];
        i++;
        k++;
    }

    while (j < totalSize) {
        aux[k] = v[j];
        j++;
        k++;
    }

    for (k = 0; k < totalSize; k++) {
        v[k] = aux[k];
    }

    free(aux);
}

void printResultString(char *v, int totalSize) {
    for (int i = 0; i < totalSize; i++) {
        printf("%c", v[i]);
    }
    printf("\n");
}

int main() {
    int n, m, i;
    int totalSize;
    char *v;

    scanf("%d %d", &n, &m);
    totalSize = n + m;
    
    v = (char *) malloc(sizeof(char) * totalSize);

    if (v == NULL) {
        return 1;
    }

    for (i = 0; i < totalSize; i++) {
        scanf(" %c", &v[i]);
    }

    mergeBipartiteString(v, n, m);

    printResultString(v, totalSize);

    free(v);
    return 0;
}