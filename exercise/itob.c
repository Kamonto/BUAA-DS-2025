#include <stdio.h>

char s[1000];

void itob(int num, int base) {
    int absnum = (num < 0) ? (-num) : num;
    char inverts[1000];
    int head = 0;
    while (absnum) {
        int mod = absnum % base;
        inverts[head++] = (mod < 10) ? (mod + '0') : (mod + 'a' - 10);
        absnum /= base;
    }
    if (num < 0) {
        inverts[head++] = '-';
    }
    for (int i = 0; i < head; i++) {
        s[head - i - 1] = inverts[i];
    }
}

int main() {
    int num, base;
    scanf("%d%d", &num, &base);
    itob(num, base);
    printf("%s", s);
    return 0;
}