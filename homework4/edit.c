#include <stdio.h>
#include <string.h>

struct Command {
    int op;
    int pos;
    char s[520];
};

struct Command history[1000];
int historyhead;
char str[520];

void strinsert(int pos, char *s) {
    // printf("insert: %d %s\n", pos, s);
    char tempstr[520] = {'\0'};
    strncpy(tempstr, str, pos);
    strcpy(tempstr + pos, s);
    strcpy(tempstr + pos + strlen(s), str + pos);
    strcpy(str, tempstr);
}

void strdelete(int pos, char *s) {
    // printf("delete: %d %s\n", pos, s);
    char tempstr[520] = {'\0'};
    strncpy(tempstr, str, pos);
    strcpy(tempstr + pos, str + pos + strlen(s));
    strcpy(str, tempstr);
}

int main() {
    gets(str);
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        struct Command command = {0, 0, {'\0'}};
        scanf("%d%d%s", &command.op, &command.pos, &command.s);
        history[historyhead++] = command;
    }

    int op;
    scanf("%d", &op);
    while (op != -1) {
        if (op == 1) {
            struct Command command = {0, 0, {'\0'}};
            command.op = 1;
            scanf("%d%s", &command.pos, &command.s);
            strinsert(command.pos, command.s);
            history[historyhead++] = command;
        }
        else if (op == 2) {
            struct Command command = {0, 0, {'\0'}};
            command.op = 2;
            int deletelen;
            scanf("%d%d", &command.pos, &deletelen);
            strncpy(command.s, str + command.pos, deletelen);
            strdelete(command.pos, command.s);
            history[historyhead++] = command;
        }
        else if (op == 3) {
            if (historyhead > 0) {
                struct Command command = history[--historyhead];
                if (command.op == 1) {
                    strdelete(command.pos, command.s);
                }
                else if (command.op == 2) {
                    strinsert(command.pos, command.s);
                }
            }
        }
        // puts(str);
        scanf("%d", &op);
    }
    printf("%s", str);
    return 0;
}