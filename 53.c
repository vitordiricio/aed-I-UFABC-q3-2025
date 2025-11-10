#include <stdio.h>
#include <stdlib.h>

typedef struct tItem {
    int chave;
    struct tItem *prox;
} Item;

typedef struct tFila {
    Item *inicio, *fim;
} Fila;

Fila * criaFilaVazia() {
    Fila *fila = (Fila *) malloc(sizeof(Fila));
    if (fila != NULL) {
        fila->inicio = NULL;
        fila->fim = NULL;
    }
    return fila;
}

Item * criaItem(int x) {
    Item *item = (Item *) malloc(sizeof(Item));
    if (item != NULL) {
        item->chave = x;
        item->prox = NULL;
    }
    return item;
}

void liberaFila(Fila *fila) {
    if (fila == NULL) {
        return;
    }
    Item *current = fila->inicio;
    Item *temp;
    while (current != NULL) {
        temp = current;
        current = current->prox;
        free(temp);
    }
    free(fila);
}

int vazia(Fila *fila) {
    if (fila == NULL) {
        return 1;
    }
    return (fila->inicio == NULL);
}

void imprimir(Fila *fila) {
    if (vazia(fila)) {
        return;
    }

    Item *current = fila->inicio;
    while (current != NULL) {
        printf("%d", current->chave);
        if (current->prox != NULL) {
            printf(" ");
        }
        current = current->prox;
    }
    printf("\n");
}

void enfileirar(Fila *fila, int x) {
    if (fila == NULL) {
        return;
    }

    Item *newItem = criaItem(x);
    if (newItem == NULL) {
        return;
    }

    if (vazia(fila)) {
        fila->inicio = newItem;
        fila->fim = newItem;
    } else {
        fila->fim->prox = newItem;
        fila->fim = newItem;
    }
}

int desenfileirar(Fila *fila) {
    if (vazia(fila)) {
        return -1;
    }

    Item *temp = fila->inicio;
    int dequeuedKey = temp->chave;

    fila->inicio = temp->prox;
    
    if (fila->inicio == NULL) {
        fila->fim = NULL;
    }

    free(temp);
    return dequeuedKey;
}

int main() {
    char op;
    int x;
    Fila *fila = criaFilaVazia();
    if (fila == NULL) {
        return 1;
    }

    while (scanf(" %c", &op) != EOF) {
        switch (op) {
            case 'E':
                scanf("%d", &x);
                enfileirar(fila, x);
                break;
            case 'D': ;
                int dequeuedValue = desenfileirar(fila);
                if (dequeuedValue != -1) {
                    printf("<%d>\n", dequeuedValue);
                }
                break;
            case 'M':
                imprimir(fila);
                break;
        }
    }
    
    liberaFila(fila);
    return 0;
}