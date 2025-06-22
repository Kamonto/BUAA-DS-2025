#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Dish {
    char name[10];
    int num;
    int money;
};

struct Dish dishes[100];
int alldish;

int allmoney;

int qsortrule(const void *P1, const void *P2) {
    struct Dish *p1 = (struct Dish *)P1;
    struct Dish *p2 = (struct Dish *)P2;
    if (p1->money > p2->money) {
        return -1;
    }
    else if (p1->money < p2->money) {
        return 1;
    }
    else if (p1->num > p2->num) {
        return -1;
    }
    else if (p1->num < p2->num) {
        return 1;
    }
    else {
        return 0;
    }
}

int main() {
    int allorder;
    scanf("%d", &allorder);
    for (int i = 0; i < allorder; i++) {
        int order;
        char name[10] = {'\0'};
        int num;
        int money;
        scanf("%d%s%d%d", &order, name, &num, &money);
        int visflag = 0;
        for (int i = 0; i < alldish; i++) {
            if (!strcmp(dishes[i].name, name)) {
                visflag = 1;
                dishes[i].num += num;
                dishes[i].money += num * money;
                break;
            }
        }
        if (visflag == 0) {
            strcpy(dishes[alldish].name, name);
            dishes[alldish].num = num;
            dishes[alldish].money = num * money;
            alldish++;
        }
        allmoney += num * money;
    }
    qsort(dishes, alldish, sizeof(struct Dish), qsortrule);
    printf("%d\n", allmoney);
    for (int i = 0; i < alldish; i++) {
        printf("%s %d %d\n", dishes[i].name, dishes[i].num, dishes[i].money);
    }
    return 0;
}