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

int vazio(Heap *h) {
    if (h == NULL) {
        return 1;
    }
    return h->quantidade == 0;
}

int cheio(Heap *h) {
    if (h == NULL) {
        return 1;
    }
    return h->quantidade == h->tamanho;
}

void sobeChave(Heap *h, int i) {
    while (i > 0 && h->v[pai(i)] > h->v[i]) {
        troca(&h->v[pai(i)], &h->v[i]);
        i = pai(i);
    }
}

void inserir(Heap *h, int x) {
    if (h == NULL || cheio(h)) {
        return;
    }
    
    h->v[h->quantidade] = x;
    h->quantidade++;
    
    sobeChave(h, h->quantidade - 1);
}

int extraiMinimo(Heap *h) {
    if (h == NULL || vazio(h)) {
        return -1;
    }

    int minimo = h->v[0];
    
    troca(&h->v[0], &h->v[h->quantidade - 1]);
    h->quantidade--;
    
    desceChave(h, 0);
    
    return minimo;
}

void remover(Heap *h, int x) {
    if (h == NULL || vazio(h)) {
        return;
    }

    int i = -1;
    for (int j = 0; j < h->quantidade; j++) {
        if (h->v[j] == x) {
            i = j;
            break;
        }
    }

    if (i == -1) {
        return;
    }

    troca(&h->v[i], &h->v[h->quantidade - 1]);
    h->quantidade--;

    if (i < h->quantidade) {
        if (i > 0 && h->v[i] < h->v[pai(i)]) {
            sobeChave(h, i);
        } else {
            desceChave(h, i);
        }
    }
}

int main () {
    int tam;
    scanf ("%d", &tam);
    Heap *h = criaHeapVazio (tam);
    if (h == NULL) {
        return 1;
    }

    char op;
    int x;
    while (scanf (" %c", &op) != EOF) {
        switch (op) {
            case 'I': scanf ("%d", &x); 
                      inserir (h, x);
                      break;
            case 'R': scanf ("%d", &x); 
                      remover (h, x);
                      break;
            case 'E': if (!vazio (h)) {
                          x = extraiMinimo (h);
                          printf ("[%d]\n", x);
                      }
                      break;
            case 'P': if (!vazio (h)) {
                          imprime (h->v, h->quantidade);
                      }
                      break;
        }
    }
    liberaHeap (h);
    return 0;
}