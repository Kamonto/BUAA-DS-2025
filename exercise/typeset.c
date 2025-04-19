#include <stdio.h>
#include <string.h>

char s[100][1000];
int alllines;

int isblankk(char c) {
    if (c == ' ' || c == '\t') {
        return 1;
    }
    return 0;
}

int main() {
    int pos;
    scanf("%d", &pos);
    while (fgets(s[alllines], 1000, stdin) != NULL) {
        if (isblankk(s[alllines][0])) {
            s[alllines][0] = ' ';
        }
        for (int i = 1; i < strlen(s[alllines]); i++) {
            if (isblankk(s[alllines][i])) {
                s[alllines][i] = ' ';
            }
            if (isblankk(s[alllines][i]) && isblankk(s[alllines][i - 1])) {
                for (int j = i + 1; j < strlen(s[alllines]); j++) {
                    s[alllines][j - 1] = s[alllines][j];
                }
                s[alllines][strlen(s[alllines]) - 1] = '\0';
                i--;
            }
            else if (s[alllines][i] == ':' && !isblankk(s[alllines][i - 1])) {
                for (int j = strlen(s[alllines]) - 1; j >= i; j--) {
                    s[alllines][j + 1] = s[alllines][j];
                }
                s[alllines][i] = ' ';
                i++;
            }
            else if (!isblankk(s[alllines][i]) && s[alllines][i - 1] == ':') {
                for (int j = strlen(s[alllines]) - 1; j >= i; j--) {
                    s[alllines][j + 1] = s[alllines][j];
                }
                s[alllines][i] = ' ';
                i++;
            }
        }
        for (int i = 1; i < strlen(s[alllines]); i++) {
            if (s[alllines][i] == ':') {
                int offset = pos - i - 1;
                for (int j = strlen(s[alllines]) - 1; j >= 0; j--) {
                    s[alllines][j + offset] = s[alllines][j];
                }
                for (int j = 0; j < offset; j++) {
                    s[alllines][j] = ' ';
                }
                break;
            }
        }
        for (int i = strlen(s[alllines]) - 1; i >= 0; i++) {
            if (isblankk(s[alllines][i])) {
                s[alllines][i] = '\0';
            }
            else {
                break;
            }
        }
        alllines++;
    }
    for (int i = 0; i < alllines; i++) {
        if (strcmp(s[i], "\n")){
            printf("%s", s[i]);
        }
    }
    return 0;
}