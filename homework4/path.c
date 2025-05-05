#include <stdio.h>

struct Path {
    int toward;
    int distance;
};

struct Path stack[1005];
int stackhead;

int reverse(int n) {
    return (n == 1) ? 2 : (n == 2) ? 1 : (n == 3) ? 4 : (n == 4) ? 3 : 0;
}

int main() {
    struct Path path;
    scanf("%d-%d", &path.toward, &path.distance);
    while (path.toward) {
        if (stackhead > 0) {
            if (stack[stackhead - 1].toward == path.toward) {
                stack[stackhead - 1].distance += path.distance;
            }
            else if (stack[stackhead - 1].toward == reverse(path.toward)) {
                if (stack[stackhead - 1].distance < path.distance) {
                    stack[stackhead - 1].toward = path.toward;
                    stack[stackhead - 1].distance = path.distance - stack[stackhead - 1].distance;
                }
                else if (stack[stackhead - 1].distance > path.distance) {
                    stack[stackhead - 1].distance -= path.distance;
                }
                else {
                    stackhead--;
                }
            }
            else {
                stack[stackhead++] = path;
            }
        }
        else {
            stack[stackhead++] = path;
        }
        scanf("%d-%d", &path.toward, &path.distance);
    }
    for (int i = stackhead - 1; i >= 0; i--) {
        printf("%d-%d ", reverse(stack[i].toward), stack[i].distance);
    }
    return 0;
}