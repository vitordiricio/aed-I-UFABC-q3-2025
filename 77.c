#include <stdio.h>
#include <stdlib.h>

typedef struct tItem {
    int chave;
    struct tItem *pai, *esq, *dir;
    int altura;
} No;

typedef struct tArvore {
    No *raiz;
} Arvore;

No *criaNo(int x) {
    No *novoNo = (No *) malloc(sizeof(No));
    if (novoNo != NULL) {
        novoNo->chave = x;
        novoNo->pai = NULL;
        novoNo->esq = NULL;
        novoNo->dir = NULL;
        novoNo->altura = 0;
    }
    return novoNo;
}

Arvore *criaArvoreVazia() {
    Arvore *arv = (Arvore *) malloc(sizeof(Arvore));
    if (arv != NULL) {
        arv->raiz = NULL;
    }
    return arv;
}

void liberaNos(No *no) {
    if (no != NULL) {
        liberaNos(no->esq);
        liberaNos(no->dir);
        free(no);
    }
}

void liberaArvore(Arvore *arv) {
    if (arv != NULL) {
        liberaNos(arv->raiz);
        free(arv);
    }
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

int altura(No *no) {
    if (no == NULL) {
        return -1;
    }
    return no->altura;
}

void atualizaAltura(No *no) {
    if (no != NULL) {
        no->altura = 1 + max(altura(no->esq), altura(no->dir));
    }
}

int fatorBalanceamento(No *no) {
    if (no == NULL) {
        return 0;
    }
    return altura(no->esq) - altura(no->dir);
}

void inserir(Arvore *arv, int x) {
    if (arv == NULL) {
        return;
    }

    No *novoNo = criaNo(x);
    if (novoNo == NULL) {
        return;
    }

    No *atual = arv->raiz;
    No *paiDoAtual = NULL;

    while (atual != NULL) {
        paiDoAtual = atual;
        if (x < atual->chave) {
            atual = atual->esq;
        } else if (x > atual->chave) {
            atual = atual->dir;
        } else {
            free(novoNo);
            return;
        }
    }

    novoNo->pai = paiDoAtual;

    if (paiDoAtual == NULL) {
        arv->raiz = novoNo;
    } else if (x < paiDoAtual->chave) {
        paiDoAtual->esq = novoNo;
    } else {
        paiDoAtual->dir = novoNo;
    }
}

void atualizaAlturasFB(No *no) {
    if (no == NULL) {
        return;
    }
    atualizaAlturasFB(no->esq);
    atualizaAlturasFB(no->dir);
    atualizaAltura(no);
}

void rotacaoEsquerda(Arvore *arv, No *x) {
    No *y = x->dir;
    x->dir = y->esq;
    
    if (y->esq != NULL) {
        y->esq->pai = x;
    }
    
    y->pai = x->pai;
    
    if (x->pai == NULL) {
        arv->raiz = y;
    } else if (x == x->pai->esq) {
        x->pai->esq = y;
    } else {
        x->pai->dir = y;
    }
    
    y->esq = x;
    x->pai = y;
    
    atualizaAltura(x);
    atualizaAltura(y);
}

void rotacaoDireita(Arvore *arv, No *y) {
    No *x = y->esq;
    y->esq = x->dir;
    
    if (x->dir != NULL) {
        x->dir->pai = y;
    }
    
    x->pai = y->pai;
    
    if (y->pai == NULL) {
        arv->raiz = x;
    } else if (y == y->pai->esq) {
        y->pai->esq = x;
    } else {
        y->pai->dir = x;
    }
    
    x->dir = y;
    y->pai = x;
    
    atualizaAltura(y);
    atualizaAltura(x);
}

void atualizaAlturasAteRaiz(No *no) {
    while (no != NULL) {
        atualizaAltura(no);
        no = no->pai;
    }
}

void balancearNo(Arvore *arv, No *no) {
    int fb = fatorBalanceamento(no);
    No *novoPai = NULL;
    printf("Balanceamento: %d\n", no->chave);

    if (fb < -1) {
        if (fatorBalanceamento(no->dir) <= 0) {
            printf("Caso 1\n");
            novoPai = no->dir;
            rotacaoEsquerda(arv, no);
        } else {
            printf("Caso 2\n");
            novoPai = no->dir->esq;
            rotacaoDireita(arv, no->dir);
            rotacaoEsquerda(arv, no);
        }
    } else if (fb > 1) {
        if (fatorBalanceamento(no->esq) >= 0) {
            printf("Caso 3\n");
            novoPai = no->esq;
            rotacaoDireita(arv, no);
        } else {
            printf("Caso 4\n");
            novoPai = no->esq->dir;
            rotacaoEsquerda(arv, no->esq);
            rotacaoDireita(arv, no);
        }
    }
    
    if (novoPai != NULL) {
        atualizaAlturasAteRaiz(novoPai);
    }
}

No *encontraDesbalanceado(No *no) {
    if (no == NULL) {
        return NULL;
    }
    
    No *desb = encontraDesbalanceado(no->esq);
    if (desb != NULL) {
        return desb;
    }
    
    desb = encontraDesbalanceado(no->dir);
    if (desb != NULL) {
        return desb;
    }
    
    int fb = fatorBalanceamento(no);
    if (fb > 1 || fb < -1) {
        return no;
    }
    
    return NULL;
}

void imprimirRec(No *no) {
    if (no == NULL) {
        return;
    }
    
    imprimirRec(no->esq);
    
    printf("%d[h=%d; fb=%d;", no->chave, no->altura, fatorBalanceamento(no));
    if (no->pai != NULL) {
        printf(" pai=%d;", no->pai->chave);
    }
    if (no->esq != NULL) {
        printf(" esq=%d;", no->esq->chave);
    }
    if (no->dir != NULL) {
        printf(" dir=%d;", no->dir->chave);
    }
    printf("]\n");
    
    imprimirRec(no->dir);
}

void imprimir(Arvore *arv) {
    if (arv != NULL && arv->raiz != NULL) {
        imprimirRec(arv->raiz);
    }
}

int main () {
    int n, i, x;
    scanf ("%d", &n);
    Arvore *arv = criaArvoreVazia ();
    if (arv == NULL) return 1;

    for (i = 0; i < n; i++) {
        scanf ("%d", &x);
        inserir (arv, x);
    }
    
    atualizaAlturasFB(arv->raiz);
    imprimir(arv);

    No *noDesb = encontraDesbalanceado(arv->raiz);
    if (noDesb != NULL) {
        balancearNo(arv, noDesb);
    }
    
    imprimir(arv);
    
    liberaArvore (arv);
    return 0;
}