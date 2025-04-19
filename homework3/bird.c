#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

char nowbird[100];
int nowbirdhead;

struct Bird {
    char bird[100];
    int times;
    struct Bird *next;
};

struct Bird *head = NULL;
struct Bird *tail = NULL;

struct Bird *createBird(char *bird) {
    struct Bird *p;
    p = (struct Bird *)malloc(sizeof(struct Bird));
    strcpy(p->bird, bird);
    p->times = 1;
    p->next = NULL;
    return p;
}

void insertBird() {
    struct Bird *temp = NULL;
    for (temp = head; temp != NULL; temp = temp->next) {
        if (!strcmp(temp->bird, nowbird)) {
            (temp->times)++;
            return;
        }
    }
    struct Bird *p = createBird(nowbird);
    if (head == NULL) {
        head = p;
        tail = p;
    }
    else if (strcmp(p->bird, head->bird) < 0) {
        p->next = head;
        head = p;
    }
    else if (strcmp(tail->bird, p->bird) < 0) {
        tail->next = p;
        tail = p;
    }
    else {
        for (temp = head; strcmp(temp->next->bird, p->bird) < 0; temp = temp->next);
        p->next = temp->next;
        temp->next = p;
    }
    return;
}

int main() {
    // FILE *in = fopen("C:\\Users\\24502\\Desktop\\Projects\\DS2025\\homework3\\article.txt", "r");
    FILE *in = fopen("article.txt", "r");
    char c;
    while (fscanf(in, "%c", &c) != EOF) {
        if (isalpha(c)) {
            nowbird[nowbirdhead++] = tolower(c);
        }
        else {
            if (strlen(nowbird) > 0) {
                // puts(nowbird);
                insertBird();
                for (int i = 0; i < 100; i++) {
                    nowbird[i] = '\0';
                }
                nowbirdhead = 0;
            }
        }
    }
    if (strlen(nowbird) > 0) {
        insertBird();
    }

    for (struct Bird *temp = head; temp != NULL; temp = temp->next) {
        printf("%s %d\n", temp->bird, temp->times);
    }
    return 0;
}