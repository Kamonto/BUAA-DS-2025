#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

char nowbird[100];
int nowbirdhead;

struct TreeBird {
    char bird[100];
    int times;
    struct TreeBird *leftchild;
    struct TreeBird *rightchild;
};

struct TreeBird *root = NULL;

struct TreeBird *createBird() {
    struct TreeBird *p = (struct TreeBird *)malloc(sizeof(struct TreeBird));
    strcpy(p->bird, nowbird);
    p->times = 1;
    p->leftchild = NULL;
    p->rightchild = NULL;
    return p;
}

void insertBird() {
    if (root == NULL) {
        root = createBird();
        return;
    }
    else {
        struct TreeBird *now = root;
        while (1) {
            if (strcmp(nowbird, now->bird) < 0) {
                if (now->leftchild == NULL) {
                    struct TreeBird *new = createBird();
                    now->leftchild = new;
                    return;
                }
                else {
                    now = now->leftchild;
                }
            }
            else if (strcmp(nowbird, now->bird) > 0) {
                if (now->rightchild == NULL) {
                    struct TreeBird *new = createBird();
                    now->rightchild = new;
                    return;
                }
                else {
                    now = now->rightchild;
                }
            }
            else {
                now->times++;
                return;
            }
        }
    }
}

void inorder_traversal(struct TreeBird *now) {
    if (now == NULL) {
        return;
    }
    else {
        inorder_traversal(now->leftchild);
        printf("%s %d\n", now->bird, now->times);
        inorder_traversal(now->rightchild);
    }
}

int main() {
    // FILE *in = fopen("C:\\Users\\24502\\Desktop\\Projects\\DS2025\\homework5\\article.txt", "r");
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
    if (root != NULL) {
        printf("%s", root->bird);
        if (root->rightchild != NULL) {
            printf(" %s", root->rightchild->bird);
            if (root->rightchild->rightchild != NULL) {
                printf(" %s", root->rightchild->rightchild->bird);
            }
        }
    }
    printf("\n");
    if (root != NULL) {
        inorder_traversal(root);
    }
    return 0;
}