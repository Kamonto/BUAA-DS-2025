#include <stdio.h>
#include <stdlib.h>

int num[1000];
int allnum;

int seek(int n) {
    for (int i = 0; i < allnum; i++) {
        if (num[i] == n) {
            return i;
        }
    }
    return -1;
}

int qsortrule(const void *P1, const void *P2) {
    int *p1 = (int *)P1;
    int *p2 = (int *)P2;
    if (*p1 < *p2) {
        return 1;
    }
    else if (*p1 > *p2) {
        return -1;
    }
    else {
        return 0;
    }
}

int main() {
    int n;
    while (scanf("%d", &n) != EOF) {
        int isseek = seek(n);
        if (isseek == -1) {
            num[allnum++] = n;
        }
        else {
            num[isseek] = -114514;
        }
    }
    qsort(num, allnum, sizeof(int), qsortrule);
    for (int i = 0; i < allnum; i++) {
        if (num[i] != -114514) {
            printf("%d ", num[i]);
        }
    }
    return 0;
}