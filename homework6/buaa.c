#include <stdio.h>
#include <stdlib.h>

int allnode;

struct Edge {
    int id;
    int beginnode;
    int endnode;
    int weight;
};

struct Edge edges[1000];
int alledge;

struct Edge res[1000];
int allres;
int allweight;

int disjointSet[100];

void disjointSetInit() {
    for (int i = 0; i < allnode; i++) {
        disjointSet[i] = i;
    }
}

int disjointSetFind(int node) {
    if (disjointSet[node] == node) {
        return node;
    }
    else {
        return disjointSet[node] = disjointSetFind(disjointSet[node]);
    }
}

void disjointSetUnion(int root1, int root2) {
    disjointSet[root1] = root2;
}

int qsortrule_weight(const void *P1, const void *P2) {
    struct Edge *p1 = (struct Edge *)P1;
    struct Edge *p2 = (struct Edge *)P2;
    if (p1->weight < p2->weight) {
        return -1;
    }
    else if (p1->weight > p2->weight) {
        return 1;
    }
    else {
        return 0;
    }
}

int qsortrule_id(const void *P1, const void *P2) {
    struct Edge *p1 = (struct Edge *)P1;
    struct Edge *p2 = (struct Edge *)P2;
    if (p1->id < p2->id) {
        return -1;
    }
    else if (p1->id > p2->id) {
        return 1;
    }
    else {
        return 0;
    }
}

int main() {
    scanf("%d%d", &allnode, &alledge);
    disjointSetInit();
    for (int i = 0 ; i < alledge; i++) {
        scanf("%d%d%d%d", &edges[i].id, &edges[i].beginnode, &edges[i].endnode, &edges[i].weight);
    }
    qsort(edges, alledge, sizeof(struct Edge), qsortrule_weight);
    for (int i = 0; i < alledge && allres < allnode - 1; i++) {
        int beginroot = disjointSetFind(edges[i].beginnode);
        int endroot = disjointSetFind(edges[i].endnode);
        if (beginroot != endroot) {
            res[allres++] = edges[i];
            allweight += edges[i].weight;
            disjointSetUnion(beginroot, endroot);
        }
    }
    qsort(res, allres, sizeof(struct Edge), qsortrule_id);
    printf("%d\n", allweight);
    for (int i = 0; i < allres; i++) {
        printf("%d ", res[i].id);
    }
    return 0;
}