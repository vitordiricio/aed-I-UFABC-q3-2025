#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM_MAX_PALAVRA 101

typedef struct tItem {
    char chave[TAM_MAX_PALAVRA];
    int contagem;
    struct tItem *ant;
    struct tItem *prox;
} Item;

typedef struct tLista {
    Item *primeiro;
    Item *ultimo;
} Lista;

Lista *criarListaVazia() {
    Lista *lista = (Lista *) malloc(sizeof(Lista));
    if (lista != NULL) {
        lista->primeiro = NULL;
        lista->ultimo = NULL;
    }
    return lista;
}

Item *criarItem(char *palavra) {
    Item *item = (Item *) malloc(sizeof(Item));
    if (item != NULL) {
        strcpy(item->chave, palavra);
        item->contagem = 1;
        item->ant = NULL;
        item->prox = NULL;
    }
    return item;
}

void liberarLista(Lista *lista) {
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

Item *buscarItem(Lista *lista, char *palavra) {
    Item *atual = lista->primeiro;
    while (atual != NULL) {
        if (strcmp(atual->chave, palavra) == 0) {
            return atual;
        }
        atual = atual->prox;
    }
    return NULL;
}

void promoverItem(Lista *lista, Item *item) {
    while (item->ant != NULL && item->contagem > item->ant->contagem) {
        Item *itemAnt = item->ant;

        itemAnt->prox = item->prox;
        item->ant = itemAnt->ant;

        if (item->prox != NULL) {
            item->prox->ant = itemAnt;
        }

        if (itemAnt->ant != NULL) {
            itemAnt->ant->prox = item;
        }

        item->prox = itemAnt;
        itemAnt->ant = item;

        if (lista->primeiro == itemAnt) {
            lista->primeiro = item;
        }
        if (lista->ultimo == item) {
            lista->ultimo = itemAnt;
        }
    }
}

void processarBusca(Lista *lista, char *palavra) {
    Item *encontrado = buscarItem(lista, palavra);

    if (encontrado != NULL) {
        encontrado->contagem++;
        promoverItem(lista, encontrado);
    } else {
        Item *novo = criarItem(palavra);
        if (novo == NULL) {
            return;
        }

        if (lista->primeiro == NULL) {
            lista->primeiro = novo;
            lista->ultimo = novo;
        } else {
            lista->ultimo->prox = novo;
            novo->ant = lista->ultimo;
            lista->ultimo = novo;
        }
    }
}

void imprimirLista(Lista *lista) {
    if (lista == NULL) {
        return;
    }
    Item *atual = lista->primeiro;
    while (atual != NULL) {
        printf("%s [%d]\n", atual->chave, atual->contagem);
        atual = atual->prox;
    }
}

int main() {
    char palavra[TAM_MAX_PALAVRA];
    Lista *lista = criarListaVazia();
    if (lista == NULL) {
        return 1;
    }

    while (scanf("%s", palavra) != EOF) {
        processarBusca(lista, palavra);
    }

    imprimirLista(lista);
    liberarLista(lista);

    return 0;
}
