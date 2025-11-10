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

void peneirar(Heap *h, int indicePai) {
    int esq = filhoEsq(indicePai);
    int dir = filhoDir(indicePai);
    int maior = indicePai;

    if (esq < h->quantidade && h->v[esq] > h->v[maior]) {
        maior = esq;
    }

    if (dir < h->quantidade && h->v[dir] > h->v[maior]) {
        maior = dir;
    }

    if (maior != indicePai) {
        troca(&h->v[indicePai], &h->v[maior]);
        peneirar(h, maior);
    }
}

void constroiHeap(Heap *h) {
    int i;
    for (i = ultimoPai(h); i >= 0; i--) {
        peneirar(h, i);
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

void heapSort(Heap *h) {
    if (h == NULL || h->quantidade <= 0) {
        return;
    }
    
    constroiHeap(h);
    imprime(h->v, h->tamanho);

    int i;
    for (i = h->tamanho - 1; i > 0; i--) {
        troca(&h->v[0], &h->v[i]);
        h->quantidade--;
        
        peneirar(h, 0);
        
        imprime(h->v, h->tamanho);
    }
}

int main () {
    int n, i;
    scanf ("%d", &n);
    
    if (n <= 0) {
        return 0;
    }

    Heap *h = criaHeapVazio (n);
    if (h == NULL) {
        return 1;
    }

    for (i = 0; i < n; i++) {
        scanf ("%d", &h->v[i]);
    }
    
    h->quantidade = n;
    heapSort (h);
    liberaHeap (h);
    
    return 0;
}