#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define NHASH 3001
#define MULT 37

struct Bird {
    char str[30];
    struct Bird *next;
};

struct Bird *birds[3500];
int allbird;

int index_begin[30];
int index_count[30];

struct Bird *hashMap[3500];

unsigned int hashCode(struct Bird *bird) {
    unsigned int hash = 0;
    int len = strlen(bird->str);
    for (int i = 0; i < len; i++) {
        hash = MULT * hash + bird->str[i];
    }
    return hash % NHASH;
}

int sequentialSearch(struct Bird *bird) {
    int times = 0;
    for (int i = 0; i < allbird; i++) {
        times++;
        if (strcmp(birds[i]->str, bird->str) > 0) {
            return -times;
        }
        else if (strcmp(birds[i]->str, bird->str) == 0) {
            return times;
        }
    }
    return -times;
}

int binarySearch(struct Bird *bird, int left, int right) {
    int times = 0;
    while (left < right) {
        int mid = (left + right - 1) / 2;
        times++;
        if (strcmp(birds[mid]->str, bird->str) < 0) {
            left = mid + 1;
        }
        else if (strcmp(birds[mid]->str, bird->str) > 0) {
            right = mid;
        }
        else {
            return times;
        }
    }
    return -times;
}

int indexSearch(struct Bird *bird) {
    char firstchar = bird->str[0];
    int left = index_begin[firstchar - 'a'];
    int right = left + index_count[firstchar - 'a'];
    return binarySearch(bird, left, right);
}

int hashSearch(struct Bird *bird) {
    int times = 0;
    int hash = hashCode(bird);
    for (struct Bird *p = hashMap[hash]; p != NULL; p = p->next) {
        times++;
        if (strcmp(p->str, bird->str) > 0) {
            return -times;
        }
        else if (strcmp(p->str, bird->str) == 0) {
            return times;
        }
    }
    return -times;
}

int main() {
    // FILE *in = fopen("C:\\Users\\24502\\Desktop\\Projects\\DS2025\\homework7\\dictionary3000.txt", "r");
    FILE *in = fopen("dictionary3000.txt", "r");
    struct Bird *bird = (struct Bird *)malloc(sizeof(struct Bird));
    while (fscanf(in, "%s", bird->str) != EOF) {
        bird->next = NULL;
        birds[allbird] = bird;
        char firstchar = bird->str[0];
        if (index_count[firstchar - 'a'] == 0) {
            index_begin[firstchar - 'a'] = allbird;
        }
        index_count[firstchar - 'a']++;
        int hash = hashCode(bird);
        if (hashMap[hash] == NULL) {
            hashMap[hash] = bird;
        }
        else {
            struct Bird *last = NULL;
            for (last = hashMap[hash]; last->next != NULL; last = last->next);
            last->next = bird;
        }
        allbird++;
        bird = (struct Bird *)malloc(sizeof(struct Bird));
    }
    
    int times = 0;
    int op;
    scanf("%s%d", bird->str, &op);
    if (op == 1) {
        times = sequentialSearch(bird);
    }
    else if (op == 2) {
        times = binarySearch(bird, 0, allbird);
    }
    else if (op == 3) {
        times = indexSearch(bird);
    }
    else if (op == 4) {
        times = hashSearch(bird);
    }
    if (times > 0) {
        printf("1 %d", times);
    }
    else {
        printf("0 %d", -times);
    }
    return 0;
}