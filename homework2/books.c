#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Book {
    char name[100];
    char author[100];
    char press[100];
    char date[100];
};

struct Book books[510];
int allbook;

int qsortrule(const void *P1, const void *P2) {
    struct Book *p1 = (struct Book *)P1;
    struct Book *p2 = (struct Book *)P2;
    if (strcmp(p1->name, p2->name) < 0) {
        return -1;
    }
    else if (strcmp(p1->name, p2->name) > 0) {
        return 1;
    }
    else {
        return 0;
    }
}

int main() {
    FILE *in, *out;
    // in = fopen("C:\\Users\\24502\\Desktop\\Projects\\DS2025\\homework2\\books.txt", "r");
    // out = fopen("C:\\Users\\24502\\Desktop\\Projects\\DS2025\\homework2\\ordered.txt", "w");
    in = fopen("books.txt", "r");
    out = fopen("ordered.txt", "w");

    char s[100] = {'\0'};
    while(fscanf(in, "%s", books[allbook].name) != EOF) {
        fscanf(in, "%s", books[allbook].author);
        fscanf(in, "%s", books[allbook].press);
        fscanf(in, "%s", books[allbook++].date);
    }
    qsort(books, allbook, sizeof(struct Book), qsortrule);
    int op;
    scanf("%d", &op);
    while (op != 0) {
        if (op == 1) {
            struct Book book;
            scanf("%s", book.name);
            scanf("%s", book.author);
            scanf("%s", book.press);
            scanf("%s", book.date);
            int insert = allbook - 1;
            while (strcmp(books[insert].name, book.name) > 0) {
                books[insert + 1] = books[insert];
                insert--;
            }
            books[insert + 1] = book;
            allbook++;
        }
        else if (op == 2) {
            scanf("%s", s);
            for (int i = 0; i < allbook; i++) {
                if (strstr(books[i].name, s) != NULL) {
                    printf("%-50s%-20s%-30s%-10s\n", books[i].name, books[i].author, books[i].press, books[i].date);
                }
            }
        }
        else if (op == 3) {
            scanf("%s", s);
            for (int i = 0; i < allbook; i++) {
                if (strstr(books[i].name, s) != NULL) {
                    for (int j = i + 1; j < allbook; j++) {
                        books[j - 1] = books[j];
                    }
                    allbook--;
                    i--;
                }
            }
        }
        scanf("%d", &op);
    }
    for (int i = 0; i < allbook; i++) {
        fprintf(out, "%-50s%-20s%-30s%-10s\n", books[i].name, books[i].author, books[i].press, books[i].date);
    }
    return 0;
}