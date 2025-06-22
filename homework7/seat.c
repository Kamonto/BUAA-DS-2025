#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Student {
    char id[10];
    char name[30];
    int seat;
};

struct Student students[105];
int allstudent;

int qsortrule_seat(const void *P1, const void *P2) {
    struct Student *p1 = (struct Student *)P1;
    struct Student *p2 = (struct Student *)P2;
    if (p1->seat < p2->seat) {
        return -1;
    }
    else if (p1->seat > p2->seat) {
        return 1;
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

int qsortrule_id(const void *P1, const void *P2) {
    struct Student *p1 = (struct Student *)P1;
    struct Student *p2 = (struct Student *)P2;
    if (strcmp(p1->id, p2->id) < 0) {
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
    // FILE *in = fopen("C:\\Users\\24502\\Desktop\\Projects\\DS2025\\homework7\\in.txt", "r");
    FILE *in = fopen("in.txt", "r");
    // FILE *out = fopen("C:\\Users\\24502\\Desktop\\Projects\\DS2025\\homework7\\out.txt", "w");
    FILE *out = fopen("out.txt", "w");
    int allstudent;
    scanf("%d", &allstudent);
    for (int i = 0; i < allstudent; i++) {
        struct Student student;
        fscanf(in, "%s%s%d", student.id, student.name, &student.seat);
        students[i] = student;
    }
    qsort(students, allstudent, sizeof(struct Student), qsortrule_seat);
    if (students[0].seat > 1) {
        struct Student temp = students[allstudent - 1];
        for (int j = allstudent - 1; j > 0; j--) {
            students[j] = students[j - 1];
        }
        students[0] = temp;
        students[0].seat = 1;
    }
    for (int i = 1; i < allstudent; i++) {
        if (students[i].seat > students[i - 1].seat + 1) {
            struct Student temp = students[allstudent - 1];
            for (int j = allstudent - 1; j > i; j--) {
                students[j] = students[j - 1];
            }
            students[i] = temp;
            students[i].seat = students[i - 1].seat + 1;
        }
    }
    for (int i = 1; i < allstudent; i++) {
        if (students[i].seat == students[i - 1].seat) {
            struct Student temp = students[i];
            for (int j = i + 1; j < allstudent; j++) {
                students[j - 1] = students[j];
            }
            students[allstudent - 1] = temp;
            students[allstudent - 1].seat = students[allstudent - 2].seat + 1;
        }
    }
    qsort(students, allstudent, sizeof(struct Student), qsortrule_id);
    for (int i = 0; i < allstudent; i++) {
        fprintf(out, "%s %s %d\n", students[i].id, students[i].name, students[i].seat);
    }
    return 0;
}