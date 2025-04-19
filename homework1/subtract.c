#include <stdio.h>
#include <string.h>

char a[1000];
char b[1000];

int cmp(char *x, char *y) {
    int lenx = strlen(x);
    int leny = strlen(y);
    int maxlen = (lenx > leny) ? lenx : leny;
    if (lenx < leny) {
        for (int i = lenx - 1, j = leny - 1; i >= 0; i--, j--) {
            x[j] = x[i];
        }
        for (int i = 0; i < leny - lenx; i++) {
            x[i] = '0';
        }
    }
    else if (lenx > leny) {
        for (int i = leny - 1, j = lenx - 1; i >= 0; i--, j--) {
            y[j] = y[i];
        }
        for (int i = 0; i < lenx - leny; i++) {
            y[i] = '0';
        }
    }
    for (int i = 0; i < maxlen; i++) {
        if (x[i] < y[i]) {
            return -1;
        }
        else if (x[i] > y[i]) {
            return 1;
        }
    }
    return 0;
}

void sub(char *x, char *y) {
    int len = strlen(x);
    char invx[1000] = {'\0'};
    char invy[1000] = {'\0'};
    int invsub[1000] = {0};
    for (int i = 0; i < len; i++) {
        invx[len - i - 1] = x[i];
        invy[len - i - 1] = y[i];
    }
    for (int i = 0; i < len; i++) {
        if (invx[i] >= invy[i]) {
            invsub[i] = invx[i] - invy[i];
        }
        else {
            invsub[i] = invx[i] - invy[i] + 10;
            invx[i + 1]--;
        }
    }
    // for (int i = len - 1; i >= 0; i--) {
    //     printf("%d", invsub[i]);
    // }
    int mark = 0;
    for (int i = len - 1; i >= 0; i--) {
        if (invsub[i] != 0) {
            mark = i;
            break;
        }
    }
    for (int i = mark; i >= 0; i--) {
        printf("%d", invsub[i]);
    }
}

int main() {
    scanf("%s", a);
    scanf("%s", b);
    int cmpres = cmp(a, b);
    if (cmpres < 0) {
        printf("-");
        sub(b, a);
    }
    else if (cmpres > 0) {
        sub(a, b);
    }
    else {
        printf("0");
    }
    return 0;
}