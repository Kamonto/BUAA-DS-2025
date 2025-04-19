#include <stdio.h>
#include <string.h>

char code[100];
char table[100];
int tablehead;
int vis[100];

int main() {
    FILE *in, *out;
    // in = fopen("C:\\Users\\24502\\Desktop\\Projects\\DS2025\\homework2\\encrypt.txt", "r");
    // out = fopen("C:\\Users\\24502\\Desktop\\Projects\\DS2025\\homework2\\output.txt", "w");
    in = fopen("encrypt.txt", "r");
    out = fopen("output.txt", "w");
    scanf("%s", code);
    for (int i = 0; i < strlen(code); i++) {
        if (vis[code[i] - 'a'] == 0) {
            table[tablehead++] = code[i];
            vis[code[i] - 'a'] = 1;
        }
    }
    for (int i = 25; i >= 0; i--) {
        if (vis[i] == 0) {
            table[tablehead++] = i + 'a';
            vis[i] = 1;
        }
    }
    for (int i = 0; i < 26; i++) {
        printf("%c", table[i]);
    }
    char c;
    while (fscanf(in, "%c", &c) != EOF) {
        if (c >= 'a' && c <= 'z') {
            fprintf(out, "%c", table[c - 'a']);
        }
        else {
            fprintf(out, "%c", c);
        }
    }
    return 0;
}