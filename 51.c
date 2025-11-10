#include <stdio.h>
#include <stdlib.h>

typedef struct tItem {
    int chave;
    struct tItem *prox;
} Item;

typedef struct tLista {
    Item *inicio;
    int quantidade;
} Lista;

Lista * criaListaVazia() {
    Lista *lista = (Lista *) malloc(sizeof(Lista));
    if (lista == NULL) {
        return NULL;
    }
    lista->inicio = NULL;
    lista->quantidade = 0;
    return lista;
}

Item * criaItem(int x) {
    Item *item = (Item *) malloc(sizeof(Item));
    if (item == NULL) {
        return NULL;
    }
    item->chave = x;
    item->prox = NULL;
    return item;
}

void liberaLista(Lista *lista) {
    if (lista == NULL) {
        return;
    }
    Item *current = lista->inicio;
    Item *next;
    while (current != NULL) {
        next = current->prox;
        free(current);
        current = next;
    }
    free(lista);
}

int vazia(Lista *lista) {
    if (lista == NULL) {
        return 1;
    }
    return (lista->inicio == NULL);
}

void imprimir(Lista *lista) {
    if (lista == NULL) {
        printf("\n");
        return;
    }
    Item *current = lista->inicio;
    while (current != NULL) {
        printf("%d", current->chave);
        if (current->prox != NULL) {
            printf(" ");
        }
        current = current->prox;
    }
    printf("\n");
}

int buscar(Lista *lista, int x) {
    if (lista == NULL) {
        return 0;
    }
    Item *current = lista->inicio;
    while (current != NULL) {
        if (current->chave == x) {
            return 1;
        }
        if (current->chave > x) {
            return 0;
        }
        current = current->prox;
    }
    return 0;
}

void inserir(Lista *lista, int x) {
    if (lista == NULL) {
        return;
    }

    Item *newItem = criaItem(x);
    if (newItem == NULL) {
        return;
    }

    Item *previous = NULL;
    Item *current = lista->inicio;

    while (current != NULL && current->chave < x) {
        previous = current;
        current = current->prox;
    }

    if (current != NULL && current->chave == x) {
        free(newItem);
        return;
    }

    if (previous == NULL) {
        newItem->prox = lista->inicio;
        lista->inicio = newItem;
    } else {
        newItem->prox = current;
        previous->prox = newItem;
    }
    lista->quantidade++;
}

void remover(Lista *lista, int x) {
    if (lista == NULL || vazia(lista)) {
        return;
    }

    Item *previous = NULL;
    Item *current = lista->inicio;

    while (current != NULL && current->chave < x) {
        previous = current;
        current = current->prox;
    }

    if (current == NULL || current->chave != x) {
        return;
    }

    if (previous == NULL) {
        lista->inicio = current->prox;
    } else {
        previous->prox = current->prox;
    }

    free(current);
    lista->quantidade--;
}

int main() {
    char op;
    int x;
    Lista *lista = criaListaVazia();

    if (lista == NULL) {
        return 1;
    }

    while (scanf(" %c", &op) != EOF) {
        switch (op) {
            case 'I':
                scanf("%d", &x);
                inserir(lista, x);
                break;
            case 'R':
                scanf("%d", &x);
                remover(lista, x);
                break;
            case 'B':
                scanf("%d", &x);
                if (buscar(lista, x)) {
                    printf("SIM\n");
                } else {
                    printf("NAO\n");
                }
                break;
            case 'L':
                imprimir(lista);
                break;
        }
    }

    liberaLista(lista);
    return 0;
}