#include <stdio.h>
#include <string.h>

int num[1000];
char op[1000];

int main() {
    int head = 0, result = 0;
    char c;
    do {
        scanf("%c", &c);
        if (c == ' ') {
            // do nothing
        }
        else if (c >= '0' && c <= '9') {
            num[head] = num[head] * 10 + c - '0';
        }
        else {
            op[head] = c;
            if (head > 0 && op[head - 1] == '*') {
                num[head - 1] = num[head - 1] * num[head];
                num[head] = 0;
                op[head - 1] = op[head];
            }
            else if (head > 0 && op[head - 1] == '/') {
                num[head - 1] = num[head - 1] / num[head];
                num[head] = 0;
                op[head - 1] = op[head];
            }
            else {
                head++;
            }
        }
    } while (c != '=');
    // for (int i = 0; i < head; i++) {
    //     printf("%d %c ", num[i], op[i]);
    // }
    for (int i = 0; i < head; i++) {
        if (i == 0) {
            result = num[i];
        }
        else {
            if (op[i - 1] == '+') {
                result += num[i];
            }
            else {
                result -= num[i];
            }
        }
    }
    printf("%d", result);
    return 0;
}