#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BIGNUM_LEN 202

struct tInteiro {
    char digits[MAX_BIGNUM_LEN];
    int length;
};

void reverseString(char *str) {
    int len = strlen(str);
    for (int i = 0; i < len / 2; i++) {
        char temp = str[i];
        str[i] = str[len - 1 - i];
        str[len - 1 - i] = temp;
    }
}

struct tInteiro inteiro(char *s) {
    struct tInteiro bignum;
    strcpy(bignum.digits, s);
    reverseString(bignum.digits);
    bignum.length = strlen(bignum.digits);
    return bignum;
}

struct tInteiro soma(struct tInteiro a, struct tInteiro b) {
    struct tInteiro result;
    int carry = 0;
    int i = 0;
    int lenA = a.length;
    int lenB = b.length;
    int maxLen = (lenA > lenB) ? lenA : lenB;

    for (i = 0; i < maxLen; i++) {
        int digitA = (i < lenA) ? (a.digits[i] - '0') : 0;
        int digitB = (i < lenB) ? (b.digits[i] - '0') : 0;

        int sum = digitA + digitB + carry;
        result.digits[i] = (sum % 10) + '0';
        carry = sum / 10;
    }

    if (carry > 0) {
        result.digits[i] = carry + '0';
        i++;
    }

    result.digits[i] = '\0';
    result.length = i;
    return result;
}

struct tInteiro subtrai(struct tInteiro a, struct tInteiro b) {
    struct tInteiro result;
    int borrow = 0;
    int i = 0;
    int lenA = a.length;
    int lenB = b.length;

    for (i = 0; i < lenA; i++) {
        int digitA = (i < lenA) ? (a.digits[i] - '0') : 0;
        int digitB = (i < lenB) ? (b.digits[i] - '0') : 0;

        int diff = digitA - digitB - borrow;

        if (diff < 0) {
            diff += 10;
            borrow = 1;
        } else {
            borrow = 0;
        }
        result.digits[i] = diff + '0';
    }

    int len = i;
    while (len > 1 && result.digits[len - 1] == '0') {
        len--;
    }

    result.digits[len] = '\0';
    result.length = len;
    return result;
}

struct tInteiro multiplica(struct tInteiro a, struct tInteiro b) {
    struct tInteiro result;

    if ((a.length == 1 && a.digits[0] == '0') || (b.length == 1 && b.digits[0] == '0')) {
        return inteiro("0");
    }

    int lenA = a.length;
    int lenB = b.length;
    int maxResLen = lenA + lenB;
    int *intResult = (int *) calloc(maxResLen, sizeof(int));
    
    if (intResult == NULL) {
         return inteiro("0");
    }

    for (int i = 0; i < lenA; i++) {
        for (int j = 0; j < lenB; j++) {
            int digitA = a.digits[i] - '0';
            int digitB = b.digits[j] - '0';
            intResult[i + j] += digitA * digitB;
        }
    }

    int carry = 0;
    int k;
    for (k = 0; k < maxResLen; k++) {
        int sum = intResult[k] + carry;
        result.digits[k] = (sum % 10) + '0';
        carry = sum / 10;
    }

    int len = maxResLen;
    while (len > 1 && result.digits[len - 1] == '0') {
        len--;
    }

    result.digits[len] = '\0';
    result.length = len;

    free(intResult);
    return result;
}

int main() {
    char s1[102], s2[102];
    char op;

    while (scanf("%s %c %s", s1, &op, s2) == 3) {
        struct tInteiro a = inteiro(s1);
        struct tInteiro b = inteiro(s2);
        struct tInteiro result;

        if (op == '+') {
            result = soma(a, b);
        } else if (op == '-') {
            result = subtrai(a, b);
        } else if (op == '*') {
            result = multiplica(a, b);
        }

        for (int i = result.length - 1; i >= 0; i--) {
            printf("%c", result.digits[i]);
        }
        printf("\n");
    }

    return 0;
}