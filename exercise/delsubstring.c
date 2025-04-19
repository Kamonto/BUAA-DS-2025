#include <stdio.h>
#include <string.h>

char str1[1000];
char str2[1000];

int main() {
    fgets(str1, 1000, stdin);
    fgets(str2, 1000, stdin);
    str1[strlen(str1) - 1] = '\0';
    str2[strlen(str2) - 1] = '\0';
    char *head = str1;
    char *tail = strstr(str1, str2);
    while (tail != NULL) {
        while (head != tail) {
            printf("%c", *head);
            head++;
        }
        head = tail + strlen(str2);
        tail = strstr(head, str2);
    }
    printf("%s", head);
    return 0;
}