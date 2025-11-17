#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct tItem {
    char chave;
    struct tItem *pai, *esq, *dir;
} Item;

typedef struct tArvore {
    Item *raiz;
} Arvore;

Item *criaItem(char x) {
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

void preOrdemRec(Item *no) {
    if (no != NULL) {
        printf("%c ", no->chave);
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
        printf("%c ", no->chave);
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
        printf("%c ", no->chave);
    }
}

void imprimirPosOrdem(Arvore *arv) {
    if (arv != NULL && !vazia(arv)) {
        posOrdemRec(arv->raiz);
        printf("\n");
    }
}

void inserir(Arvore *arv, char x) {
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
        } else {
            atual = atual->dir;
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

Item *buscaPosicao(Arvore *arv, char x) {
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

void remover(Arvore *arv, char x) {
    if (arv == NULL || vazia(arv)) {
        return;
    }

    Item *no = buscaPosicao(arv, x);
    if (no == NULL) {
        return;
    }

    if (no->esq != NULL && no->dir != NULL) {
        Item *suc = sucessor(no);
        char chaveSucessor = suc->chave;
        remover(arv, suc->chave);
        no->chave = chaveSucessor;
        return;
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
}

int main () {
    char op[20];
    char x;
    Arvore *arv = criaArvoreVazia ();
    if (arv == NULL) return 1;

    while (scanf ("%s", op) != EOF) {
        if (strcmp (op, "insert") == 0) {
            scanf (" %c", &x);
            inserir (arv, x);
        }
        else if (strcmp (op, "delete") == 0) {
            scanf (" %c", &x);
            remover (arv, x);
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
    printf("\n");
    return 0;
}