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
    Item *atual = fila->inicio;
    Item *temp;
    while (atual != NULL) {
        temp = atual;
        atual = atual->prox;
        free(temp);
    }
    free(fila);
}

int estaVazia(Fila *fila) {
    if (fila == NULL) {
        return 1;
    }
    return (fila->inicio == NULL);
}

void imprimeFila(Fila *fila) {
    if (estaVazia(fila)) {
        return;
    }

    Item *atual = fila->inicio;
    while (atual != NULL) {
        printf("%d", atual->chave);
        if (atual->prox != NULL) {
            printf(" ");
        }
        atual = atual->prox;
    }
    printf("\n");
}

void enfileira(Fila *fila, int x) {
    if (fila == NULL) {
        return;
    }

    Item *novoItem = criaItem(x);
    if (novoItem == NULL) {
        return;
    }

    if (estaVazia(fila)) {
        fila->inicio = novoItem;
        fila->fim = novoItem;
    } else {
        fila->fim->prox = novoItem;
        fila->fim = novoItem;
    }
}

int desenfileira(Fila *fila) {
    if (estaVazia(fila)) {
        return -1;
    }

    Item *temp = fila->inicio;
    int chaveRemovida = temp->chave;

    fila->inicio = temp->prox;

    if (fila->inicio == NULL) {
        fila->fim = NULL;
    }

    free(temp);
    return chaveRemovida;
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
                enfileira(fila, x);
                break;
            case 'D': ;
                int valorRemovido = desenfileira(fila);
                if (valorRemovido != -1) {
                    printf("<%d>\n", valorRemovido);
                }
                break;
            case 'M':
                imprimeFila(fila);
                break;
        }
    }

    liberaFila(fila);
    return 0;
}
