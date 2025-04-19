#include <stdio.h>

int greater(int x, int y) {
    return (x > y) ? x : y;
}

int less(int x, int y) {
    return (x < y) ? x : y;
}

int main() {
    int Ax1, Ay1, Ax2, Ay2, Bx1, By1, Bx2, By2;
    int delta_x, delta_y;
    scanf("%d%d%d%d%d%d%d%d", &Ax1, &Ay1, &Ax2, &Ay2, &Bx1, &By1, &Bx2, &By2);
    delta_x = less(greater(Ax1, Ax2), greater(Bx1, Bx2)) - greater(less(Ax1, Ax2), less(Bx1, Bx2));
    delta_y = less(greater(Ay1, Ay2), greater(By1, By2)) - greater(less(Ay1, Ay2), less(By1, By2));
    if (delta_x > 0 && delta_y > 0) {
        printf("%d", delta_x * delta_y);
    }
    else {
        printf("0");
    }
    return 0;
}