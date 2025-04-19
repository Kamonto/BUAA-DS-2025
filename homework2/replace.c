#include <stdio.h>
#include <string.h>
#include <ctype.h>

char txt[10000];
int txthead;
char before[10000];
char after[10000];

int equal(int i) {
    for (int j = 0; j < strlen(before); j++) {
        if (isupper(txt[i + j])) {
            if (txt[i + j] != toupper(before[j])) {
                return 0;
            }
        }
        else if (islower(txt[i + j])) {
            if (txt[i + j] != tolower(before[j])) {
                return 0;
            }
        }
        else {
            if (txt[i + j] != before[j]) {
                return 0;
            }
        }
    }
    return 1;
}

int main() {
    FILE *in, *out;
    // in = fopen("C:\\Users\\24502\\Desktop\\Projects\\DS2025\\homework2\\filein.txt", "r");
    // out = fopen("C:\\Users\\24502\\Desktop\\Projects\\DS2025\\homework2\\fileout.txt", "w");
    in = fopen("filein.txt", "r");
    out = fopen("fileout.txt", "w");
    if (in == NULL) {
        perror("error: ");
    }
    while (fscanf(in, "%c", &txt[txthead]) != EOF) {
        txthead++;
    }
    scanf("%s", before);
    scanf("%s", after);
    for (int i = 0; i < txthead; i++) {
        if (equal(i)) {
            fprintf(out, "%s", after);
            i = i + strlen(before) - 1;
        }
        else {
            fprintf(out, "%c", txt[i]);
        }
    }
    fclose(in);
    fclose(out);
    return 0;
}