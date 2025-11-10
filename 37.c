#include <stdio.h>

int isLeapYear(int year) {
    if ((year % 400 == 0) || (year % 4 == 0 && year % 100 != 0)) {
        return 1;
    }
    return 0;
}

int main() {
    int year;

    scanf("%d", &year);

    if (isLeapYear(year)) {
        printf("ANO BISSEXTO\n");
    } else {
        printf("ANO NAO BISSEXTO\n");
    }

    return 0;
}