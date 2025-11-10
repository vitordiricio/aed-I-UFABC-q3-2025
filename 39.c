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

Date calculateNextDay(Date currentDate) {
    Date nextDate = currentDate;
    int maxDays = getMaxDaysInMonth(currentDate.month, currentDate.year);

    if (nextDate.day < maxDays) {
        nextDate.day++;
    } else {
        nextDate.day = 1;
        if (nextDate.month < 12) {
            nextDate.month++;
        } else {
            nextDate.month = 1;
            nextDate.year++;
        }
    }
    return nextDate;
}

int main() {
    Date currentDate;
    Date nextDate;

    scanf("%d %d %d", &currentDate.day, &currentDate.month, &currentDate.year);

    nextDate = calculateNextDay(currentDate);

    printf("%d %d %d\n", nextDate.day, nextDate.month, nextDate.year);

    return 0;
}