#include <stdio.h>
#include <stdlib.h>

struct Mono {
    long long coefficient;
    long long exponent;
};

struct Mono poly1[1000];
int poly1head;
struct Mono poly2[1000];
int poly2head;
struct Mono polyresult[1000];
int polyresulthead;

int qsortrule(const void *P1, const void *P2) {
    struct Mono *p1 = (struct Mono *)P1;
    struct Mono *p2 = (struct Mono *)P2;
    if (p1->exponent > p2->exponent) {
        return -1;
    }
    else if (p1->exponent < p2->exponent) {
        return 1;
    }
    else {
        return 0;
    }
}

int main() {
    char c;
    do {
        scanf("%lld%lld", &poly1[poly1head].coefficient, &poly1[poly1head].exponent);
        poly1head++;
        c = getchar();
    } while (c != '\n');
    do {
        scanf("%lld%lld", &poly2[poly2head].coefficient, &poly2[poly2head].exponent);
        poly2head++;
        c = getchar();
    } while (c != '\n');
    // for (int i = 0; i < poly1head; i++) {
    //     printf("{%lld %lld} ", poly1[i].coefficient, poly1[i].exponent);
    // }
    // printf("\n");
    // for (int i = 0; i < poly2head; i++) {
    //     printf("{%lld %lld} ", poly2[i].coefficient, poly2[i].exponent);
    // }
    // printf("\n");
    for (int i = 0; i < poly1head; i++) {
        for (int j = 0; j < poly2head; j++) {
            struct Mono mono = {poly1[i].coefficient * poly2[j].coefficient, 
                                poly1[i].exponent + poly2[j].exponent};
            int flag = 0;
            for (int k = 0; k < polyresulthead; k++) {
                if (polyresult[k].exponent == mono.exponent) {
                    polyresult[k].coefficient += mono.coefficient;
                    flag = 1;
                    break;
                }
            }
            if (flag == 0) {
                polyresult[polyresulthead++] = mono;
            }
        }
    }
    qsort(polyresult, polyresulthead, sizeof(struct Mono), qsortrule);
    for (int i = 0; i < polyresulthead; i++) {
        if (polyresult[i].coefficient != 0) {
            printf("%lld %lld ", polyresult[i].coefficient, polyresult[i].exponent);
        }
    }
    return 0;
}