#include <stdio.h>

int vis[15];
int arr[15];

void arrange(int num, int rest) {
    if (rest == 0) {
        for (int i = 0; i < num; i++) {
            printf("%d ", arr[i]);
        }
        printf("\n");
        return ;
    }
    for (int i = 1; i <= num; i++) {
        if (vis[i] == 0) {
            arr[num - rest] = i;
            vis[i] = 1;
            arrange(num, rest - 1);
            vis[i] = 0;
        }
    }
}

int main() {
    int num;
    scanf("%d", &num);
    arrange(num, num);
    return 0;
}