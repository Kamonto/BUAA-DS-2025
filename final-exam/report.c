#include <stdio.h>

struct News {
    char name[105];
    char date[10];
};

struct News enews[105];
int nowenews;
struct News dnews[105];
int nowdnews;
struct News cnews[105];
int nowcnews;

int main() {
    char op;
    scanf("%c", &op);
    while (op != 'R') {
        if (op == 'E') {
            scanf("%s", enews[nowenews].name);
            scanf("%s", enews[nowenews].date);
            nowenews++;
        }
        else if (op == 'D') {
            scanf("%s", dnews[nowdnews].name);
            scanf("%s", dnews[nowdnews].date);
            nowdnews++;
        }
        else if (op == 'C') {
            scanf("%s", cnews[nowcnews].name);
            scanf("%s", cnews[nowcnews].date);
            nowcnews++;
        }
        else if (op == 'S') {
            int newsnum;
            scanf("%d", &newsnum);
            getchar();
            for (int i = 0; i < newsnum; i++) {
                if (nowenews > 0) {
                    nowenews--;
                    printf("E %s %s\n", enews[nowenews].name, enews[nowenews].date);
                }
                else if (nowdnews > 0) {
                    nowdnews--;
                    printf("D %s %s\n", dnews[nowdnews].name, dnews[nowdnews].date);
                }
                else if (nowcnews > 0) {
                    nowcnews--;
                    printf("C %s %s\n", cnews[nowcnews].name, cnews[nowcnews].date);
                }
            }
        }
        scanf("%c", &op);
    }
    // printf("%d %d %d\n", nowenews, nowdnews, nowcnews);
    for (int i = nowenews - 1; i >= 0; i--) {
        printf("E %s %s\n", enews[i].name, enews[i].date);
    }
    for (int i = nowdnews - 1; i >= 0; i--) {
        printf("D %s %s\n", dnews[i].name, dnews[i].date);
    }
    for (int i = nowcnews - 1; i >= 0; i--) {
        printf("C %s %s\n", cnews[i].name, cnews[i].date);
    }
    return 0;
}