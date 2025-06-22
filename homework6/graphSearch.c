#include <stdio.h>

int allnode, alledge;

int matrix[105][105];

int vis[105];
int res[105];
int allres;

void clearall() {
    for (int i = 0; i < allnode; i++) {
        vis[i] = 0;
        res[i] = 0;
    }
    allres = 0;
}

void printres() {
    for (int i = 0; i < allres; i++) {
        printf("%d ", res[i]);
    }
    printf("\n");
}

void dfs(int beginnode) {
    vis[beginnode] = 1;
    res[allres++] = beginnode;
    for (int i = 0; i < allnode; i++) {
        if (matrix[beginnode][i] == 1 && vis[i] == 0) {
            dfs(i);
        }
    }
}

void bfs(int beginnode) {
    vis[beginnode] = 1;
    res[0] = beginnode;
    int head = 0, tail = 1;
    while (head < tail) {
        for (int i = 0; i < allnode; i++) {
            if (matrix[res[head]][i] == 1 && vis[i] == 0) {
                vis[i] = 1;
                res[tail++] = i;
            }
        }
        head++;
    }
    allres = tail;
}

int main() {
    scanf("%d%d", &allnode, &alledge);
    for (int i = 0; i < alledge; i++) {
        int beginnode, endnode;
        scanf("%d%d", &beginnode, &endnode);
        matrix[beginnode][endnode] = 1;
        matrix[endnode][beginnode] = 1;
    }
    int deletenode;
    scanf("%d", &deletenode);
    // for (int i = 0; i < allnode; i++) {
    //     for (int j = 0; j < allnode; j++) {
    //         printf("%d ", matrix[i][j]);
    //     }
    //     printf("\n");
    // }
    clearall();
    dfs(0);
    printres();
    clearall();
    bfs(0);
    printres();
    for (int i = 0; i < alledge; i++) {
        matrix[deletenode][i] = 0;
        matrix[i][deletenode] = 0;
    }
    clearall();
    dfs(0);
    printres();
    clearall();
    bfs(0);
    printres();
    return 0;
}