#include <stdio.h>

int calculateAge(int currentYear, int birthYear) {
    return currentYear - birthYear;
}

int main() {
    int currentYear;
    char name[50];
    int birthYear;
    int age;

    scanf("%d %s %d", &currentYear, name, &birthYear);

    age = calculateAge(currentYear, birthYear);

    printf("%s, voce completa %d anos de idade neste ano.\n", name, age);

    return 0;
}