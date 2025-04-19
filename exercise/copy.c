#include <stdio.h>

int isblankk(char c) {
    if (c == ' ' || c == '\t') {
        return 1;
    }
    return 0;
}

int main() {
    FILE *in, *out;
    char c, lc = '\0';

    in = fopen("fcopy.in", "r");
    out = fopen("fcopy.out", "w");

    while (fscanf(in, "%c", &c) != EOF) {
        if (isblankk(c) && isblankk(lc)) {
            // do nothing
        }
        else if (c == '\t') {
            fprintf(out, " ");
        }
        else {
            fprintf(out, "%c", c);
        }
        lc = c;
    }

    fclose(in);
    fclose(out);

    return 0;
}