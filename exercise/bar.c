#include <stdio.h>

int times[30];
int maxtime;

int main() {
    char c;
    while (scanf("%c", &c) != EOF) {
        if (c >= 'a' && c <= 'z') {
            times[c - 'a']++;
            if (times[c - 'a'] > maxtime) {
                maxtime = times[c - 'a'];
            }
        }
    }
    for (int i = maxtime; i > 0; i--) {
        for (int j = 0; j < 26; j++) {
            if (times[j] >= i) {
                printf("*");
            }
            else {
                printf(" ");
            }
        }
        printf("\n");
    }
    printf("abcdefghijklmnopqrstuvwxyz");
    return 0;
}