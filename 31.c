#include <stdio.h>
#include <stdlib.h>

char * intercala(char *v1, char *v2, int q1, int q2) {
    int totalSize = q1 + q2;
    char *vr = (char *) malloc(totalSize * sizeof(char));

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

void printMergedString(char *v, int n) {
    int i;
    for (i = 0; i < n; i++) {
        printf("%c", v[i]);
    }
    printf("\n");
}

int main() {
    int q1, q2, i;
    char *v1, *v2, *vr;

    scanf("%d", &q1);
    v1 = (char *) malloc(sizeof(char) * q1);
    if (v1 == NULL) {
        return 1;
    }
    for (i = 0; i < q1; i++) {
        scanf(" %c", &v1[i]);
    }

    scanf("%d", &q2);
    v2 = (char *) malloc(sizeof(char) * q2);
    if (v2 == NULL) {
        free(v1);
        return 1;
    }
    for (i = 0; i < q2; i++) {
        scanf(" %c", &v2[i]);
    }

    vr = intercala(v1, v2, q1, q2);

    if (vr != NULL) {
        printMergedString(vr, q1 + q2);
        free(vr);
    }

    free(v1);
    free(v2);
    return 0;
}