#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct tItem {
    char nome[101];
    int rank;
    struct tItem *ant, *prox;
} Item;

typedef struct tLista {
    Item *primeiro, *ultimo;
} Lista;

Lista * criaListaVazia() {
    Lista *lista = (Lista *) malloc(sizeof(Lista));
    if (lista != NULL) {
        lista->primeiro = NULL;
        lista->ultimo = NULL;
    }
    return lista;
}

Item * criaItem(char *s) {
    Item *item = (Item *) malloc(sizeof(Item));
    if (item != NULL) {
        strcpy(item->nome, s);
        item->rank = 1;
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
        return;
    }
    Item *current = lista->primeiro;
    while (current != NULL) {
        printf("%s [%d]\n", current->nome, current->rank);
        current = current->prox;
    }
}

Item * buscaNome(Lista *lista, char *x) {
    if (lista == NULL) {
        return NULL;
    }
    Item *current = lista->primeiro;
    while (current != NULL) {
        if (strcmp(current->nome, x) == 0) {
            return current;
        }
        current = current->prox;
    }
    return NULL;
}

void troca(Lista *lista, Item *ant, Item *atu) {
    if (ant == NULL || atu == NULL || lista == NULL) {
        return;
    }

    if (ant->ant != NULL) {
        ant->ant->prox = atu;
    } else {
        lista->primeiro = atu;
    }

    if (atu->prox != NULL) {
        atu->prox->ant = ant;
    } else {
        lista->ultimo = ant;
    }

    atu->ant = ant->ant;
    ant->prox = atu->prox;

    atu->prox = ant;
    ant->ant = atu;
}

void inserir(Lista *lista, char *s) {
    if (lista == NULL) {
        return;
    }

    Item *item = buscaNome(lista, s);

    if (item == NULL) {
        Item *newItem = criaItem(s);
        if (newItem == NULL) {
            return;
        }

        if (vazia(lista)) {
            lista->primeiro = newItem;
            lista->ultimo = newItem;
        } else {
            lista->ultimo->prox = newItem;
            newItem->ant = lista->ultimo;
            lista->ultimo = newItem;
        }
    } else {
        item->rank++;
        while (item->ant != NULL && item->rank > item->ant->rank) {
            troca(lista, item->ant, item);
        }
    }
}

int main() {
    char s[101];
    Lista *lista = criaListaVazia();
    if (lista == NULL) {
        return 1;
    }
    
    while (scanf("%s", s) != EOF) {
        inserir(lista, s);
    }
    
    imprimir(lista);
    liberaLista(lista);
    
    return 0;
}