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
    Item *atual = lista->primeiro;
    Item *temp;
    while (atual != NULL) {
        temp = atual;
        atual = atual->prox;
        free(temp);
    }
    free(lista);
}

int estaVazia(Lista *lista) {
    if (lista == NULL) {
        return 1;
    }
    return (lista->primeiro == NULL);
}

void imprimeLista(Lista *lista) {
    if (lista == NULL) {
        printf("\n");
        return;
    }
    Item *atual = lista->primeiro;
    while (atual != NULL) {
        printf("%d ", atual->chave);
        atual = atual->prox;
    }
    printf("\n");
}

void imprimeListaReversa(Lista *lista) {
    if (lista == NULL) {
        printf("\n");
        return;
    }
    Item *atual = lista->ultimo;
    while (atual != NULL) {
        printf("%d ", atual->chave);
        atual = atual->ant;
    }
    printf("\n");
}

void inserir(Lista *lista, int x) {
    if (lista == NULL) {
        return;
    }

    Item *novoItem = criaItem(x);
    if (novoItem == NULL) {
        return;
    }

    Item *atual = lista->primeiro;
    Item *anterior = NULL;

    while (atual != NULL && atual->chave < x) {
        anterior = atual;
        atual = atual->prox;
    }

    if (atual != NULL && atual->chave == x) {
        free(novoItem);
        return;
    }

    novoItem->prox = atual;
    novoItem->ant = anterior;

    if (anterior == NULL) {
        lista->primeiro = novoItem;
    } else {
        anterior->prox = novoItem;
    }

    if (atual == NULL) {
        lista->ultimo = novoItem;
    } else {
        atual->ant = novoItem;
    }

    lista->quantidade++;
}

void remover(Lista *lista, int x) {
    if (lista == NULL || estaVazia(lista)) {
        return;
    }

    Item *atual = lista->primeiro;

    while (atual != NULL && atual->chave < x) {
        atual = atual->prox;
    }

    if (atual == NULL || atual->chave != x) {
        return;
    }

    if (atual->ant == NULL) {
        lista->primeiro = atual->prox;
    } else {
        atual->ant->prox = atual->prox;
    }

    if (atual->prox == NULL) {
        lista->ultimo = atual->ant;
    } else {
        atual->prox->ant = atual->ant;
    }

    free(atual);
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
                imprimeLista(lista);
                break;
            case 'R':
                imprimeListaReversa(lista);
                break;
        }
    }

    liberaLista(lista);
    return 0;
}
