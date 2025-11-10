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
    Item *atual = lista->primeiro;
    Item *temp;
    while (atual != NULL) {
        temp = atual;
        atual = atual->prox;
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
    Item *atual = lista->primeiro;
    while (atual != NULL) {
        printf("%s [%d]\n", atual->nome, atual->rank);
        atual = atual->prox;
    }
}

Item * buscaNome(Lista *lista, char *x) {
    if (lista == NULL) {
        return NULL;
    }
    Item *atual = lista->primeiro;
    while (atual != NULL) {
        if (strcmp(atual->nome, x) == 0) {
            return atual;
        }
        atual = atual->prox;
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
        Item *novo = criaItem(s);
        if (novo == NULL) {
            return;
        }

        if (vazia(lista)) {
            lista->primeiro = novo;
            lista->ultimo = novo;
        } else {
            lista->ultimo->prox = novo;
            novo->ant = lista->ultimo;
            lista->ultimo = novo;
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
