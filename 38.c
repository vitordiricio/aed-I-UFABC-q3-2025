#include <stdio.h>

typedef struct tData {
    int dia, mes, ano;
} Data;

int isBissexto(int ano) {
    if ((ano % 400 == 0) || (ano % 4 == 0 && ano % 100 != 0)) {
        return 1;
    }
    return 0;
}

int isValida(Data dt) {
    int maxDays;

    if (dt.mes < 1 || dt.mes > 12) {
        return 0;
    }

    if (dt.dia < 1) {
        return 0;
    }

    if (dt.mes == 2) {
        if (isBissexto(dt.ano) == 1) {
            maxDays = 29;
        } else {
            maxDays = 28;
        }
    } else if (dt.mes == 4 || dt.mes == 6 || dt.mes == 9 || dt.mes == 11) {
        maxDays = 30;
    } else {
        maxDays = 31;
    }

    if (dt.dia > maxDays) {
        return 0;
    }

    return 1;
}

int main() {
    int n;
    Data currentDate;

    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        scanf("%d %d %d", &currentDate.dia, &currentDate.mes, &currentDate.ano);

        if (isValida(currentDate) == 1) {
            printf("DATA VALIDA\n");
        } else {
            printf("DATA INVALIDA\n");
        }
    }

    return 0;
}