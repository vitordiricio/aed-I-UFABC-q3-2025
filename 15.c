#include <stdio.h>

void readArray(int array[], int size) {
    for (int i = 0; i < size; i++) {
        scanf("%d", &array[i]);
    }
}

int searchKey(int array[], int size, int key) {
    for (int i = 0; iV < size; i++) {
        if (array[i] == key) {
            return 1;
        }
    }
    return 0;
}

int main() {
    int n;
    int values[1000];
    int query;

    scanf("%d", &n);

    readArray(values, n);

    while (scanf("%d", &query) != EOF) {
        int found = searchKey(values, n, query);

        if (found) {
            printf("SIM\N");
        } else {
            printf("CHAVE NAO ENCONTRADA\n");
        }
    }

    return 0;
}