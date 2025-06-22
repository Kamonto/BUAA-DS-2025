#include <stdio.h>
#include <stdlib.h>

struct Silver {
    int weight;
    struct Silver *next;
};

struct Silver *head = NULL;
struct Silver *tail = NULL;

struct Silver *createSilver(int w) {
    struct Silver *p = (struct Silver *)malloc(sizeof(struct Silver));
    p->weight = w;
    p->next = NULL;
    return p;
}

void insertSilver(struct Silver *p) {
    int op = p->weight;
    if (head == NULL) {
        head = p;
        tail = p;
    }
    else if (op < head->weight) {
        p->next = head;
        head = p;
    }
    else if (op >= tail->weight) {
        tail->next = p;
        tail = p;
    }
    else {
        struct Silver *last;
        for (last = head; last->next->weight <= op; last = last->next);
        p->next = last->next;
        last->next = p;
    }
}

struct Silver *removeSilver(struct Silver *p) {
    if (p == head) {
        if (p->next == NULL) {
            head = NULL;
            tail = NULL;
            return NULL;
        }
        else {
            head = p->next;
            return head;
        }
    }
    struct Silver *last = NULL;
    for (last = head; last->next != p; last = last->next);
    if (p->next == NULL) {
        tail = last;
        tail->next = NULL;
        return NULL;
    }
    else {
        last->next = p->next;
        return last->next;
    }
}

int allweight = 0;

int main() {
    int op;
    scanf("%d", &op);
    while (op != 999999) {
        if (op > 0) {
            struct Silver *p = createSilver(op);
            insertSilver(p);
            allweight += op;
            // printf("%d : OK\n", op);
        }
        else if (op < 0) {
            int target = (-op);
            int nowweight = 0;
            if (target > allweight) {
                scanf("%d", &op);
                continue;
            }
            else {
                while (nowweight < target) {
                    nowweight += head->weight;
                    head = head->next;
                }
                if (nowweight > target) {
                    int left = nowweight - target;
                    struct Silver *p = createSilver(left);
                    insertSilver(p);
                }
            }
            allweight += op;
            // printf("%d : OK\n", op);
        }
        else if (op == 0) {
            int nowweight = 0;
            struct Silver *temp = head;
            while (temp != NULL) {
                if (temp->weight < 10) {
                    nowweight += temp->weight;
                    temp = removeSilver(temp);
                }
                else {
                    temp = temp->next;
                }
            }
            if (nowweight > 0) {
                struct Silver *p = createSilver(nowweight);
                insertSilver(p);
            }
            // printf("%d : OK\n", op);
        }
        // struct Silver *nowp;
        // for (nowp = head; nowp != NULL; nowp = nowp->next) {
        //     printf("%d ", nowp->weight);
        // }
        // printf("allweight: %d\n", allweight);
        scanf("%d", &op);
    }
    struct Silver *nowp;
    for (nowp = head; nowp != NULL; nowp = nowp->next) {
        printf("%d ", nowp->weight);
    }
    return 0;
}