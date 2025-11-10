#include <stdio.h>
#include <stdlib.h>

typedef struct tPilha {
    int *itens;
    int topo;
    int tamanho;
} Pilha;

Pilha * criaPilhaVazia(int tamanho) {
    Pilha *pilha = (Pilha *) malloc(sizeof(Pilha));
    if (pilha == NULL) {
        return NULL;
    }

    pilha->itens = (int *) malloc(tamanho * sizeof(int));
    if (pilha->itens == NULL) {
        free(pilha);
        return NULL;
    }

    pilha->topo = 0;
    pilha->tamanho = tamanho;
    return pilha;
}

void liberaPilha(Pilha *pilha) {
    if (pilha != NULL) {
        free(pilha->itens);
        free(pilha);
    }
}

int cheia(Pilha *pilha) {
    if (pilha == NULL) {
        return 1;
    }
    return (pilha->topo == pilha->tamanho);
}

int vazia(Pilha *pilha) {
    if (pilha == NULL) {
        return 1;
    }
    return (pilha->topo == 0);
}

void empilha(Pilha *pilha, int x) {
    if (pilha == NULL || cheia(pilha)) {
        return;
    }
    pilha->itens[pilha->topo] = x;
    pilha->topo++;
}

int desempilha(Pilha *pilha) {
    if (pilha == NULL || vazia(pilha)) {
        return -1;
    }
    pilha->topo--;
    return pilha->itens[pilha->topo];
}

void imprimePilhaTopo(Pilha *pilha) {
    if (pilha == NULL || vazia(pilha)) {
        return;
    }
    for (int i = pilha->topo - 1; i >= 0; i--) {
        printf("%d\n", pilha->itens[i]);
    }
}

void imprimePilhaBase(Pilha *pilha) {
    if (pilha == NULL || vazia(pilha)) {
        return;
    }
    for (int i = 0; i < pilha->topo; i++) {
        printf("%d\n", pilha->itens[i]);
    }
}

int main() {
    char op;
    int n, x;
    scanf("%d", &n);

    Pilha *pilha = criaPilhaVazia(n);
    if (pilha == NULL) {
        return 1;
    }

    while (scanf(" %c", &op) != EOF) {
        switch (op) {
            case 'E':
                scanf("%d", &x);
                empilha(pilha, x);
                break;
            case 'D':
                desempilha(pilha);
                break;
            case 'T':
                imprimePilhaTopo(pilha);
                break;
            case 'B':
                imprimePilhaBase(pilha);
                break;
        }
    }

    liberaPilha(pilha);
    return 0;
}