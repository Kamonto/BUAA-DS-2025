#include <stdio.h>
#include <stdlib.h>

struct Edges {
    int alledge;
    int edges[100];
};

struct Edges matrix[100][100];
int vis[100];
int path[1000];
int allpath;

struct Edges res[100];
int allres;

int allnode, alledge;

void dfs(int beginnode, int endnode) {
    if (beginnode == endnode) {
        for (int i = 0; i < allpath; i++) {
            res[allres].edges[i] = path[i];
        }
        res[allres++].alledge = allpath;
        return;
    }
    vis[beginnode] = 1;
    for (int i = 0; i < allnode; i++) {
        if (matrix[beginnode][i].alledge > 0 && vis[i] == 0) {
            for (int j = 0; j < matrix[beginnode][i].alledge; j++) {
                path[allpath++] = matrix[beginnode][i].edges[j];
                dfs(i, endnode);
                allpath--;
            }
        }
    }
    vis[beginnode] = 0;
}

int qsortrule(const void *P1, const void *P2) {
    struct Edges *p1 = (struct Edges *)P1;
    struct Edges *p2 = (struct Edges *)P2;
    int len1 = p1->alledge;
    int len2 = p2->alledge;
    for (int i = 0; i < len1 && i < len2; i++) {
        if (p1->edges[i] < p2->edges[i]) {
            return -1;
        }
        else if (p1->edges[i] > p2->edges[i]) {
            return 1;
        }
    }
    return 0;
}

int main() {
    scanf("%d%d", &allnode, &alledge);
    for (int i = 0; i < alledge; i++) {
        int edge, beginnode, endnode;
        scanf("%d%d%d", &edge, &beginnode, &endnode);
        matrix[beginnode][endnode].edges[matrix[beginnode][endnode].alledge++] = edge;
        matrix[endnode][beginnode].edges[matrix[endnode][beginnode].alledge++] = edge;
    }
    dfs(0, allnode - 1);
    qsort(res, allres, sizeof(struct Edges), qsortrule);
    for (int i = 0; i < allres; i++) {
        for (int j = 0; j < res[i].alledge; j++) {
            printf("%d ", res[i].edges[j]);
        }
        printf("\n");
    }
    return 0;
}