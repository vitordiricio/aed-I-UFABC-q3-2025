#include <stdio.h>
#include <stdlib.h>

typedef struct tItem {
    int chave;
    struct tItem *ant, *prox;
} Item;

typedef struct tLista {
    Item *primeiro, *ultimo;
    int quantidade;
} Lista;

Lista * criaListaVazia() {
    Lista *lista = (Lista *) malloc(sizeof(Lista));
    if (lista != NULL) {
        lista->primeiro = NULL;
        lista->ultimo = NULL;
        lista->quantidade = 0;
    }
    return lista;
}

Item * criaItem(int x) {
    Item *item = (Item *) malloc(sizeof(Item));
    if (item != NULL) {
        item->chave = x;
        item->ant = NULL;
        item->prox = NULL;
    }
    return item;
}

void liberaLista(Lista *lista) {
    if (lista == NULL) {
        return;
    }
    Item *current = lista->primeiro;
    Item *temp;
    while (current != NULL) {
        temp = current;
        current = current->prox;
        free(temp);
    }
    free(lista);
}

int vazia(Lista *lista) {
    if (lista == NULL) {
        return 1;
    }
    return (lista->primeiro == NULL);
}

void imprimir(Lista *lista) {
    if (lista == NULL) {
        printf("\n");
        return;
    }
    Item *current = lista->primeiro;
    while (current != NULL) {
        printf("%d ", current->chave);
        current = current->prox;
    }
    printf("\n");
}

void imprimirReverso(Lista *lista) {
    if (lista == NULL) {
        printf("\n");
        return;
    }
    Item *current = lista->ultimo;
    while (current != NULL) {
        printf("%d ", current->chave);
        current = current->ant;
    }
    printf("\n");
}

void inserir(Lista *lista, int x) {
    if (lista == NULL) {
        return;
    }

    Item *newItem = criaItem(x);
    if (newItem == NULL) {
        return;
    }

    Item *current = lista->primeiro;
    Item *previous = NULL;

    while (current != NULL && current->chave < x) {
        previous = current;
        current = current->prox;
    }

    if (current != NULL && current->chave == x) {
        free(newItem);
        return;
    }

    newItem->prox = current;
    newItem->ant = previous;

    if (previous == NULL) {
        lista->primeiro = newItem;
    } else {
        previous->prox = newItem;
    }

    if (current == NULL) {
        lista->ultimo = newItem;
    } else {
        current->ant = newItem;
    }

    lista->quantidade++;
}

void remover(Lista *lista, int x) {
    if (lista == NULL || vazia(lista)) {
        return;
    }

    Item *current = lista->primeiro;

    while (current != NULL && current->chave < x) {
        current = current->prox;
    }

    if (current == NULL || current->chave != x) {
        return;
    }

    if (current->ant == NULL) {
        lista->primeiro = current->prox;
    } else {
        current->ant->prox = current->prox;
    }

    if (current->prox == NULL) {
        lista->ultimo = current->ant;
    } else {
        current->prox->ant = current->ant;
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
            case 'E':
                scanf("%d", &x);
                remover(lista, x);
                break;
            case 'M':
                imprimir(lista);
                break;
            case 'R':
                imprimirReverso(lista);
                break;
        }
    }

    liberaLista(lista);
    return 0;
}