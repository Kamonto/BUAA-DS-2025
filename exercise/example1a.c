#include <stdio.h>

double pi[1000];
double term[1000];

int main() {
    double delta;
    int n = 1;
    scanf("%lf", &delta);
    pi[1] = 2.0;
    term[1] = 2.0;
    do {
        n++;
        term[n] = term[n - 1] * ((double)n - 1.0) / (2.0 * (double)n - 1.0);
        pi[n] = pi[n - 1] + term[n];
    } while (term[n] >= delta);
    printf("%d %.7f", n, pi[n]);
    return 0;
}