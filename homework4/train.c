#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Station {
    char name[25];
    int distance;
};

struct Request {
    char number[5];
    char destination[25];
    int distance;
};

struct Station stations[55];
struct Request requests[55];

int main() {
    int allstation, allrequest;
    int allpush = 0;
    scanf("%d", &allstation);
    for (int i = 0; i < allstation; i++) {
        scanf("%s%d", stations[i].name, &stations[i].distance);
    }
    scanf("%d", &allrequest);
    for (int i = 0; i < allrequest; i++) {
        scanf("%s%s", requests[i].number, requests[i].destination);
        for (int j = 0; j < allstation; j++) {
            if (!strcmp(requests[i].destination, stations[j].name)) {
                requests[i].distance = stations[j].distance;
                break;
            }
        }
    }
    for (int i = 0; i < allrequest; i++) {
        allpush++;
        int flag = 0;
        for (int j = 0; j < i; j++) {
            if (requests[i].distance > requests[j].distance) {
                allpush++;
                flag = 1;
            }
        }
        if (flag) {
            allpush++;
        }
    }
    for (int i = 1; i < allrequest; i++) {
        for (int j = 0; j < allrequest - i; j++) {
            if (requests[j].distance < requests[j + 1].distance) {
                struct Request temp = requests[j];
                requests[j] = requests[j + 1];
                requests[j + 1] = temp;
            }
        }
    }
    for (int i = 0; i < allrequest; i++) {
        printf("%s ", requests[i].number);
    }
    printf("\n%d", allpush);
    return 0;
}