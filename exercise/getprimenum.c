#include <stdio.h>

int invert(int x) {
    int y = 0;
    while (x) {
        y = y * 10 + x % 10;
        x /= 10;
    }
    return y;
}

int isprime(int x) {
    if (x == 1) {
        return 0;
    }
    else if (x == 2) {
        return 1;
    }
    else if (x % 2 == 0) {
        return 0;
    }
    else {
        for (int i = 3; i * i < x; i += 2) {
            if (x % i == 0) {
                return 0;
            }
        }
        return 1;
    }
}

int main() {
    int num;
    scanf("%d", &num);
    if (isprime(num) && isprime(invert(num))) {
        printf("yes");
    }
    else {
        printf("no");
    }
    return 0;
}