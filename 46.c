#include <stdio.h>
#include <stdlib.h>

typedef struct tFilaCircular {
    int *itens;
    int inicio, fim;
    int tamanho;
} FilaCircular;

FilaCircular * criaFilaCircularVazia(int tamanho) {
    FilaCircular *fila = (FilaCircular *) malloc(sizeof(FilaCircular));
    if (fila == NULL) {
        return NULL;
    }

    fila->itens = (int *) malloc(tamanho * sizeof(int));
    if (fila->itens == NULL) {
        free(fila);
        return NULL;
    }

    fila->tamanho = tamanho;
    fila->inicio = -1;
    fila->fim = -1;
    return fila;
}

void liberaFilaCircular(FilaCircular *fila) {
    if (fila != NULL) {
        free(fila->itens);
        free(fila);
    }
}

int vazia(FilaCircular *fila) {
    if (fila == NULL) {
        return 1;
    }
    return (fila->inicio == -1);
}

int cheia(FilaCircular *fila) {
    if (fila == NULL || fila->tamanho == 0) {
        return 1;
    }
    return ((fila->fim + 1) % fila->tamanho == fila->inicio);
}

void enfileirar(FilaCircular *fila, int x) {
    if (fila == NULL || cheia(fila)) {
        return;
    }

    if (vazia(fila)) {
        fila->inicio = 0;
    }

    fila->fim = (fila->fim + 1) % fila->tamanho;
    fila->itens[fila->fim] = x;
}

int desenfileirar(FilaCircular *fila) {
    if (fila == NULL || vazia(fila)) {
        return -1;
    }

    int item = fila->itens[fila->inicio];

    if (fila->inicio == fila->fim) {
        fila->inicio = -1;
        fila->fim = -1;
    } else {
        fila->inicio = (fila->inicio + 1) % fila->tamanho;
    }

    return item;
}

int main() {
    char op;
    int x, n;
    scanf("%d", &n);

    FilaCircular *fila = criaFilaCircularVazia(n);
    if (fila == NULL) {
        return 1;
    }

    while (scanf(" %c", &op) != EOF) {
        switch (op) {
            case 'E':
                scanf("%d", &x);
                enfileirar(fila, x);
                break;
            case 'D':
                int valorDesenfileirado = desenfileirar(fila);
                if (valorDesenfileirado != -1) {
                    printf("%d\n", valorDesenfileirado);
                }
                break;
        }
    }

    liberaFilaCircular(fila);
    return 0;
}