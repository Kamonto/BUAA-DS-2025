#include <stdio.h>

struct Bracket {
    char c;
    int line;
};

struct Bracket brackets[205];
int allbrackets;
struct Bracket stack[205];
int stackhead;

int nowline = 1;

int ignore = 0;
// ignore: 0: not ignore; 1: " "; 2: ' '; 3: // ; 4: /* */

int main() {
    FILE *file;
    file = fopen("C:\\Users\\24502\\Desktop\\Projects\\DS2025\\homework4\\example.txt", "r");
    // file = fopen("example.c", "r");
    char c, lastc = '\0';
    while (fscanf(file, "%c", &c) != EOF) {
        if (c == '"') {
            ignore = (ignore == 0) ? 1 : (ignore == 1) ? 0 : ignore;
        }
        else if (c == '\'') {
            ignore = (ignore == 0) ? 2 : (ignore == 2) ? 0 : ignore;
        }
        else if (c == '/' && lastc == '/') {
            ignore = (ignore == 0) ? 3 : ignore;
        }
        else if (c == '\n') {
            ignore = (ignore == 3) ? 0 : ignore;
            nowline++;
        }
        else if (c == '*' && lastc == '/') {
            ignore = (ignore == 0) ? 4 : ignore;
        }
        else if (c == '/' && lastc == '*') {
            ignore = (ignore == 4) ? 0 : ignore;
        }
        else if (c == '(') {
            if (ignore == 0) {
                struct Bracket bracket = {'(', nowline};
                brackets[allbrackets++] = bracket;
                stack[stackhead++] = bracket;
            }
        }
        else if (c == '{') {
            if (ignore == 0) {
                if (stack[stackhead - 1].c == '(') {
                    printf("without maching '(' at line %d", stack[stackhead - 1].line);
                    return 0;
                }
                else {
                    struct Bracket bracket = {'{', nowline};
                    brackets[allbrackets++] = bracket;
                    stack[stackhead++] = bracket;
                }
            }
        }
        else if (c == ')') {
            if (ignore == 0) {
                if (stack[stackhead - 1].c != '(') {
                    printf("without maching ')' at line %d", nowline);
                    return 0;
                }
                else {
                    struct Bracket bracket = {')', nowline};
                    brackets[allbrackets++] = bracket;
                    stackhead--;
                }
            }
        }
        else if (c == '}') {
            if (ignore == 0) {
                if (stack[stackhead - 1].c != '{') {
                    printf("without maching '}' at line %d", nowline);
                    return 0;
                }
                else {
                    struct Bracket bracket = {'}', nowline};
                    brackets[allbrackets++] = bracket;
                    stackhead--;
                }
            }
        }
        lastc = c;
    }
    if (stackhead > 0) {
        printf("without maching '%c' at line %d", stack[stackhead - 1].c, stack[stackhead - 1].line);
    }
    else {
        for (int i = 0; i < allbrackets; i++) {
            printf("%c", brackets[i].c);
        }
    }
    return 0;
}