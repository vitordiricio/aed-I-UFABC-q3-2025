#include <stdio.h>
#include <stdlib.h>

void intercala(int *v, int q1, int q2) {
    int totalSize = q1 + q2;
    int *vaux = (int *) malloc(totalSize * sizeof(int));

    if (vaux == NULL) {
        return;
    }

    int i = 0;
    int j = q1;
    int k = 0;

    while (i < q1 && j < totalSize) {
        if (v[i] < v[j]) {
            vaux[k] = v[i];
            i++;
        } else {
            vaux[k] = v[j];
            j++;
        }
        k++;
    }

    while (i < q1) {
        vaux[k] = v[i];
        i++;
        k++;
    }

    while (j < totalSize) {
        vaux[k] = v[j];
        j++;
        k++;
    }

    for (k = 0; k < totalSize; k++) {
        v[k] = vaux[k];
    }

    free(vaux);
}

void printMergedArray(int *v, int n) {
    for (int i = 0; i < n; i++) {
        printf("%d\n", v[i]);
    }
}

int main() {
    int q1, q2, i;
    int *v;

    scanf("%d", &q1);
    scanf("%d", &q2);

    int totalSize = q1 + q2;
    v = (int *) malloc(sizeof(int) * totalSize);

    if (v == NULL) {
        return 1;
    }

    for (i = 0; i < q1; i++) {
        scanf("%d", &v[i]);
    }
    for (; i < totalSize; i++) {
        scanf("%d", &v[i]);
    }

    intercala(v, q1, q2);

    printMergedArray(v, totalSize);

    free(v);
    return 0;
}