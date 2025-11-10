#include <stdio.h>
#include <stdlib.h>

typedef struct tHeap {
    int *v;
    int tamanho;
    int quantidade;
} Heap;

void troca(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

Heap *criaHeapVazio(int tam) {
    Heap *h = (Heap *) malloc(sizeof(Heap));
    if (h == NULL) {
        return NULL;
    }

    h->v = (int *) malloc(tam * sizeof(int));
    if (h->v == NULL) {
        free(h);
        return NULL;
    }

    h->tamanho = tam;
    h->quantidade = 0;
    return h;
}

void liberaHeap(Heap *h) {
    if (h != NULL) {
        free(h->v);
        free(h);
    }
}

int pai(int i) {
    return (i - 1) / 2;
}

int filhoEsq(int i) {
    return 2 * i + 1;
}

int filhoDir(int i) {
    return 2 * i + 2;
}

int ultimoPai(Heap *h) {
    if (h == NULL || h->quantidade == 0) {
        return -1;
    }
    return pai(h->quantidade - 1);
}

void desceChave(Heap *h, int indicePai) {
    int esq = filhoEsq(indicePai);
    int dir = filhoDir(indicePai);
    int menor = indicePai;

    if (esq < h->quantidade && h->v[esq] < h->v[menor]) {
        menor = esq;
    }

    if (dir < h->quantidade && h->v[dir] < h->v[menor]) {
        menor = dir;
    }

    if (menor != indicePai) {
        troca(&h->v[indicePai], &h->v[menor]);
        desceChave(h, menor);
    }
}

void constroiHeap(Heap *h) {
    int i;
    for (i = ultimoPai(h); i >= 0; i--) {
        desceChave(h, i);
    }
}

void imprime(int *v, int n) {
    int i;
    for (i = 0; i < n; i++) {
        printf("%d", v[i]);
        if (i < n - 1) {
            printf(" ");
        }
    }
    printf("\n");
}

int main () {
    int n, i;
    scanf ("%d", &n);
    while (n != 0) {
        Heap *h = criaHeapVazio (n);
        if (h == NULL) return 1;
        
        for (i = 0; i < n; i++) {
            scanf ("%d", &h->v[i]);
        }
        h->quantidade = n;
        
        constroiHeap (h);
        imprime (h->v, h->quantidade);
        
        liberaHeap (h);
        scanf ("%d", &n);
    }
    return 0;
}