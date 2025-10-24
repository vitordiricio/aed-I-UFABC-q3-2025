#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME 100
#define MAX_ATHLETES 5000
#define NO_TIME 999999999

typedef struct {
    char name[MAX_NAME];
    long totalTime;
    int originalIndex;
} Athlete;

long calculateTimeInCentiseconds(int min, int seg, int cent) {
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
    int fastestIndexInHeat = heatSize - 1;
    int currentRank = 0;
    int rightOffset = 1;
    int leftOffset = -1;

    printf("Raia %d: %s\n", centerLane, heatAthletes[fastestIndexInHeat - currentRank].name);
    currentRank++;

    while (currentRank < heatSize) {
        int rightLane = centerLane + rightOffset;
        if (rightLane <= numLanes) {
            printf("Raia %d: %s\n", rightLane, heatAthletes[fastestIndexInHeat - currentRank].name);
            currentRank++;
        }
        rightOffset++;

        if (currentRank >= heatSize) {
            break;
        }

        int leftLane = centerLane + leftOffset;
        if (leftLane >= 1) {
            printf("Raia %d: %s\n", leftLane, heatAthletes[fastestIndexInHeat - currentRank].name);
            currentRank++;
        }
        leftOffset--;
    }
}

int main() {
    int numLanes, numAthletes;
    scanf("%d", &numLanes);
    scanf("%d", &numAthletes);

    Athlete athletes[MAX_ATHLETES];
    for (int i = 0; i < numAthletes; i++) {
        int min, seg, cent;
        scanf("%s %d %d %d", athletes[i].name, &min, &seg, &cent);
        athletes[i].totalTime = calculateTimeInCentiseconds(min, seg, cent);
        athletes[i].originalIndex = i;
    }

    qsort(athletes, numAthletes, sizeof(Athlete), compareAthletes);

    int numSeries = (numAthletes + numLanes - 1) / numLanes;
    int *seriesSizes = (int *) malloc(numSeries * sizeof(int));
    if (seriesSizes == NULL) {
        return 1;
    }

    int athletesInSlowestHeat = numAthletes % numLanes;
    if (athletesInSlowestHeat == 0 && numAthletes > 0) {
        athletesInSlowestHeat = numLanes;
    }

    seriesSizes[0] = athletesInSlowestHeat;
    for (int i = 1; i < numSeries; i++) {
        seriesSizes[i] = numLanes;
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
        Athlete heatAthletes[currentHeatSize];

        for (int i = 0; i < currentHeatSize; i++) {
            heatAthletes[i] = athletes[athleteIndex];
            athleteIndex--;
        }

        assignAndPrintLanes(heatAthletes, currentHeatSize, numLanes);
    }

    free(seriesSizes);

    return 0;
}