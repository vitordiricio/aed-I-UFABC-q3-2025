#include <stdio.h>

void convertTime(int totalSeconds, int *hours, int *minutes, int *seconds) {
    *hours = totalSeconds / 3600;
    int remainder = totalSeconds % 3600;
    *minutes = remainder / 60;
    *seconds = remainder % 60;
}

int main() {
    int totalSeconds;
    int hours, minutes, seconds;

    scanf("%d", &totalSeconds);

    convertTime(totalSeconds, &hours, &minutes, &seconds);

    printf("%d:%d:%d\n", hours, minutes, seconds);

    return 0;
}