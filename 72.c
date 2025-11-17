#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

void preOrdemRec(Item *no) {
    if (no != NULL) {
        printf("%d ", no->chave);
        preOrdemRec(no->esq);
        preOrdemRec(no->dir);
    }
}

void imprimirPreOrdem(Arvore *arv) {
    if (arv != NULL && !vazia(arv)) {
        preOrdemRec(arv->raiz);
        printf("\n");
    }
}

void inOrdemRec(Item *no) {
    if (no != NULL) {
        inOrdemRec(no->esq);
        printf("%d ", no->chave);
        inOrdemRec(no->dir);
    }
}

void imprimirInOrdem(Arvore *arv) {
    if (arv != NULL && !vazia(arv)) {
        inOrdemRec(arv->raiz);
        printf("\n");
    }
}

void posOrdemRec(Item *no) {
    if (no != NULL) {
        posOrdemRec(no->esq);
        posOrdemRec(no->dir);
        printf("%d ", no->chave);
    }
}

void imprimirPosOrdem(Arvore *arv) {
    if (arv != NULL && !vazia(arv)) {
        posOrdemRec(arv->raiz);
        printf("\n");
    }
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

int remover(Arvore *arv, int x) {
    if (arv == NULL || vazia(arv)) {
        return 0;
    }

    Item *no = buscaPosicao(arv, x);
    if (no == NULL) {
        return 0;
    }

    if (no->esq != NULL && no->dir != NULL) {
        Item *suc = sucessor(no);
        int chaveSucessor = suc->chave;
        remover(arv, suc->chave);
        no->chave = chaveSucessor;
        return 1;
    }

    Item *filho = (no->esq != NULL) ? no->esq : no->dir;

    if (no->pai == NULL) {
        arv->raiz = filho;
        if (filho != NULL) {
            filho->pai = NULL;
        }
    } else {
        if (no == no->pai->esq) {
            no->pai->esq = filho;
        } else {
            no->pai->dir = filho;
        }
        if (filho != NULL) {
            filho->pai = no->pai;
        }
    }

    free(no);
    arv->quantidade--;
    return 1;
}


int main () {
    char op[20];
    int x;
    Arvore *arv = criaArvoreVazia ();
    
    while (scanf ("%s", op) != EOF) {
        if (strcmp (op, "insert") == 0) {
            scanf ("%d", &x);
            inserir (arv, x);
        }
        else if (strcmp (op, "delete") == 0) {
            scanf ("%d", &x);
            if (remover (arv, x)) {
                printf ("%d\n", x);
            }
        }
        else if (strcmp (op, "pre-order") == 0) {
            imprimirPreOrdem (arv);
        }
        else if (strcmp (op, "in-order") == 0) {
            imprimirInOrdem (arv);
        }
        else if (strcmp (op, "post-order") == 0) {
            imprimirPosOrdem (arv);
        }
    }
    
    liberaArvore (arv);
    return 0;
}