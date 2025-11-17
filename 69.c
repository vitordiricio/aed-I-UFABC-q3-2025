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

Item *buscaPosicao(Arvore *arv, int x) {
    if (vazia(arv)) {
        return NULL;
    }

    Item *atual = arv->raiz;
    while (atual != NULL) {
        if (x < atual->chave) {
            atual = atual->esq;
        } else if (x > atual->chave) {
            atual = atual->dir;
        } else {
            return atual;
        }
    }
    return NULL;
}

Item *antecessor(Item *i) {
    if (i == NULL || i->esq == NULL) {
        return NULL;
    }
    
    Item *atual = i->esq;
    while (atual->dir != NULL) {
        atual = atual->dir;
    }
    return atual;
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
    
    while (scanf ("%d", &x) != EOF) {
        Item *it = buscaPosicao (arv, x);
        if (it != NULL && it->chave == x) {
            Item *ant = antecessor (it);
            if (ant != NULL) {
                printf ("Antecessor de %d: %d\n", x, ant->chave);
            }
            else {
                printf ("Nao ha antecessor para a chave pesquisada.\n");
            }
        }
        else {
            printf ("Chave nao encontrada.\n");
        }
    }
    
    liberaArvore (arv);
    return 0;
}