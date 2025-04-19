#include <stdio.h>
#include <stdlib.h>

struct Memory {
    int addr;
    int size;
    struct Memory *next;
};

struct Memory *head = NULL;
struct Memory *now  = NULL;

struct Memory *createMemory(int addr, int size) {
    struct Memory *p;
    p = (struct Memory *)malloc(sizeof(struct Memory));
    p->addr = addr;
    p->size = size;
    p->next = NULL;
    return p;
}

struct Memory *removeMemory(struct Memory *p) {
    struct Memory *last = NULL;
    for (last = head; last->next != p; last = last->next);
    last->next = p->next;
    if (p == head) {
        head = p->next;
    }
    free(p);
    if (last == p) {
        head = NULL;
        now  = NULL;
        return NULL;
    }
    else {
        return last->next;
    }
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        int addr, size;
        scanf("%d%d", &addr, &size);
        if (head == NULL) {
            head = createMemory(addr, size);
            now  = head;
        }
        else {
            now->next = createMemory(addr, size);
            now = now->next;
        }
    }
    now->next = head;
    now = head;

    int request;
    scanf("%d", &request);
    while (request != -1) {
        if (head != NULL) {
            struct Memory *temp = now;
            int minsize = -1;
            struct Memory *whereminsize = NULL;
            do {
                if (now->size >= request && (minsize == -1 || now->size < minsize)) {
                    minsize = now->size;
                    whereminsize = now;
                }
                now = now->next;
            } while (now != temp);
            if (minsize > request) {
                whereminsize->size -= request;
                now = whereminsize;
            }
            else if (minsize == request) {
                now = removeMemory(whereminsize);
            }
        }
        scanf("%d", &request);
    }

    if (head != NULL) {
        struct Memory *temp = now;
        do {
            printf("%d %d\n", now->addr, now->size);
            now = now->next;
        } while (now != temp);
    }
    return 0;
}