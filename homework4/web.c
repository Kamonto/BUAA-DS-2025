#include <stdio.h>
#include <string.h>

struct Website {
    char page[85];
    char address[85];
};

struct Favorite {
    char address[85];
    int times;
};

struct Website forwardStack[105];
struct Website backwardStack[105];
int forwardhead;
int backwardhead;

struct Favorite favoriteList[105] = {{"www.baidu.com", 1}};
int allFavorite;

char command[10];
struct Website nowwebsite = {"https://www.baidu.com/", "www.baidu.com"};

void addFavoriteList() {
    for (int i = 0; i < allFavorite; i++) {
        if (!strcmp(nowwebsite.address, favoriteList[i].address)) {
            favoriteList[i].times++;
            return;
        }
    }
    struct Favorite favorite;
    strcpy(favorite.address, nowwebsite.address);
    favorite.times = 1;
    favoriteList[allFavorite++] = favorite;
    return;
}

int main() {
    printf("https://www.baidu.com/\n");
    scanf("%s", command);
    while (strcmp(command, "QUIT")) {
        if (!strcmp(command, "VISIT")) {
            backwardStack[backwardhead++] = nowwebsite;

            struct Website website;
            scanf("%s", website.page);
            // website.page[8] is the first character after "https://"
            char *whereslash = strchr(website.page + 8, '/');
            int addresslen = whereslash - website.page - 8;
            strncpy(website.address, website.page + 8, addresslen);
            nowwebsite = website;
            addFavoriteList();
            printf("%s\n", nowwebsite.page);

            forwardhead = 0;
        }
        else if (!strcmp(command, "<<")) {
            if (backwardhead > 0) {
                forwardStack[forwardhead++] = nowwebsite;
                nowwebsite = backwardStack[--backwardhead];
                addFavoriteList();
                printf("%s\n", nowwebsite.page);
            }
        }
        else if (!strcmp(command, ">>")) {
            if (forwardhead > 0) {
                backwardStack[backwardhead++] = nowwebsite;
                nowwebsite = forwardStack[--forwardhead];
                addFavoriteList();
                printf("%s\n", nowwebsite.page);
            }
        }
        scanf("%s", command);
    }
    scanf("%s", command);
    if (!strcmp(command, "0")) {
        int max = 0, wheremax = -1;
        for (int i = 0; i < allFavorite; i++) {
            if (favoriteList[i].times > max) {
                max = favoriteList[i].times;
                wheremax = i;
            }
        }
        printf("%s %d", favoriteList[wheremax].address, favoriteList[wheremax].times);
    }
    return 0;
}