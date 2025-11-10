#include <stdio.h>
#include <stdlib.h>

typedef struct tPilha {
    int *itens;
    int topo;
    int tamanho;
} Pilha;

Pilha * createEmptyStack(int size) {
    Pilha *stack = (Pilha *) malloc(sizeof(Pilha));
    if (stack == NULL) {
        return NULL;
    }

    stack->itens = (int *) malloc(size * sizeof(int));
    if (stack->itens == NULL) {
        free(stack);
        return NULL;
    }

    stack->topo = 0;
    stack->tamanho = size;
    return stack;
}

void freeStack(Pilha *stack) {
    if (stack != NULL) {
        free(stack->itens);
        free(stack);
    }
}

int isEmpty(Pilha *stack) {
    if (stack == NULL) {
        return 1;
    }
    return (stack->topo == 0);
}

int isFull(Pilha *stack) {
    if (stack == NULL) {
        return 1;
    }
    return (stack->topo == stack->tamanho);
}

void push(Pilha *stack, int x) {
    if (stack == NULL || isFull(stack)) {
        return;
    }
    stack->itens[stack->topo] = x;
    stack->topo++;
}

void pop(Pilha *stack) {
    if (stack == NULL || isEmpty(stack)) {
        return;
    }
    stack->topo--;
}

void printTop(Pilha *stack) {
    if (stack == NULL || isEmpty(stack)) {
        return;
    }
    printf("%d\n", stack->itens[stack->topo - 1]);
}

void printStackTopToBottom(Pilha *stack) {
    if (stack == NULL || isEmpty(stack)) {
        return;
    }
    for (int i = stack->topo - 1; i >= 0; i--) {
        printf("%d", stack->itens[i]);
        if (i > 0) {
            printf(" ");
        }
    }
    printf("\n");
}

void printStackBottomToTop(Pilha *stack) {
    if (stack == NULL || isEmpty(stack)) {
        return;
    }
    for (int i = 0; i < stack->topo; i++) {
        printf("%d", stack->itens[i]);
        if (i < stack->topo - 1) {
            printf(" ");
        }
    }
    printf("\n");
}

int main() {
    char op;
    int n, x;
    scanf("%d", &n);

    Pilha *stack = createEmptyStack(n);
    if (stack == NULL) {
        return 1;
    }

    while (scanf(" %c", &op) != EOF) {
        switch (op) {
            case 'E':
                scanf("%d", &x);
                push(stack, x);
                break;
            case 'D':
                pop(stack);
                break;
            case 'T':
                printTop(stack);
                break;
            case 'X':
                printStackTopToBottom(stack);
                break;
            case 'B':
                printStackBottomToTop(stack);
                break;
        }
    }

    freeStack(stack);
    return 0;
}