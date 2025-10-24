#include <stdio.h>
#include <math.h>

double calculateDelta(double a, double b, double c) {
    return (b * b) - (4 * a * c);
}

void findQuadraticRoots(double a, double b, double discriminant, double *root1, double *root2) {
    double sqrtDiscriminant = sqrt(discriminant);
    *root1 = (-b + sqrtDiscriminant) / (2 * a);
    *root2 = (-b - sqrtDiscriminant) / (2 * a);
}

int main() {
    double a, b, c;
    double discriminant;
    double root1, root2;

    scanf("%lf %lf %lf", &a, &b, &c);

    discriminant = calculateDelta(a, b, c);

    findQuadraticRoots(a, b, discriminant, &root1, &root2);

    printf("%.4f %.4f\n", root1, root2);

    return 0;
}