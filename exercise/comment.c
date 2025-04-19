#include <stdio.h>
#include <math.h>

int main() {
    FILE *input;
    input = fopen("filein.c", "r");
    char c, lc = '\0';
    int allchar = 0, comchar = 0;
    int incom = 0;
    while (fscanf(input, "%c", &c) != EOF) {
        if (c == '*' && lc == '/') {
            allchar++;
            incom = 1;
        }
        else if (c == '/' && lc == '*') {
            allchar++;
            comchar--;
            incom = 0;
        }
        else {
            if (incom) {
                allchar++;
                comchar++;
            }
            else {
                allchar++;
            }
        }
        lc = c;
    }
    printf("%.0f%%", floor((double)comchar / (double)allchar * 100.0));
    fclose(input);
    return 0;
}