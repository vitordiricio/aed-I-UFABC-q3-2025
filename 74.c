#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PALAVRA 21

typedef struct tItem {
    int chave;
    char palavra[MAX_PALAVRA];
    struct tItem *pai, *esq, *dir;
} Item;

typedef struct tArvore {
    Item *raiz;
} Arvore;

int calculaChave(char *palavra) {
    int soma = 0;
    int len = strlen(palavra);
    for (int i = 0; i < len; i++) {
        soma += (int)palavra[i];
    }
    return soma;
}

Item *criaItem(char *palavra) {
    Item *novoItem = (Item *) malloc(sizeof(Item));
    if (novoItem != NULL) {
        novoItem->chave = calculaChave(palavra);
        strcpy(novoItem->palavra, palavra);
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
        printf("[%d]:%s\n", no->chave, no->palavra);
        preOrdemRec(no->esq);
        preOrdemRec(no->dir);
    }
}

void imprimirPreOrdem(Arvore *arv) {
    if (arv != NULL && !vazia(arv)) {
        preOrdemRec(arv->raiz);
    }
}

void inOrdemRec(Item *no) {
    if (no != NULL) {
        inOrdemRec(no->esq);
        printf("[%d]:%s\n", no->chave, no->palavra);
        inOrdemRec(no->dir);
    }
}

void imprimirInOrdem(Arvore *arv) {
    if (arv != NULL && !vazia(arv)) {
        inOrdemRec(arv->raiz);
    }
}

void posOrdemRec(Item *no) {
    if (no != NULL) {
        posOrdemRec(no->esq);
        posOrdemRec(no->dir);
        printf("[%d]:%s\n", no->chave, no->palavra);
    }
}

void imprimirPosOrdem(Arvore *arv) {
    if (arv != NULL && !vazia(arv)) {
        posOrdemRec(arv->raiz);
    }
}

void inserir(Arvore *arv, char *palavra) {
    if (arv == NULL) {
        return;
    }

    Item *novoItem = criaItem(palavra);
    if (novoItem == NULL) {
        return;
    }
    int chave = novoItem->chave;

    Item *atual = arv->raiz;
    Item *paiDoAtual = NULL;

    while (atual != NULL) {
        paiDoAtual = atual;
        if (chave < atual->chave) {
            atual = atual->esq;
        } else if (chave > atual->chave) {
            atual = atual->dir;
        } else {
            free(novoItem);
            return;
        }
    }

    novoItem->pai = paiDoAtual;

    if (paiDoAtual == NULL) {
        arv->raiz = novoItem;
    } else if (chave < paiDoAtual->chave) {
        paiDoAtual->esq = novoItem;
    } else {
        paiDoAtual->dir = novoItem;
    }
}

Item *buscaPosicao(Arvore *arv, int chave) {
    if (vazia(arv)) {
        return NULL;
    }
    Item *atual = arv->raiz;
    while (atual != NULL) {
        if (chave < atual->chave) {
            atual = atual->esq;
        } else if (chave > atual->chave) {
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

void remover(Arvore *arv, char *palavra) {
    if (arv == NULL || vazia(arv)) {
        return;
    }

    int chave = calculaChave(palavra);
    Item *no = buscaPosicao(arv, chave);
    
    if (no == NULL) {
        return;
    }

    if (no->esq != NULL && no->dir != NULL) {
        Item *suc = sucessor(no);
        strcpy(no->palavra, suc->palavra);
        no->chave = suc->chave;
        no = suc;
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
    char palavra[MAX_PALAVRA];
    
    Arvore *arv = criaArvoreVazia ();
    if (arv == NULL) return 1;

    while (scanf ("%s", op) != EOF) {
        if (strcmp (op, "insert") == 0) {
            scanf ("%s", palavra);
            inserir (arv, palavra);
        }
        else if (strcmp (op, "delete") == 0) {
            scanf ("%s", palavra);
            remover (arv, palavra);
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