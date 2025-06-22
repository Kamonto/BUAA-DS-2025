#include <stdio.h>

int numbers[105];
int allnumber;

int selectionSort() {
    int times = 0;
    for (int i = 0; i < allnumber - 1; i++) {
        int min = numbers[i];
        int wheremin = i;
        for (int j = i + 1; j < allnumber; j++) {
            if (numbers[j] < min) {
                min = numbers[j];
                wheremin = j;
            }
            times++;
        }
        for (int j = wheremin; j > i; j--) {
            numbers[j] = numbers[j - 1];
        }
        numbers[i] = min;
    }
    return times;
}

int bubbleSort() {
    int times = 0;
    for (int i = 0; i < allnumber - 1; i++) {
        int swapflag = 0;
        for (int j = 0; j < allnumber - i - 1; j++) {
            if (numbers[j] > numbers[j + 1]) {
                int temp = numbers[j];
                numbers[j] = numbers[j + 1];
                numbers[j + 1] = temp;
                swapflag = 1;
            }
            times++;
        }
        if (swapflag == 0) {
            break;
        }
    }
    return times;
}

int heapSort() {
    int times = 0;
    for (int i = allnumber / 2 - 1; i >= 0; i--) {
        int j = i;
        while (2 * j + 1 < allnumber) {
            int max = numbers[2 * j + 1];
            int wheremax = 2 * j + 1;
            if (2 * j + 2 < allnumber && numbers[2 * j + 1] < numbers[2 * j + 2]) {
                max = numbers[2 * j + 2];
                wheremax = 2 * j + 2;
            }
            times++;
            if (numbers[j] < max) {
                numbers[wheremax] = numbers[j];
                numbers[j] = max;
                j = wheremax;
            }
            else {
                break;
            }
        }
    }
    for (int i = 0; i < allnumber - 1; i++) {
        int temp = numbers[allnumber - i - 1];
        numbers[allnumber - i - 1] = numbers[0];
        numbers[0] = temp;
        int j = 0;
        while (2 * j + 1 < allnumber - i - 1) {
            int max = numbers[2 * j + 1];
            int wheremax = 2 * j + 1;
            if (2 * j + 2 < allnumber - i - 1 && numbers[2 * j + 1] < numbers[2 * j + 2]) {
                max = numbers[2 * j + 2];
                wheremax = 2 * j + 2;
            }
            times++;
            if (numbers[j] < max) {
                numbers[wheremax] = numbers[j];
                numbers[j] = max;
                j = wheremax;
            }
            else {
                break;
            }
        }
    }
    return times;
}

int mergeSort(int left, int right) {
    int times = 0;
    if (left + 1 == right) {
        return times;
    }
    int mid = (left + right - 1) / 2 + 1;
    times += mergeSort(left, mid);
    times += mergeSort(mid, right);
    int temp[105] = {0};
    int i = left, j = mid, alltemp = left;
    while (i < mid && j < right) {
        if (numbers[i] < numbers[j]) {
            temp[alltemp++] = numbers[i++];
        }
        else {
            temp[alltemp++] = numbers[j++];
        }
        times++;
    }
    while (i < mid) {
        temp[alltemp++] = numbers[i++];
    }
    while (j < right) {
        temp[alltemp++] = numbers[j++];
    }
    for (int k = left; k < alltemp; k++) {
        numbers[k] = temp[k];
    }
    return times;
}

int quickSort(int left, int right) {
    int times = 0;
    if (left + 1 >= right) {
        return times;
    }
    int last = left;
    for (int i = left + 1; i < right; i++) {
        if (numbers[i] < numbers[left]) {
            last++;
            int temp = numbers[i];
            numbers[i] = numbers[last];
            numbers[last] = temp;
        }
        times++;
    }
    int temp = numbers[left];
    numbers[left] = numbers[last];
    numbers[last] = temp;
    times += quickSort(left, last);
    times += quickSort(last + 1, right);
    return times;
}

int main() {
    int op, times = 0;
    scanf("%d%d", &allnumber, &op);
    for (int i = 0; i < allnumber; i++) {
        scanf("%d", &numbers[i]);
    }
    if (op == 1) {
        times = selectionSort();
    }
    else if (op == 2) {
        times = bubbleSort();
    }
    else if (op == 3) {
        times = heapSort();
    }
    else if (op == 4) {
        times = mergeSort(0, allnumber);
    }
    else if (op == 5) {
        times = quickSort(0, allnumber);
    }
    for (int i = 0; i < allnumber; i++) {
        printf("%d ", numbers[i]);
    }
    printf("\n%d", times);
    return 0;
}