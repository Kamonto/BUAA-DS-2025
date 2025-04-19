#include <stdio.h>
#include <string.h>

char s[1000];

int main() {
    int offset = 0;
    scanf("%s", s);
    if (s[0] == '0') {
        int head = 0;
        for (head = 0; head < strlen(s); head++) {
            if (s[head] == '0') {
                offset++;
            }
            else if (s[head] == '.') {
                // do nothing
            }
            else {
                printf("%c", s[head]);
                break;
            }
        }
        if (head != strlen(s) - 1) {
            printf(".");
            for (int i = head + 1; i < strlen(s); i++) {
                printf("%c", s[i]);
            }
        }
        printf("e-%d", offset);
    }
    else {
        for (int i = 0; i < strlen(s); i++) {
            if (s[i] == '.') {
                offset = i - 1;
            }
            else {
                if (i == 0) {
                    printf("%c.", s[i]);
                }
                else {
                    printf("%c", s[i]);
                }
            }
        }
        printf("e%d", offset);
    }
    return 0;
}