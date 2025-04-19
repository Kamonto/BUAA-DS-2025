#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Person {
    char name[30];
    char number[20];
    int times;
};

struct Person persons[110];
int personshead;

int qsortrule(const void *P1, const void *P2) {
    struct Person *p1 = (struct Person *)P1;
    struct Person *p2 = (struct Person *)P2;
    if (strcmp(p1->name, p2->name) < 0) {
        return -1;
    }
    else if (strcmp(p1->name, p2->name) > 0) {
        return 1;
    }
    else {
        if (p1->times < p2->times) {
            return -1;
        }
        else if (p1->times > p2->times) {
            return 1;
        }
        else {
            return 0;
        }
    }
}

int main() {
    int allperson;
    scanf("%d", &allperson);
    for (int i = 0; i < allperson; i++) {
        struct Person person;
        scanf("%s", person.name);
        scanf("%s", person.number);
        person.times = 0;
        int flag = 1;
        for (int j = 0; j < personshead; j++) {
            if (strcmp(person.name, persons[j].name) == 0) {
                if (strcmp(person.number, persons[j].number) == 0) {
                    flag = 0;
                    break;
                }
                else {
                    if (person.times <= persons[j].times) {
                        person.times = persons[j].times + 1;
                    }
                }
            }
        }
        if (flag) {
            persons[personshead++] = person;
        }
    }
    qsort(persons, personshead, sizeof(struct Person), qsortrule);
    for (int i = 0; i < personshead; i++){
        if (persons[i].times > 0) {
            printf("%s_%d %s\n", persons[i].name, persons[i].times, persons[i].number);
        }
        else {
            printf("%s %s\n", persons[i].name, persons[i].number);
        }
    }
    return 0;
}