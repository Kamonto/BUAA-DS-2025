#include <stdio.h>

int sum[1005];

int main() {
    for (int i = 1; i <= 1000; i++) {
        sum[i] = sum[i - 1] + i;
    }
    int n;
    scanf("%d", &n);
    for (int i = 2; i <= n / 2 + 1; i++) {
        for (int j = 0; j < i - 1; j++) {
            if (sum[i] - sum[j] == n) {
                printf("%d=%d", n, j + 1);
                for (int k = j + 2; k <= i; k++) {
                    printf("+%d", k);
                }
                return 0;
            }
            else if (sum[i] - sum[j] < n) {
                continue;
            }
        }
    }
    printf("No Answer");
    return 0;
}