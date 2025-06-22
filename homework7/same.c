#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Note {
    char number[15];
    char where;
    char arrive[10];
    char leave[10];
};

struct Note notes[1000];
int allnote;

struct Note targetNotes[1000];
int alltargetNote;

struct Note notTargetNotes[1000];
int allnotTargetNote;

struct Note res[1000];
int allres;

char target[15];

int qsortrule(const void *P1, const void *P2) {
    struct Note *p1 = (struct Note *)P1;
    struct Note *p2 = (struct Note *)P2;
    if (strcmp(p1->number, p2->number) < 0) {
        return -1;
    }
    else if (strcmp(p1->number, p2->number) > 0) {
        return 1;
    }
    else if (p1->where < p2->where) {
        return -1;
    }
    else if (p1->where > p2->where) {
        return 1;
    }
    else {
        return 0;
    }
}

int main() {
    scanf("%d", &allnote);
    for (int i = 0; i < allnote; i++) {
        scanf("%s", notes[i].number);
        getchar();
        scanf("%c", &notes[i].where);
        getchar();
        scanf("%s", notes[i].arrive);
        scanf("%s", notes[i].leave);
    }
    scanf("%s", target);
    for (int i = 0; i < allnote; i++) {
        if (strcmp(notes[i].number, target)) {
            notTargetNotes[allnotTargetNote++] = notes[i];
        }
        else {
            targetNotes[alltargetNote++] = notes[i];
        }
    }
    for (int i = 0; i < allnotTargetNote; i++) {
        for (int j = 0; j < alltargetNote; j++) {
            if ((notTargetNotes[i].where == targetNotes[j].where) && 
                (!(strcmp(notTargetNotes[i].leave, targetNotes[j].arrive) < 0 || 
                strcmp(notTargetNotes[i].arrive, targetNotes[j].leave) > 0))) {
                int flag = 0;
                for (int k = 0; k < allres; k++) {
                    if (!strcmp(notTargetNotes[i].number, res[k].number) && 
                        notTargetNotes[i].where == res[k].where) {
                        flag = 1;
                        break;
                    }
                }
                if (flag == 0) {
                    res[allres++] = notTargetNotes[i];
                }
            }
        }
    }
    qsort(res, allres, sizeof(struct Note), qsortrule);
    for (int i = 0; i < allres; i++) {
        printf("%s %c\n", res[i].number, res[i].where);
    }
    return 0;
}