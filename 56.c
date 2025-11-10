#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define MAX_NAME_LEN 100
#define NO_TIME LONG_MAX

typedef struct {
    char name[MAX_NAME_LEN];
    long totalTime;
    int originalIndex;
} Athlete;

long calculateTime(int min, int seg, int cent) {
    if (min == 0 && seg == 0 && cent == 0) {
        return NO_TIME;
    }
    return (long)min * 60 * 100 + (long)seg * 100 + (long)cent;
}

int compareAthletes(const void *a, const void *b) {
    Athlete *athleteA = (Athlete *)a;
    Athlete *athleteB = (Athlete *)b;

    if (athleteA->totalTime < athleteB->totalTime) {
        return -1;
    } else if (athleteA->totalTime > athleteB->totalTime) {
        return 1;
    } else {
        return athleteA->originalIndex - athleteB->originalIndex;
    }
}

void assignAndPrintLanes(Athlete heatAthletes[], int heatSize, int numLanes) {
    int centerLane = (numLanes + 1) / 2;
    int athleteIndexInHeat = heatSize - 1;
    int currentRank = 0;
    int rightOffset = 1;
    int leftOffset = -1;

    if (currentRank < heatSize) {
        printf("Raia %d: %s\n", centerLane, heatAthletes[athleteIndexInHeat - currentRank].name);
        currentRank++;
    }

    while (currentRank < heatSize) {
        int rightLane = centerLane + rightOffset;
        if (rightLane <= numLanes && currentRank < heatSize) {
            printf("Raia %d: %s\n", rightLane, heatAthletes[athleteIndexInHeat - currentRank].name);
            currentRank++;
        }
        rightOffset++;

        int leftLane = centerLane + leftOffset;
        if (leftLane >= 1 && currentRank < heatSize) {
            printf("Raia %d: %s\n", leftLane, heatAthletes[athleteIndexInHeat - currentRank].name);
            currentRank++;
        }
        leftOffset--;
    }
}

int main() {
    int numLanes, numAthletes;
    scanf("%d", &numLanes);
    scanf("%d", &numAthletes);

    Athlete *allAthletes = (Athlete *) malloc(numAthletes * sizeof(Athlete));
    if (allAthletes == NULL) {
        return 1;
    }

    for (int i = 0; i < numAthletes; i++) {
        int min, seg, cent;
        scanf("%s %d %d %d", allAthletes[i].name, &min, &seg, &cent);
        allAthletes[i].totalTime = calculateTime(min, seg, cent);
        allAthletes[i].originalIndex = i;
    }

    qsort(allAthletes, numAthletes, sizeof(Athlete), compareAthletes);

    int numSeries = (numAthletes + numLanes - 1) / numLanes;
    int *seriesSizes = (int *) malloc(numSeries * sizeof(int));
    if (seriesSizes == NULL) {
        free(allAthletes);
        return 1;
    }

    int athletesInFirstSeries = numAthletes % numLanes;
    if (athletesInFirstSeries == 0 && numAthletes > 0) {
        athletesInFirstSeries = numLanes;
    }

    for (int i = 0; i < numSeries; i++) {
        seriesSizes[i] = numLanes;
    }
    
    if (athletesInFirstSeries > 0) {
        seriesSizes[0] = athletesInFirstSeries;
    }

    if (numSeries > 1 && seriesSizes[0] < 3) {
        int numToMove = 3 - seriesSizes[0];
        seriesSizes[0] = 3;
        seriesSizes[1] -= numToMove;
    }

    printf("%d %s\n", numSeries, (numSeries > 1) ? "series" : "serie");

    int athleteIndex = numAthletes - 1;
    for (int s = 0; s < numSeries; s++) {
        printf("%da. serie:\n", s + 1);

        int currentHeatSize = seriesSizes[s];
        Athlete *heatAthletes = (Athlete *) malloc(currentHeatSize * sizeof(Athlete));
        
        if (heatAthletes == NULL) {
            free(allAthletes);
            free(seriesSizes);
            return 1;
        }

        for (int i = 0; i < currentHeatSize; i++) {
            if(athleteIndex >= 0) {
                 heatAthletes[i] = allAthletes[athleteIndex];
                 athleteIndex--;
            }
        }

        assignAndPrintLanes(heatAthletes, currentHeatSize, numLanes);
        free(heatAthletes);
    }

    free(allAthletes);
    free(seriesSizes);

    return 0;
}