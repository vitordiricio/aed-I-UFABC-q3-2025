#include <stdio.h>
#include <stdlib.h>

typedef struct tItem {
    int chave;
    struct tItem *pai, *esq, *dir;
} Item;

typedef struct tArvore {
    Item *raiz;
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
    }
    return arv;
}

void liberaNos(Item *no) {
    if (no != NULL) {
        liberaNos(no->esq);
        liberaNos(no->dir);
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
}

int contaFolhasRec(Item *no) {
    if (no == NULL) {
        return 0;
    }
    
    if (no->esq == NULL && no->dir == NULL) {
        return 1;
    }

    return contaFolhasRec(no->esq) + contaFolhasRec(no->dir);
}

int contaFolhas(Arvore *arv) {
    if (arv == NULL || vazia(arv)) {
        return 0;
    }
    return contaFolhasRec(arv->raiz);
}

int main () {
    int n, i, x;
    scanf ("%d", &n);
    Arvore *arv = criaArvoreVazia ();
    if (arv == NULL) {
        return 1;
    }

    for (i = 0; i < n; i++) {
        scanf ("%d", &x);
        inserir (arv, x);
    }

    int totalFolhas = contaFolhas(arv);
    printf("%d\n", totalFolhas);
    
    liberaArvore (arv);
    return 0;
}