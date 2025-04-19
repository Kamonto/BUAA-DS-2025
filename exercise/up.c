#include <stdio.h>
#include <string.h>

char s[10005];
int length[10005];

int main() {
    scanf("%s", s);
    for (int i = 0; i < strlen(s); i++) {
        int maxlen = 0;
        for (int j = 0; j < i; j++) {
            if (s[j] <= s[i] && length[j] > maxlen) {
                maxlen = length[j];
            }
        }
        length[i] = maxlen + 1;
    }
    printf("%d", length[strlen(s) - 1]);
    return 0;
}