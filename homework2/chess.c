#include <stdio.h>

int chess[25][25];

int main() {
    for (int i = 0; i < 25; i++) {
        for (int j = 0; j < 25; j++) {
            chess[i][j] = -1;
        }
    }
    for (int i = 1; i <= 19; i++) {
        for (int j = 1; j <= 19; j++) {
            scanf("%d", &chess[i][j]);
        }
    }
    for (int i = 1; i <= 19; i++) {
        for (int j = 1; j <= 16; j++) {
            if (chess[i][j] == 1 && chess[i][j + 1] == 1 && chess[i][j + 2] == 1 && chess[i][j + 3] == 1) {
                if (chess[i][j - 1] == 0 || chess[i][j + 4] == 0) {
                    printf("1:%d,%d\n", i, j);
                    return 0;
                }
            }
            if (chess[i][j] == 2 && chess[i][j + 1] == 2 && chess[i][j + 2] == 2 && chess[i][j + 3] == 2) {
                if (chess[i][j - 1] == 0 || chess[i][j + 4] == 0) {
                    printf("2:%d,%d\n", i, j);
                    return 0;
                }
            }
        }
    }
    for (int i = 1; i <= 16; i++) {
        for (int j = 1; j <= 19; j++) {
            if (chess[i][j] == 1 && chess[i + 1][j] == 1 && chess[i + 2][j] == 1 && chess[i + 3][j] == 1) {
                if (chess[i - 1][j] == 0 || chess[i + 4][j] == 0) {
                    printf("1:%d,%d\n", i, j);
                    return 0;
                }
            }
            if (chess[i][j] == 2 && chess[i + 1][j] == 2 && chess[i + 2][j] == 2 && chess[i + 3][j] == 2) {
                if (chess[i - 1][j] == 0 || chess[i + 4][j] == 0) {
                    printf("2:%d,%d\n", i, j);
                    return 0;
                }
            }
        }
    }
    for (int i = 1; i <= 16; i++) {
        for (int j = 1; j <= 16; j++) {
            if (chess[i][j] == 1 && chess[i + 1][j + 1] == 1 && chess[i + 2][j + 2] == 1 && chess[i + 3][j + 3] == 1) {
                if (chess[i - 1][j - 1] == 0 || chess[i + 4][j + 4] == 0) {
                    printf("1:%d,%d\n", i, j);
                    return 0;
                }
            }
            if (chess[i][j] == 2 && chess[i + 1][j + 1] == 2 && chess[i + 2][j + 2] == 2 && chess[i + 3][j + 3] == 2) {
                if (chess[i - 1][j - 1] == 0 || chess[i + 4][j + 4] == 0) {
                    printf("2:%d,%d\n", i, j);
                    return 0;
                }
            }
        }
    }
    for (int i = 1; i <= 16; i++) {
        for (int j = 4; j <= 19; j++) {
            if (chess[i][j] == 1 && chess[i + 1][j - 1] == 1 && chess[i + 2][j - 2] == 1 && chess[i + 3][j - 3] == 1) {
                if (chess[i - 1][j + 1] == 0 || chess[i + 4][j - 4] == 0) {
                    printf("1:%d,%d\n", i, j);
                    return 0;
                }
            }
            if (chess[i][j] == 2 && chess[i + 1][j - 1] == 2 && chess[i + 2][j - 2] == 2 && chess[i + 3][j - 3] == 2) {
                if (chess[i - 1][j + 1] == 0 || chess[i + 4][j - 4] == 0) {
                    printf("2:%d,%d\n", i, j);
                    return 0;
                }
            }
        }
    }
    printf("No\n");
    return 0;
}