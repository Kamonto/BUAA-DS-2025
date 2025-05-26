#include <stdio.h>
#include <stdlib.h>

struct Airport {
    int num;
    struct Airport *leftchild;
    struct Airport *midchild;
    struct Airport *rightchild;
};

struct NumAndWeight {
    int num;
    int weight;
};

int airports[105];
int allairports;
struct NumAndWeight airportsWithWeight[105];

struct Airport *createAirport(int num) {
    struct Airport *p = (struct Airport *)malloc(sizeof(struct Airport));
    p->num = num;
    p->leftchild = NULL;
    p->midchild = NULL;
    p->rightchild = NULL;
    return p;
}

struct Airport *findAirport(struct Airport *now, int num) {
    if (now == NULL) {
        return NULL;
    }
    if (now->num == num) {
        return now;
    }
    struct Airport *leftresult = findAirport(now->leftchild, num);
    if (leftresult != NULL) {
        return leftresult;
    }
    struct Airport *midresult = findAirport(now->midchild, num);
    if (midresult != NULL) {
        return midresult;
    }
    struct Airport *rightresult = findAirport(now->rightchild, num);
    if (rightresult != NULL) {
        return rightresult;
    }
    return NULL;
}

struct Airport *level_order[105];

void level_order_traversal(struct Airport *root) {
    level_order[0] = root;
    for (int head = 0, tail = 1; head < tail; head++) {
        if (level_order[head]->leftchild != NULL) {
            level_order[tail++] = level_order[head]->leftchild;
        }
        if (level_order[head]->midchild != NULL) {
            level_order[tail++] = level_order[head]->midchild;
        }
        if (level_order[head]->rightchild != NULL) {
            level_order[tail++] = level_order[head]->rightchild;
        }
        if (level_order[head]->num < 100) {
            airports[allairports++] = level_order[head]->num;
        }
    }
}

int qsortrule(const void *P1, const void *P2) {
    struct NumAndWeight *p1 = (struct NumAndWeight *)P1;
    struct NumAndWeight *p2 = (struct NumAndWeight *)P2;
    if (p1->weight > p2->weight) {
        return -1;
    }
    else if (p1->weight < p2->weight) {
        return 1;
    }
    else if (p1->num < p2->num) {
        return -1;
    }
    else if (p1->num > p2->num) {
        return 1;
    }
    else {
        return 0;
    }
}

int main() {
    struct Airport *root = createAirport(100);
    int parentnum;
    scanf("%d", &parentnum);
    while (parentnum != -1) {
        struct Airport *parent = findAirport(root, parentnum);
        int childnum;
        scanf("%d", &childnum);
        while (childnum != -1) {
            if (parent->leftchild == NULL) {
                parent->leftchild = createAirport(childnum);
            }
            else if (parent->midchild == NULL) {
                parent->midchild = createAirport(childnum);
            }
            else {
                parent->rightchild = createAirport(childnum);
            }
            scanf("%d", &childnum);
        }
        scanf("%d", &parentnum);
    }

    level_order_traversal(root);

    for (int i = 0; i < allairports; i++) {
        scanf("%d%d", &airportsWithWeight[i].num, &airportsWithWeight[i].weight);
    }
    qsort(airportsWithWeight, allairports, sizeof(struct NumAndWeight), qsortrule);

    for (int i = 0; i < allairports; i++) {
        printf("%d->%d\n", airportsWithWeight[i].num, airports[i]);
    }
    return 0;
}