#include <stdio.h>
#include <stdlib.h>

#define INF 114514

struct Node {
    int index;
    int number;
    int like[15];
    int lastindex;
    int distance;
    int vis;
};

int allvis;

struct Node nodes[205];
int allnode;

int matrix[205][205];

struct Path {
    int distance;
    int length;
    int indexes[205];
};

struct Path paths[205];
int allpath;

int qsortrule(const void *P1, const void *P2) {
    struct Path *p1 = (struct Path *)P1;
    struct Path *p2 = (struct Path *)P2;
    if (p1->distance < p2->distance) {
        return -1;
    }
    else if (p1->distance > p2->distance) {
        return 1;
    }
    else {
        return 0;
    }
}

int main() {
    scanf("%d", &allnode);
    for (int i = 0; i < allnode; i++) {
        int number;
        scanf("%d", &number);
        nodes[i].index = i;
        nodes[i].number = number;
        int whichlike;
        scanf("%d", &whichlike);
        while (whichlike != -1) {
            nodes[i].like[whichlike] = 1;
            scanf("%d", &whichlike);
        }
        nodes[i].lastindex = -1;
        nodes[i].distance = INF;
        nodes[i].vis = 0;
    }
    int beginnode, endnode, distance;
    scanf("%d%d%d", &beginnode, &endnode, &distance);
    while (beginnode != -1) {
        int beginindex, endindex;
        for (int i = 0; i < allnode; i++) {
            if (nodes[i].number == beginnode) {
                beginindex = i;
            }
            if (nodes[i].number == endnode) {
                endindex = i;
            }
        }
        matrix[beginindex][endindex] = distance;
        matrix[endindex][beginindex] = distance;
        scanf("%d%d%d", &beginnode, &endnode, &distance);
    }

    int fromnode, target;
    scanf("%d%d", &fromnode, &target);
    int fromindex;
    for (int i = 0; i < allnode; i++) {
        if (nodes[i].number == fromnode) {
            fromindex = i;
            break;
        }
    }
    
    nodes[fromindex].distance = 0;

    while (1) {
        int min = INF, wheremin = -1;
        for (int i = 0; i < allnode; i++) {
            if (nodes[i].vis == 0 && nodes[i].distance < min) {
                min = nodes[i].distance;
                wheremin = i;
            }
        }
        nodes[wheremin].vis = 1;
        allvis++;
        if (allvis == allnode) {
            break;
        }
        for (int i = 0; i < allnode; i++) {
            if (matrix[wheremin][i]) {
                if (nodes[i].distance > nodes[wheremin].distance + matrix[wheremin][i]) {
                    nodes[i].distance = nodes[wheremin].distance + matrix[wheremin][i];
                    nodes[i].lastindex = wheremin;
                }
            }
        }
    }

    for (int endindex = 0; endindex < allnode; endindex++) {
        if (nodes[endindex].like[target] == 1) {
            paths[allpath].indexes[0] = nodes[endindex].number;
            paths[allpath].length++;
            int nextindex = endindex;
            for (int i = nodes[endindex].lastindex; i != -1; i = nodes[i].lastindex) {
                paths[allpath].indexes[paths[allpath].length] = nodes[i].number;
                paths[allpath].distance += matrix[i][nextindex];
                paths[allpath].length++;
                nextindex = i;
            }
            allpath++;
        }
    }

    qsort(paths, allpath, sizeof(struct Path), qsortrule);

    for (int i = 0; i < allpath; i++) {
        if (paths[i].length == 1) {
            printf("%d %d\n", paths[i].indexes[0], paths[i].distance);
        }
        else {
            printf("%d %d ", paths[i].indexes[0], paths[i].distance);
            for (int j = paths[i].length - 1; j >= 0; j--) {
                if (j > 0) {
                    printf("%d-", paths[i].indexes[j]);
                }
                else {
                    printf("%d\n", paths[i].indexes[j]);
                }
            }
        }
    }
    return 0;
}