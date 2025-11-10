#include <stdio.h>
#include <stdlib.h>

typedef struct tItem {
    int chave;
    struct tItem *pai, *esq, *dir;
} Item;

typedef struct tArvore {
    Item *raiz;
    int quantidade;
} Arvore;

Item *criaItem(int x) {
    Item *novoItem = (Item *) malloc(sizeof(Item));
    if (novoItem != NULL) {
        novoItem->chave = x;
        novoItem->pai = NULL;
        novoItem->esq = NULL;
        novoItem->dir = NULL;
    }
    return novoItem;
}

Arvore *criaArvoreVazia() {
    Arvore *arv = (Arvore *) malloc(sizeof(Arvore));
    if (arv != NULL) {
        arv->raiz = NULL;
        arv->quantidade = 0;
    }
    return arv;
}

void liberaNos(Item *no) {
    if (no != NULL) {
        liberaNos(no->esq);
        liberaNos(no->dir);
        printf("libera: %d\n", no->chave);
        free(no);
    }
}

void liberaArvore(Arvore *arvore) {
    if (arvore != NULL) {
        liberaNos(arvore->raiz);
        free(arvore);
    }
}

int vazia(Arvore *arv) {
    if (arv == NULL) {
        return 1;
    }
    return (arv->raiz == NULL);
}

static int primeiroElementoImpresso;

void imprimirRec(Item *no) {
    if (no == NULL) {
        return;
    }
    
    imprimirRec(no->esq);
    
    if (primeiroElementoImpresso) {
        printf("%d", no->chave);
        primeiroElementoImpresso = 0;
    } else {
        printf(" %d", no->chave);
    }
    
    imprimirRec(no->dir);
}

void imprimir(Arvore *arv) {
    if (arv == NULL || vazia(arv)) {
        return;
    }
    primeiroElementoImpresso = 1;
    imprimirRec(arv->raiz);
    printf("\n");
}

void inserir(Arvore *arv, int x) {
    if (arv == NULL) {
        return;
    }

    Item *novoItem = criaItem(x);
    if (novoItem == NULL) {
        return;
    }

    Item *atual = arv->raiz;
    Item *paiDoAtual = NULL;

    while (atual != NULL) {
        paiDoAtual = atual;
        if (x < atual->chave) {
            atual = atual->esq;
        } else if (x > atual->chave) {
            atual = atual->dir;
        } else {
            free(novoItem);
            return;
        }
    }

    novoItem->pai = paiDoAtual;

    if (paiDoAtual == NULL) {
        arv->raiz = novoItem;
    } else if (x < paiDoAtual->chave) {
        paiDoAtual->esq = novoItem;
    } else {
        paiDoAtual->dir = novoItem;
    }
    
    arv->quantidade++;
}

int main () {
    int n, i, x;
    scanf ("%d", &n);
    Arvore *arv = criaArvoreVazia ();
    for (i = 0; i < n; i++) {
        scanf ("%d", &x);
        inserir (arv, x);
    }
    imprimir (arv);
    liberaArvore (arv);
    return 0;
}