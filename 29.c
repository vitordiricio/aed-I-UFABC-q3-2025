#include <stdio.h>
#include <stdlib.h>

int * intercala(int *v1, int *v2, int q1, int q2) {
    int totalSize = q1 + q2;
    int *vr = (int *) malloc(totalSize * sizeof(int));

    if (vr == NULL) {
        return NULL;
    }

    int i = 0;
    int j = 0;
    int k = 0;

    while (i < q1 && j < q2) {
        if (v1[i] < v2[j]) {
            vr[k] = v1[i];
            i++;
        } else {
            vr[k] = v2[j];
            j++;
        }
        k++;
    }

    while (i < q1) {
        vr[k] = v1[i];
        i++;
        k++;
    }

    while (j < q2) {
        vr[k] = v2[j];
        j++;
        k++;
    }

    return vr;
}

void printMergedArray(int *v, int n) {
    int i;
    for (i = 0; i < n; i++) {
        printf("%d\n", v[i]);
    }
}

int main() {
    int q1, q2, i;
    int *v1, *v2, *vr;

    scanf("%d", &q1);
    scanf("%d", &q2);

    v1 = (int *) malloc(sizeof(int) * q1);
    v2 = (int *) malloc(sizeof(int) * q2);

    if (v1 == NULL || v2 == NULL) {
        free(v1);
        free(v2);
        return 1;
    }

    for (i = 0; i < q1; i++) {
        scanf("%d", &v1[i]);
    }
    for (i = 0; i < q2; i++) {
        scanf("%d", &v2[i]);
    }

    vr = intercala(v1, v2, q1, q2);

    if (vr == NULL) {
        free(v1);
        free(v2);
        return 1;
    }

    printMergedArray(vr, q1 + q2);

    free(v1);
    free(v2);
    free(vr);

    return 0;
}