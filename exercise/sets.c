#include <stdio.h>

int sets[1000];
int vis[100000];
int head = 1;

int main() {
    int n;
    scanf("%d", &n);
    while (n != -1) {
        vis[n] = head;
        sets[head++] = n;
        scanf("%d", &n);
    }
    scanf("%d", &n);
    while (n != -1) {
        sets[vis[n]] = -1;
        scanf("%d", &n);
    }
    for (int i = 1; i < head; i++) {
        if (sets[i] != -1) {
            printf("%d ", sets[i]);
        }
    }
    return 0;
}