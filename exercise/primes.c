#include <stdio.h>

int primes[100000];

void create() {
    for (int i = 1; i < 100000; i++) {
        primes[i] = 1;
    }
    for (int i = 2; i * 2 < 100000; i++) {
        for (int j = 2; i * j < 100000; j++) {
            primes[i * j] = 0;
        }
    }
}

int main() {
    create();
    int num;
    scanf("%d", &num);
    while (1) {
        int i = 2;
        while (1) {
            if (num < 100000 && primes[num]) {
                printf("%d", num);
                return 0;
            }
            else if (primes[i] && (num % i == 0)) {
                printf("%d ", i);
                num /= i;
                break;
            }
            i++;
        }
    }
    return 0;
}