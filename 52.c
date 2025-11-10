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
    Item *current = pilha->topo;
    Item *temp;
    while (current != NULL) {
        temp = current;
        current = current->prox;
        free(temp);
    }
    free(pilha);
}

int vazia(Pilha *pilha) {
    if (pilha == NULL) {
        return 1;
    }
    return (pilha->topo == NULL);
}

void imprimir(Pilha *pilha) {
    if (vazia(pilha)) {
        return;
    }

    Item *current = pilha->topo;
    while (current != NULL) {
        printf("%d", current->chave);
        if (current->prox != NULL) {
            printf(" ");
        }
        current = current->prox;
    }
    printf("\n");
}

void empilha(Pilha *pilha, int x) {
    if (pilha == NULL) {
        return;
    }
    Item *newItem = criaItem(x);
    if (newItem == NULL) {
        return;
    }

    newItem->prox = pilha->topo;
    pilha->topo = newItem;
    pilha->quantidade++;
}

int desempilha(Pilha *pilha) {
    if (vazia(pilha)) {
        return -1;
    }

    Item *temp = pilha->topo;
    int poppedKey = temp->chave;

    pilha->topo = temp->prox;
    pilha->quantidade--;
    free(temp);

    return poppedKey;
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
                int poppedValue = desempilha(pilha);
                if (poppedValue != -1) {
                    printf("[%d]\n", poppedValue);
                }
                break;
            case 'M':
                imprimir(pilha);
                break;
        }
    }
    
    liberaPilha(pilha);
    return 0;
}