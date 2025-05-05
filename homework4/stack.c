#include <stdio.h>

int stack[105];
int stacktop;

int main() {
    int op;
    scanf("%d", &op);
    while (op != -1) {
        if (op == 1) {
            int num;
            scanf("%d", &num);
            if (stacktop == 100) {
                printf("error ");
            }
            else {
                stack[stacktop++] = num;
            }
        }
        else if (op == 0) {
            if (stacktop == 0) {
                printf("error ");
            }
            else {
                printf("%d ", stack[--stacktop]);
            }
        }
        scanf("%d", &op);
    }
    return 0;
}