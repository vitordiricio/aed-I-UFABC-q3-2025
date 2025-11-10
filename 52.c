#include <stdio.h>
#include <stdlib.h>

typedef struct tItem {
    int chave;
    struct tItem *prox;
} Item;

typedef struct tPilha {
    Item *topo;
    int quantidade;
} Pilha;

Pilha * criaPilhaVazia() {
    Pilha *pilha = (Pilha *) malloc(sizeof(Pilha));
    if (pilha != NULL) {
        pilha->topo = NULL;
        pilha->quantidade = 0;
    }
    return pilha;
}

Item * criaItem(int x) {
    Item *item = (Item *) malloc(sizeof(Item));
    if (item != NULL) {
        item->chave = x;
        item->prox = NULL;
    }
    return item;
}

void liberaPilha(Pilha *pilha) {
    if (pilha == NULL) {
        return;
    }
    Item *atual = pilha->topo;
    Item *temp;
    while (atual != NULL) {
        temp = atual;
        atual = atual->prox;
        free(temp);
    }
    free(pilha);
}

int estaVazia(Pilha *pilha) {
    if (pilha == NULL) {
        return 1;
    }
    return (pilha->topo == NULL);
}

void imprimePilha(Pilha *pilha) {
    if (estaVazia(pilha)) {
        return;
    }

    Item *atual = pilha->topo;
    while (atual != NULL) {
        printf("%d", atual->chave);
        if (atual->prox != NULL) {
            printf(" ");
        }
        atual = atual->prox;
    }
    printf("\n");
}

void empilha(Pilha *pilha, int x) {
    if (pilha == NULL) {
        return;
    }
    Item *novoItem = criaItem(x);
    if (novoItem == NULL) {
        return;
    }

    novoItem->prox = pilha->topo;
    pilha->topo = novoItem;
    pilha->quantidade++;
}

int desempilha(Pilha *pilha) {
    if (estaVazia(pilha)) {
        return -1;
    }

    Item *temp = pilha->topo;
    int chaveRemovida = temp->chave;

    pilha->topo = temp->prox;
    pilha->quantidade--;
    free(temp);

    return chaveRemovida;
}

int main() {
    char op;
    int x;
    Pilha *pilha = criaPilhaVazia();
    if (pilha == NULL) {
        return 1;
    }

    while (scanf(" %c", &op) != EOF) {
        switch (op) {
            case 'E':
                scanf("%d", &x);
                empilha(pilha, x);
                break;
            case 'D': ;
                int valorRemovido = desempilha(pilha);
                if (valorRemovido != -1) {
                    printf("[%d]\n", valorRemovido);
                }
                break;
            case 'M':
                imprimePilha(pilha);
                break;
        }
    }

    liberaPilha(pilha);
    return 0;
}
