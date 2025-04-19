#include <stdio.h>

int result[15][15];

int main() {
    int n, temp;
    char op;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &result[i][j]);
        }
    }
    scanf("%c", &op);
    while (op != '#') {
        if (op == '+') {
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    scanf("%d", &temp);
                    result[i][j] += temp;
                }
            }
        }
        else if (op == '-') {
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    scanf("%d", &temp);
                    result[i][j] -= temp;
                }
            }
        }
        scanf("%c", &op);
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%5d", result[i][j]);
        }
        printf("\n");
    }
    return 0;
}