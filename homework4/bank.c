#include <stdio.h>

struct Person {
    int number;
    int whencome;
    int whenleave;
    int worktime;
};

int personcount[1000];

struct Person waitlist[1000];
int allWaitList = 1;
int waitListHead = 1;
int waitListTail = 1;

struct Person windows[10];
int windowsbusy[10];
int windowsen[10] = {0, 1, 1, 1};
int allwindow = 3;

int main() {
    int alltime;
    scanf("%d", &alltime);
    for (int i = 1; i <= alltime; i++) {
        scanf("%d", &personcount[i]);
    }

    for (int i = 1; i <= alltime; i++) {
        for (int j = 0; j < personcount[i]; j++) {
            struct Person person;
            person.number = allWaitList;
            person.whencome = i;
            scanf("%d", &person.worktime);
            waitlist[allWaitList++] = person;
        }
    }

    int nowtime = 1;
    int waitingcount;
    while (nowtime <= alltime || waitListHead < allWaitList || windowsbusy[1] || windowsbusy[2] ||
           windowsbusy[3] || windowsbusy[4] || windowsbusy[5]) {
        if (nowtime <= alltime) {
            // add person into list
            waitListTail += personcount[nowtime];
            // update window count
            waitingcount = waitListTail - waitListHead;
            int preallwindow = allwindow;
            allwindow = waitingcount / 7 + 1;
            allwindow = (allwindow > 5) ? 5 : (allwindow < 3) ? 3 : allwindow;
            int addwindow = allwindow - preallwindow;
            for (int i = 1; i <= 5; i++) {
                if (addwindow > 0) {
                    if (windowsen[i] == 0) {
                        windowsen[i] = 1;
                        addwindow--;
                    }
                }
            }
        }
        // persons at window work
        // printf("now time: %d, open: %d\n", nowtime, allwindow);
        for (int i = 1; i <= 5; i++) {
            if (windowsbusy[i]) {
                windows[i].worktime--;
                if (windows[i].worktime == 0) {
                    waitlist[windows[i].number].whenleave = nowtime;
                    windowsbusy[i] = 0;
                }
                // printf("win %d - %d : %d\n", i, windows[i].number, windows[i].worktime);
            }
        }
        // send person from list to window
        for (int i = 1; i <= 5; i++) {
            if (windowsbusy[i] == 0 && windowsen[i] == 1) {
                if (waitListHead < waitListTail) {
                    windows[i] = waitlist[waitListHead++];
                    windowsbusy[i] = 1;
                }
            }
        }
        // update window count
        waitingcount = waitListTail - waitListHead;
        int subwindow = (allwindow > 3 &&  waitingcount / 7 < allwindow) ? 1 : 0;
        allwindow -= subwindow;
        while (subwindow > 0) {
            int min = 4, wheremin = 0;
            for (int i = 1; i <= 5; i++) {
                if (windowsen[i] == 1 && windowsbusy[i] == 0) {
                    min = 0;
                    wheremin = i;
                }
                else if (windowsen[i] == 1 && windowsbusy[i] == 1) {
                    if (windows[i].worktime <= min) {
                        min = windows[i].worktime;
                        wheremin = i;
                    }
                }
            }
            windowsen[wheremin] = 0;
            subwindow--;
        }
        nowtime++;
    }
    for (int i = 1; i < allWaitList; i++) {
        printf("%d : %d\n", i, waitlist[i].whenleave - waitlist[i].whencome - waitlist[i].worktime);
    }
    return 0;
}