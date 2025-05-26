#include <stdio.h>
#include <stdlib.h>

struct Number {
    int num;
    int height;
    struct Number *leftchild;
    struct Number *rightchild;
};

struct Number *root = NULL;

struct Number *createNumber(int num, int height) {
    struct Number *p = (struct Number *)malloc(sizeof(struct Number));
    p->num = num;
    p->height = height;
    p->leftchild = NULL;
    p->rightchild = NULL;
    return p;
}

void insertNum(int num) {
    if (root == NULL) {
        root = createNumber(num, 1);
        return;
    }
    else {
        struct Number *now = root;
        while (1) {
            if (num < now->num) {
                if (now->leftchild == NULL) {
                    struct Number *new = createNumber(num, now->height + 1);
                    now->leftchild = new;
                    return;
                }
                else {
                    now = now->leftchild;
                }
            }
            else {
                if (now->rightchild == NULL) {
                    struct Number *new = createNumber(num, now->height + 1);
                    now->rightchild = new;
                    return;
                }
                else {
                    now = now->rightchild;
                }
            }
        }
    }
}

void leaf_traversal(struct Number *now) {
    if (now->leftchild == NULL && now->rightchild == NULL) {
        printf("%d %d\n", now->num, now->height);
        return;
    }
    if (now->leftchild != NULL) {
        leaf_traversal(now->leftchild);
    }
    if (now->rightchild != NULL) {
        leaf_traversal(now->rightchild);
    }
}

int main() {
    int allnum;
    scanf("%d", &allnum);
    for (int i = 0; i < allnum; i++) {
        int num;
        scanf("%d", &num);
        insertNum(num);
    }
    if (root != NULL) {
        leaf_traversal(root);
    }
    return 0;
}