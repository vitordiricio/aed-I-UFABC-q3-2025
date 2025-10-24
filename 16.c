#include <stdio.h>
#include <stdlib.h>

int * combina(int *v, int *w, int n, int m) {
    int *z = (int *) malloc((n + m) * sizeof(int));

    if (z == NULL) {
        return NULL;
    }

    for (int i = 0; i < n; i++) {
        z[i] = v[i];
    }

    for (int i = 0; i < m; i++) {
        z[n + i] = w[m - 1 - i];
    }

    return z;
}

int main() {
    int n, m;
    int *v, *w, *z;

    scanf("%d %d", &n, &m);

    v = (int *) malloc(n * sizeof(int));
    if (v == NULL) {
        return 1;
    }

    w = (int *) malloc(m * sizeof(int));
    if (w == NULL) {
        free(v);
        return 1;
    }

    for (int i = 0; i < n; i++) {
        scanf("%d", &v[i]);
    }

    for (int i = 0; i < m; i++) {
        scanf("%d", &w[i]);
    }

    z = combina(v, w, n, m);
    if (z == NULL) {
        free(v);
        free(w);
        return 1;
    }

    for (int i = 0; i < (n + m); i++) {
        printf("%d", z[i]);
        if (i < (n + m - 1)) {
            printf(" ");
        }
    }
    printf("\n");

    free(v);
    free(w);
    free(z);

    return 0;
}