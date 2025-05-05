#include <stdio.h>
#include <string.h>

char stack[105][25];
int stackhead;

char base[105][25];
int allbase;
int allinvoke[105];
char invoke[105][15][25];

int main() {
    int op;
    do {
        scanf("%d", &op);
        if (op == 8) {
            char func[25];
            scanf("%s", func);
            if (stackhead != 0) {
                for (int i = 0; i < allbase; i++) {
                    if (!strcmp(stack[stackhead - 1], base[i])) {
                        int visflag = 0;
                        for (int j = 0; j < allinvoke[i]; j++) {
                            if (!strcmp(func, invoke[i][j])) {
                                visflag = 1;
                                break;
                            }
                        }
                        if (visflag == 0) {
                            strcpy(invoke[i][allinvoke[i]++], func);
                        }
                        break;
                    }
                }
            }

            strcpy(stack[stackhead++], func);

            int visflag = 0;
            for (int i = 0; i < allbase; i++) {
                if (!strcmp(func, base[i])) {
                    visflag = 1;
                    break;
                }
            }
            if (visflag == 0) {
                strcpy(base[allbase++], func);
            }
        }
        else if (op == 0){
            stackhead--;
        }
    } while (stackhead != 0);
    for (int i = 0; i < allbase; i++) {
        if (allinvoke[i] > 0) {
            printf("%s:", base[i]);
            printf("%s", invoke[i][0]);
            for (int j = 1; j < allinvoke[i]; j++) {
                printf(",%s", invoke[i][j]);
            }
            printf("\n");
        }
    }
    return 0;
}