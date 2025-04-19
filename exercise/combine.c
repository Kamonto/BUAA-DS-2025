#include <stdio.h>
#include <string.h>

char str1[205];
char str2[205];

void str_bin(char *str1, char *str2) {
    char result[205] = {'\0'};
    int i = 0, j = 0, head = 0;
    while (str1[i] != '\0' && str2[j] != '\0') {
        if (str1[i] < str2[j]) {
            result[head++] = str1[i++];
        }
        else {
            result[head++] = str2[j++];
        }
    }
    if (str1[i] == '\0') {
        strcat(result, str2 + j);
    }
    if (str2[j] == '\0') {
        strcat(result, str1 + i);
    }
    strcpy(str1, result);
}

int main() {
    scanf("%s", str1);
    scanf("%s", str2);
    str_bin(str1, str2);
    printf("%s", str1);
    return 0;
}