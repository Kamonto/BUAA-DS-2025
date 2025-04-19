#include <stdio.h>
#include <stdlib.h>

struct Line {
    int va_x;
    int va_y;
    int vb_x;
    int vb_y;
};

struct AttachedLine {
    struct Line attachedline;
    int count;
};

struct Line lines[105];
struct AttachedLine attachedlines[105];
int head;

int qsortrule(const void *P1, const void *P2) {
    struct Line *p1 = (struct Line *)P1;
    struct Line *p2 = (struct Line *)P2;
    if (p1->va_x < p2->va_x) {
        return -1;
    }
    else if (p1->va_x > p2->va_x) {
        return 1;
    }
    else {
        return 0;
    }
}

int main() {
    int allline;
    scanf("%d", &allline);
    for (int i = 0; i < allline; i++) {
        scanf("%d%d%d%d", &lines[i].va_x, &lines[i].va_y, &lines[i].vb_x, &lines[i].vb_y);
    }
    qsort(lines, allline, sizeof(struct Line), qsortrule);
    for (int i = 0; i < allline; i++) {
        int flag = 0;
        for (int j = 0; j < head; j++) {
            if (attachedlines[j].attachedline.vb_x == lines[i].va_x && 
                attachedlines[j].attachedline.vb_y == lines[i].va_y) {
                attachedlines[j].attachedline.vb_x = lines[i].vb_x;
                attachedlines[j].attachedline.vb_y = lines[i].vb_y;
                attachedlines[j].count++;
                flag = 1;
                break;
            }
        }
        if (flag == 0) {
            struct AttachedLine attachedline = {lines[i], 1};
            attachedlines[head++] = attachedline;
        }
    }
    int maxcount = 0, wheremaxcount = -1;
    for (int j = 0; j < head; j++) {
        if (attachedlines[j].count > maxcount) {
            wheremaxcount = j;
            maxcount = attachedlines[j].count;
        }
    }
    printf("%d %d %d", maxcount, attachedlines[wheremaxcount].attachedline.va_x, 
        attachedlines[wheremaxcount].attachedline.va_y);
    return 0;
}