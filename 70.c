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

void imprimirRec(Item *no) {
    if (no != NULL) {
        printf("%d ", no->chave);
        imprimirRec(no->esq);
        imprimirRec(no->dir);
    }
}

void imprimir(Arvore *arv) {
    if (arv == NULL || vazia(arv)) {
        return;
    }
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

Item *sucessor(Item *i) {
    if (i == NULL || i->dir == NULL) {
        return NULL;
    }
    
    Item *atual = i->dir;
    while (atual->esq != NULL) {
        atual = atual->esq;
    }
    return atual;
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

void remover(Arvore *arv, int x) {
    if (arv == NULL || vazia(arv)) {
        return;
    }

    Item *no = buscaPosicao(arv, x);
    if (no == NULL) {
        return;
    }

    if (no->esq == NULL && no->dir == NULL) {
        if (no->pai == NULL) {
            arv->raiz = NULL;
        } else if (no == no->pai->esq) {
            no->pai->esq = NULL;
        } else {
            no->pai->dir = NULL;
        }
        free(no);
    }
    
    else if (no->dir == NULL) {
        if (no->pai == NULL) {
            arv->raiz = no->esq;
        } else if (no == no->pai->esq) {
            no->pai->esq = no->esq;
        } else {
            no->pai->dir = no->esq;
        }
        if (no->esq != NULL) {
            no->esq->pai = no->pai;
        }
        free(no);
    }
    
    else if (no->esq == NULL) {
        if (no->pai == NULL) {
            arv->raiz = no->dir;
        } else if (no == no->pai->esq) {
            no->pai->esq = no->dir;
        } else {
            no->pai->dir = no->dir;
        }
        if (no->dir != NULL) {
            no->dir->pai = no->pai;
        }
        free(no);
    }
    
    else {
        Item *suc = sucessor(no);
        int chaveSucessor = suc->chave;
        remover(arv, suc->chave);
        no->chave = chaveSucessor;
        arv->quantidade++;
    }
    
    arv->quantidade--;
}


int main () {
    int n, m, i, x;
    scanf ("%d", &n);
    Arvore *arv = criaArvoreVazia ();
    if (arv == NULL) return 1;

    for (i = 0; i < n; i++) {
        scanf ("%d", &x);
        inserir (arv, x);
    }
    
    scanf ("%d", &m);
    for (i = 0; i < m; i++) {
        scanf ("%d", &x);
        remover (arv, x);
    }
    
    imprimir (arv);
    liberaArvore (arv);
    return 0;
}