#include <stdio.h>
#include <stdlib.h>

typedef struct tLista {
    int *itens;
    int quantidade;
    int tamanho;
} Lista;

Lista * criaListaVazia(int tamanho) {
    Lista *lista = (Lista *) malloc(sizeof(Lista));
    if (lista == NULL) {
        return NULL;
    }

    lista->itens = (int *) malloc(tamanho * sizeof(int));
    if (lista->itens == NULL) {
        free(lista);
        return NULL;
    }

    lista->quantidade = 0;
    lista->tamanho = tamanho;
    return lista;
}

void liberaLista(Lista *lista) {
    if (lista != NULL) {
        free(lista->itens);
        free(lista);
    }
}

int cheia(Lista *lista) {
    if (lista == NULL) {
        return 0;
    }
    return lista->quantidade == lista->tamanho;
}

int vazia(Lista *lista) {
    if (lista == NULL) {
        return 1;
    }
    return lista->quantidade == 0;
}

void inserir(Lista *lista, int x) {
    if (lista == NULL || cheia(lista)) {
        return;
    }

    int left = 0;
    int right = lista->quantidade - 1;
    int pos = 0;

    while (left <= right) {
        int middle = left + (right - left) / 2;
        if (lista->itens[middle] == x) {
            return;
        }
        if (lista->itens[middle] < x) {
            left = middle + 1;
            pos = left;
        } else {
            right = middle - 1;
            pos = middle;
        }
    }

    for (int i = lista->quantidade; i > pos; i--) {
        lista->itens[i] = lista->itens[i - 1];
    }

    lista->itens[pos] = x;
    lista->quantidade++;
}

void remover(Lista *lista, int x) {
    if (lista == NULL || vazia(lista)) {
        return;
    }

    int pos = -1;
    int left = 0;
    int right = lista->quantidade - 1;

    while (left <= right) {
        int middle = left + (right - left) / 2;
        if (lista->itens[middle] == x) {
            pos = middle;
            break;
        }
        if (lista->itens[middle] < x) {
            left = middle + 1;
        } else {
            right = middle - 1;
        }
    }

    if (pos == -1) {
        return;
    }

    for (int i = pos; i < lista->quantidade - 1; i++) {
        lista->itens[i] = lista->itens[i + 1];
    }

    lista->quantidade--;
}

int main() {
    int q, i, x;
    scanf("%d", &q);

    Lista *lista = criaListaVazia(q);
    if (lista == NULL) {
        return 1;
    }

    char op;
    for (i = 0; i < q; i++) {
        scanf(" %c", &op);
        scanf("%d", &x);

        if (op == 'I') {
            inserir(lista, x);
        } else if (op == 'E') {
            remover(lista, x);
        }
    }

    for (i = 0; i < lista->quantidade; i++) {
        printf("%d\n", lista->itens[i]);
    }

    liberaLista(lista);

    return 0;
}