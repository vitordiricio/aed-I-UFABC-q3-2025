#include <stdio.h>
#include <stdlib.h>

struct tRacional {
    int numerador;
    int denominador;
};

int findGCD(int a, int b) {
    a = abs(a);
    b = abs(b);
    int remainder;
    while (b != 0) {
        remainder = a % b;
        a = b;
        b = remainder;
    }
    return a;
}

struct tRacional racional(int num, int den) {
    struct tRacional r;
    r.numerador = num;
    r.denominador = den;
    return r;
}

struct tRacional reduz(struct tRacional r) {
    if (r.denominador == 0) {
        return r;
    }

    if (r.denominador < 0) {
        r.numerador = -r.numerador;
        r.denominador = -r.denominador;
    }

    int commonDivisor = findGCD(r.numerador, r.denominador);
    
    if (commonDivisor > 0) {
        r.numerador /= commonDivisor;
        r.denominador /= commonDivisor;
    }
    
    return r;
}

struct tRacional negativo(struct tRacional r) {
    struct tRacional result;
    result.numerador = -r.numerador;
    result.denominador = r.denominador;
    return result;
}

struct tRacional soma(struct tRacional r1, struct tRacional r2) {
    struct tRacional result;
    result.numerador = (r1.numerador * r2.denominador) + (r2.numerador * r1.denominador);
    result.denominador = r1.denominador * r2.denominador;
    return reduz(result);
}

struct tRacional multiplica(struct tRacional r1, struct tRacional r2) {
    struct tRacional result;
    result.numerador = r1.numerador * r2.numerador;
    result.denominador = r1.denominador * r2.denominador;
    return reduz(result);
}

struct tRacional divide(struct tRacional r1, struct tRacional r2) {
    struct tRacional result;
    result.numerador = r1.numerador * r2.denominador;
    result.denominador = r1.denominador * r2.numerador;
    return reduz(result);
}

int main() {
    int n1, d1, n2, d2;
    char op;
    struct tRacional r1, r2, result;

    while (scanf("%d %d %c %d %d", &n1, &d1, &op, &n2, &d2) == 5) {
        r1 = racional(n1, d1);
        r2 = racional(n2, d2);

        switch (op) {
            case '+':
                result = soma(r1, r2);
                break;
            case '-':
                result = soma(r1, negativo(r2));
                break;
            case '*':
                result = multiplica(r1, r2);
                break;
            case '/':
                result = divide(r1, r2);
                break;
        }

        printf("%d %d\n", result.numerador, result.denominador);
    }

    return 0;
}