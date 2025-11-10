#include <stdio.h>

typedef struct {
    int day;
    int month;
    int year;
} Date;

int isLeapYear(int year) {
    if ((year % 400 == 0) || (year % 4 == 0 && year % 100 != 0)) {
        return 1;
    }
    return 0;
}

int getMaxDaysInMonth(int month, int year) {
    int maxDays;
    if (month == 2) {
        if (isLeapYear(year) == 1) {
            maxDays = 29;
        } else {
            maxDays = 28;
        }
    } else if (month == 4 || month == 6 || month == 9 || month == 11) {
        maxDays = 30;
    } else {
        maxDays = 31;
    }
    return maxDays;
}

Date calculatePreviousDay(Date currentDate) {
    Date previousDate = currentDate;

    if (previousDate.day > 1) {
        previousDate.day--;
    } else {
        if (previousDate.month > 1) {
            previousDate.month--;
        } else {
            previousDate.month = 12;
            previousDate.year--;
        }
        previousDate.day = getMaxDaysInMonth(previousDate.month, previousDate.year);
    }
    return previousDate;
}

int main() {
    Date currentDate;
    Date previousDate;

    scanf("%d %d %d", &currentDate.day, &currentDate.month, &currentDate.year);

    previousDate = calculatePreviousDay(currentDate);

    printf("%d %d %d\n", previousDate.day, previousDate.month, previousDate.year);

    return 0;
}