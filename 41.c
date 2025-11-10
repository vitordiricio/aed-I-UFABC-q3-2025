#include <stdio.h>

struct tComplex {
    int real;
    int imaginary;
};

struct tComplex complexo(int a, int b) {
    struct tComplex c;
    c.real = a;
    c.imaginary = b;
    return c;
}

struct tComplex soma(struct tComplex z1, struct tComplex z2) {
    struct tComplex result;
    result.real = z1.real + z2.real;
    result.imaginary = z1.imaginary + z2.imaginary;
    return result;
}

struct tComplex subtrai(struct tComplex z1, struct tComplex z2) {
    struct tComplex result;
    result.real = z1.real - z2.real;
    result.imaginary = z1.imaginary - z2.imaginary;
    return result;
}

struct tComplex multiplica(struct tComplex z1, struct tComplex z2) {
    struct tComplex result;
    int a = z1.real;
    int b = z1.imaginary;
    int c = z2.real;
    int d = z2.imaginary;

    result.real = (a * c) - (b * d);
    result.imaginary = (a * d) + (b * c);
    return result;
}

struct tComplex divide(struct tComplex z1, struct tComplex z2) {
    struct tComplex result;
    int a = z1.real;
    int b = z1.imaginary;
    int c = z2.real;
    int d = z2.imaginary;

    int denominator = (c * c) + (d * d);

    if (denominator != 0) {
        result.real = ((a * c) + (b * d)) / denominator;
        result.imaginary = ((b * c) - (a * d)) / denominator;
    } else {
        result.real = 0;
        result.imaginary = 0;
    }

    return result;
}

void printComplex(struct tComplex z) {
    printf("%d %di\n", z.real, z.imaginary);
}

int main() {
    int a, b, c, d;
    char op, i_char1, i_char2;

    while (scanf("%d %d%c %c %d %d%c", &a, &b, &i_char1, &op, &c, &d, &i_char2) == 7) {
        struct tComplex z1 = complexo(a, b);
        struct tComplex z2 = complexo(c, d);
        struct tComplex result;

        switch (op) {
            case '+':
                result = soma(z1, z2);
                break;
            case '-':
                result = subtrai(z1, z2);
                break;
            case '*':
                result = multiplica(z1, z2);
                break;
            case '/':
                result = divide(z1, z2);
                break;
        }

        printComplex(result);
    }

    return 0;
}