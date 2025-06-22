#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Student {
    char id[10];
    char name[30];
    int time;
};

struct Student students[105];
int allstudent;

void insertStudent(struct Student student) {
    for (int i = 0; i < allstudent; i++) {
        if (!strcmp(students[i].id, student.id)) {
            students[i].time += student.time;
            return;
        }
    }
    students[allstudent++] = student;
}

int qsortrule(const void *P1, const void *P2) {
    struct Student *p1 = (struct Student *)P1;
    struct Student *p2 = (struct Student *)P2;
    if (p1->time < p2->time) {
        return 1;
    }
    else if (p1->time > p2->time) {
        return -1;
    }
    else if (strcmp(p1->id, p2->id) < 0) {
        return -1;
    }
    else if (strcmp(p1->id, p2->id) > 0) {
        return 1;
    }
    else {
        return 0;
    }
}

int main() {
    int allnote;
    scanf("%d", &allnote);
    for (int i = 0; i < allnote; i++) {
        struct Student student;
        scanf("%s%s%d", student.id, student.name, &student.time);
        insertStudent(student);
    }
    qsort(students, allstudent, sizeof(struct Student), qsortrule);
    for (int i = 0; i < allstudent; i++) {
        printf("%s %s %d\n", students[i].id, students[i].name, students[i].time);
    }
    return 0;
}