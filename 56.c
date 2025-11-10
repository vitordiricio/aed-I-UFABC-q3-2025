#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define TAM_MAX_NOME 100
#define SEM_TEMPO LONG_MAX

typedef struct {
    char nome[TAM_MAX_NOME];
    long tempoTotal;
    int indiceOriginal;
} Atleta;

long calcularTempo(int min, int seg, int cent) {
    if (min == 0 && seg == 0 && cent == 0) {
        return SEM_TEMPO;
    }
    return (long)min * 60 * 100 + (long)seg * 100 + (long)cent;
}

int compararAtletas(const void *a, const void *b) {
    Atleta *atA = (Atleta *)a;
    Atleta *atB = (Atleta *)b;

    if (atA->tempoTotal < atB->tempoTotal) return -1;
    if (atA->tempoTotal > atB->tempoTotal) return 1;

    return atA->indiceOriginal - atB->indiceOriginal;
}

void distribuirEImprimirRaias(Atleta serieAtletas[], int tamSerie, int numRaias) {
    int raiaCentral = (numRaias + 1) / 2;
    int idxAtleta = tamSerie - 1;
    int colocado = 0;
    int deslocDir = 1;
    int deslocEsq = -1;

    if (colocado < tamSerie) {
        printf("Raia %d: %s\n", raiaCentral, serieAtletas[idxAtleta - colocado].nome);
        colocado++;
    }

    while (colocado < tamSerie) {
        int raiaDir = raiaCentral + deslocDir;
        if (raiaDir <= numRaias && colocado < tamSerie) {
            printf("Raia %d: %s\n", raiaDir, serieAtletas[idxAtleta - colocado].nome);
            colocado++;
        }
        deslocDir++;

        int raiaEsq = raiaCentral + deslocEsq;
        if (raiaEsq >= 1 && colocado < tamSerie) {
            printf("Raia %d: %s\n", raiaEsq, serieAtletas[idxAtleta - colocado].nome);
            colocado++;
        }
        deslocEsq--;
    }
}

int main() {
    int numRaias, numAtletas;
    scanf("%d", &numRaias);
    scanf("%d", &numAtletas);

    Atleta *todos = (Atleta *) malloc(numAtletas * sizeof(Atleta));
    if (todos == NULL) return 1;

    for (int i = 0; i < numAtletas; i++) {
        int min, seg, cent;
        scanf("%s %d %d %d", todos[i].nome, &min, &seg, &cent);
        todos[i].tempoTotal = calcularTempo(min, seg, cent);
        todos[i].indiceOriginal = i;
    }

    qsort(todos, numAtletas, sizeof(Atleta), compararAtletas);

    int numSeries = (numAtletas + numRaias - 1) / numRaias;
    int *tamanhos = (int *) malloc(numSeries * sizeof(int));
    if (tamanhos == NULL) {
        free(todos);
        return 1;
    }

    int atletasPrimeira = numAtletas % numRaias;
    if (atletasPrimeira == 0 && numAtletas > 0) {
        atletasPrimeira = numRaias;
    }

    for (int i = 0; i < numSeries; i++) {
        tamanhos[i] = numRaias;
    }

    tamanhos[0] = atletasPrimeira;

    if (numSeries > 1 && tamanhos[0] < 3) {
        int mover = 3 - tamanhos[0];
        tamanhos[0] = 3;
        tamanhos[1] -= mover;
    }

    printf("%d %s\n", numSeries, (numSeries > 1) ? "series" : "serie");

    int idx = numAtletas - 1;

    for (int s = 0; s < numSeries; s++) {
        printf("%da. serie:\n", s + 1);

        int tamAtual = tamanhos[s];
        Atleta *atletasSerie = (Atleta *) malloc(tamAtual * sizeof(Atleta));
        if (atletasSerie == NULL) {
            free(todos);
            free(tamanhos);
            return 1;
        }

        for (int i = 0; i < tamAtual; i++) {
            if (idx >= 0) {
                atletasSerie[i] = todos[idx];
                idx--;
            }
        }

        distribuirEImprimirRaias(atletasSerie, tamAtual, numRaias);
        free(atletasSerie);
    }

    free(todos);
    free(tamanhos);

    return 0;
}
