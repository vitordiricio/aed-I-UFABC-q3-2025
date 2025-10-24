#include <stdio.h>

void findMinNaturalNumber() {
    int number;
    int minNumber;
    int numbersEntered = 0;

    while (scanf("%d", &number) == 1) {
        if (number < 0) {
            break;
        }

        if (numbersEntered == 0) {
            minNumber = number;
        } else if (number < minNumber) {
            minNumber = number;
        }
        numbersEntered++;
    }

    if (numbersEntered > 0) {
        printf("%d\n", minNumber);
    } else {
        printf("nenhum numero informado\n");
    }
}

int main() {
    findMinNaturalNumber();
    return 0;
}