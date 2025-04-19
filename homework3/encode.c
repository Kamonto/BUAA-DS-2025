#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int vis[200];
char encode[200];

char key[50];

struct KeySet {
    char c;
    struct KeySet *next;
};

struct KeySet *head = NULL;
struct KeySet *now = NULL;

struct KeySet *createKeySet(char c) {
    struct KeySet *p;
    p = (struct KeySet *)malloc(sizeof(struct KeySet));
    p->c = c;
    p->next = NULL;
    return p;
}

struct KeySet *removeKeySet(struct KeySet *p) {
    struct KeySet *last = NULL;
    for (last = head; last->next != p; last = last->next);
    last->next = p->next;
    if (head == p) {
        head = head->next;
    }
    free(p);
    if (last == p) {
        head = NULL;
        now = NULL;
        return NULL;
    }
    else {
        return last->next;
    }
}

int main() {
    gets(key);
    for (int i = 0; i < strlen(key); i++) {
        if (vis[key[i]] == 0) {
            vis[key[i]]++;
            if (head == NULL) {
                head = createKeySet(key[i]);
                now = head;
            }
            else {
                now->next = createKeySet(key[i]);
                now = now->next;
            }
        }
    }
    for (int i = 32; i <= 126; i++) {
        if (vis[i] == 0) {
            vis[i]++;
            if (head == NULL) {
                head = createKeySet(i);
                now = head;
            }
            else {
                now->next = createKeySet(i);
                now = now->next;
            }
        }
    }
    now->next = head;
    now = head;

    // do {
    //     printf("%c", now->c);
    //     now = now->next;
    // } while (now != head);
    // printf("\n");

    char firstchar = head->c;
    while (now->next != now) {
        char nowchar = now->c;
        now = removeKeySet(now);
        for (int i = 1; i < nowchar; i++) {
            now = now->next;
        }
        encode[nowchar] = now->c;
    }
    encode[now->c] = firstchar;

    // for (int i = 32; i <= 126; i++) {
    //     printf("%c", encode[i]);
    // }

    // FILE *in = fopen("C:\\Users\\24502\\Desktop\\Projects\\DS2025\\homework3\\in.txt", "r");
    // FILE *out = fopen("C:\\Users\\24502\\Desktop\\Projects\\DS2025\\homework3\\in_crpyt.txt", "w");
    FILE *in = fopen("in.txt", "r");
    FILE *out = fopen("in_crpyt.txt", "w");
    char filec;
    while (fscanf(in, "%c", &filec) != EOF) {
        if (filec >= 32 && filec <= 126) {
            fprintf(out, "%c", encode[filec]);
        }
        else {
            fprintf(out, "%c", filec);
        }
    }
    fclose(in);
    fclose(out);
    return 0;
}