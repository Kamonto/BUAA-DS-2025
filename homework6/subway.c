#include <stdio.h>
#include <string.h>

#define INF 114514

int allline;

struct Node {
    int index;
    char name[50];
    int lastindex;
    int distance;
    int vis;
};

struct Node nodes[500];
int allnode;

int matrix[500][500]; // line name

struct Path {
    int beginindex;
    int endindex;
    int distance;
    int line;
};

struct Path paths[500];
int allpath;

int main() {
    // FILE *in = fopen("C:\\Users\\24502\\Desktop\\Projects\\DS2025\\homework6\\bgstations.txt", "r");
    FILE *in = fopen("bgstations.txt", "r");
    int nowline;
    fscanf(in, "%d", &allline);
    while (fscanf(in, "%d", &nowline) != EOF) {
        int allstation;
        fscanf(in, "%d", &allstation);
        int lastrealindex = -1;
        for (int i = 0; i < allstation; i++) {
            char name[50] = {'\0'};
            int isChange; // actually no use
            fscanf(in, "%s", name);
            fscanf(in, "%d", &isChange);
            int vis = 0;
            int realindex;
            if (isChange == 1) {
                for (int j = 0; j < allnode; j++) {
                    if (!strcmp(nodes[j].name, name)) {
                        vis = 1;
                        realindex = j;
                    }
                }
            }
            if (vis == 0) {
                nodes[allnode].index = allnode;
                strcpy(nodes[allnode].name, name);
                nodes[allnode].distance = INF;
                nodes[allnode].lastindex = -1;
                nodes[allnode].vis = 0;
                realindex = allnode;
                allnode++;
            }
            if (lastrealindex != -1) {
                matrix[lastrealindex][realindex] = nowline;
                matrix[realindex][lastrealindex] = nowline;
            }
            lastrealindex = realindex;
        }
    }

    char beginstation[50] = {'\0'};
    char endstation[50] = {'\0'};
    scanf("%s", beginstation);
    scanf("%s", endstation);
    int beginindex = -1, endindex = -1;
    for (int i = 0; i < allnode; i++) {
        if (!strcmp(nodes[i].name, beginstation)) {
            beginindex = i;
        }
        if (!strcmp(nodes[i].name, endstation)) {
            endindex = i;
        }
    }
    nodes[beginindex].distance = 0;

    while (1) {
        int min = INF, wheremin = -1;
        for (int i = 0; i < allnode; i++) {
            if (nodes[i].vis == 0 && nodes[i].distance < min) {
                min = nodes[i].distance;
                wheremin = i;
            }
        }
        nodes[wheremin].vis = 1;
        // printf("wheremin : %s\n", nodes[wheremin].name);
        if (wheremin == endindex) {
            break;
        }
        for (int i = 0; i < allnode; i++) {
            if (matrix[wheremin][i]) {
                if (nodes[i].distance > nodes[wheremin].distance + 1) {
                    nodes[i].distance = nodes[wheremin].distance + 1;
                    nodes[i].lastindex = wheremin;
                    // printf("%s's last station: %s, line %d\n", nodes[i].name, nodes[wheremin].name, matrix[wheremin][i]);
                }
            }
        }
    }

    int nextindex = endindex;
    for (int i = nodes[endindex].lastindex; i != -1; i = nodes[i].lastindex) {
        int line = matrix[i][nextindex];
        if (allpath == 0 || paths[allpath - 1].line != line) {
            paths[allpath].beginindex = i;
            paths[allpath].endindex = nextindex;
            paths[allpath].distance = 1;
            paths[allpath].line = line;
            allpath++;
        }
        else {
            paths[allpath - 1].beginindex = i;
            paths[allpath - 1].distance++;
        }
        nextindex = i;
    }

    for (int i = allpath - 1; i >= 0; i--) {
        if (i > 0) {
            printf("%s-%d(%d)-", nodes[paths[i].beginindex].name, paths[i].line, paths[i].distance);
        }
        else {
            printf("%s-%d(%d)-%s", nodes[paths[i].beginindex].name, paths[i].line, paths[i].distance, nodes[paths[i].endindex].name);
        }
    }
    return 0;
}
