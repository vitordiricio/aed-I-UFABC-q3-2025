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
        return 1;
    }
    return (lista->quantidade == lista->tamanho);
}

int vazia(Lista *lista) {
    if (lista == NULL) {
        return 1;
    }
    return (lista->quantidade == 0);
}

int buscarPosicao(Lista *lista, int x) {
    int left = 0;
    int right = lista->quantidade - 1;

    while (left <= right) {
        int middle = left + (right - left) / 2;
        if (lista->itens[middle] == x) {
            return middle;
        }
        if (lista->itens[middle] < x) {
            left = middle + 1;
        } else {
            right = middle - 1;
        }
    }
    return -1;
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

    int pos = buscarPosicao(lista, x);

    if (pos == -1) {
        return;
    }

    for (int i = pos; i < lista->quantidade - 1; i++) {
        lista->itens[i] = lista->itens[i + 1];
    }

    lista->quantidade--;
}

void buscar(Lista *lista, int x) {
    if (buscarPosicao(lista, x) != -1) {
        printf("SIM\n");
    } else {
        printf("NAO\n");
    }
}

void mostrar(Lista *lista) {
    if (lista == NULL) {
        return;
    }

    for (int i = 0; i < lista->quantidade; i++) {
        printf("%d", lista->itens[i]);
        if (i < lista->quantidade - 1) {
            printf(" ");
        }
    }
    printf("\n");
}

int main() {
    int n, x;
    char op;

    scanf("%d", &n);

    Lista *lista = criaListaVazia(n);
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
                buscar(lista, x);
                break;
            case 'M':
                mostrar(lista);
                break;
        }
    }

    liberaLista(lista);

    return 0;
}