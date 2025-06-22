#include <stdio.h>
#include <string.h>

struct Hvref {
    char name[35];
    char year[35];
};

struct Hvref hvrefs[105];
int allhvref = 0;

char nowname[35];
int nownamehead = 0;
char nowyear[35];
int nowyearhead = 0;
int nameflag = 0;
int yearflag = 0;

void insertHvref() {
    for (int i = 0; i < allhvref; i++) {
        if (!strcmp(nowname, hvrefs[i].name) && !strcmp(nowyear, hvrefs[i].year)) {
            return;
        }
    }
    strcpy(hvrefs[allhvref].name, nowname);
    strcpy(hvrefs[allhvref++].year, nowyear);
}

int main() {
    char c;
    scanf("%c", &c);
    while (c != '\n') {
        if (c == ')') {
            yearflag = 0;
            insertHvref();
            int namelen = strlen(nowname);
            int yearlen = strlen(nowyear);
            for (int i = 0; i < namelen; i++) {
                nowname[i] = '\0';
            }
            for (int i = 0; i < yearlen; i++) {
                nowyear[i] = '\0';
            }
            nownamehead = 0;
            nowyearhead = 0;
        }
        if (yearflag == 1) {
            if (c != ' ') {
                nowyear[nowyearhead++] = c;
            }
        }
        if (c == ',') {
            if (nameflag == 1) {
                nameflag = 0;
                yearflag = 1;
            }
        }
        if (nameflag == 1) {
            nowname[nownamehead++] = c;
        }
        if (c == '(') {
            nameflag = 1;
        }
        scanf("%c", &c);
    }
    for (int i = 0; i < allhvref; i++) {
        printf("%s ", hvrefs[i].name);
        printf("%s\n", hvrefs[i].year);
    }
    return 0;
}