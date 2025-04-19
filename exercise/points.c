#include <stdio.h>
#include <math.h>

double pointx[20];
double pointy[20];

double s(double xone, double yone, double xtwo, double ytwo, double xthree, double ythree) {
    if (xtwo == xthree) {
        return fabs((xone - xtwo) * (ythree - ytwo) / 2.0);
    }
    else {
        return fabs(((ythree - ytwo) / (xthree - xtwo) * (xone - xtwo) + ytwo - yone) * (xthree - xtwo) / 2.0);
    }
}

int main() {
    int n;
    double result = 0.0;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%lf%lf", &pointx[i], &pointy[i]);
    }
    for (int i = 2; i < n; i++) {
        result += s(pointx[0], pointy[0], pointx[i - 1], pointy[i - 1], pointx[i], pointy[i]);
    }
    printf("%.2f", result);
    return 0;
}