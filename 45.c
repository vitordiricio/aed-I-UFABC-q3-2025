#include <stdio.h>
#include <stdlib.h>

typedef struct tFila {
    int *itens;
    int inicio, fim;
    int tamanho;
} Fila;

Fila * criaFilaVazia(int tamanho) {
    Fila *fila = (Fila *) malloc(sizeof(Fila));
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

void liberaFila(Fila *fila) {
    if (fila != NULL) {
        free(fila->itens);
        free(fila);
    }
}

int vazia(Fila *fila) {
    if (fila == NULL) {
        return 1;
    }
    return (fila->inicio == -1);
}

int cheia(Fila *fila) {
    if (fila == NULL) {
        return 1;
    }
    return (fila->fim == fila->tamanho - 1);
}

void enfileirar(Fila *fila, int x) {
    if (fila == NULL || cheia(fila)) {
        return;
    }

    if (vazia(fila)) {
        fila->inicio = 0;
    }
    
    fila->fim++;
    fila->itens[fila->fim] = x;
}

int desenfileirar(Fila *fila) {
    if (fila == NULL || vazia(fila)) {
        return -1;
    }

    int item = fila->itens[fila->inicio];

    if (fila->inicio == fila->fim) {
        fila->inicio = -1;
        fila->fim = -1;
    } else {
        fila->inicio++;
    }
    
    return item;
}

int main() {
    char op;
    int x, n;
    scanf("%d", &n);

    Fila *fila = criaFilaVazia(n);
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

    liberaFila(fila);
    return 0;
}