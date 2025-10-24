#include <stdio.h>

double calculateIMC(double mass, double height) {
    return mass / (height * height);
}

void printClassification(double imc) {
    if (imc < 16.0) {
        printf("Magreza grave\n");
    } else if (imc < 17.0) {
        printf("Magreza moderada\n");
    } else if (imc < 18.5) {
        printf("Magreza leve\n");
    } else if (imc < 25.0) {
        printf("Saudavel\n");
    } else if (imc < 30.0) {
        printf("Sobrepeso\n");
    } else if (imc < 35.0) {
        printf("Obesidade Grau I\n");
    } else if (imc < 40.0) {
        printf("Obesidade Grau II (severa)\n");
    } else {
        printf("Obesidade Grau III (morbida)\n");
    }
}

int main() {
    double height;
    double mass;
    double imc;

    scanf("%lf %lf", &height, &mass);

    imc = calculateIMC(mass, height);

    printClassification(imc);

    return 0;
}