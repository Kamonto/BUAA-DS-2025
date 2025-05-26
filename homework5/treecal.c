#include <stdio.h>
#include <stdlib.h>

struct Token {
    int type; // type: 0: num, 1: op
    union {
        int num;
        char op;
    } content;
    struct Token *leftchild;
    struct Token *rightchild;
};

struct Token *tokens[1000]; // postordered
int alltoken;
struct Token *stack[1000];
int stackhead;
struct Token *root;

void makeTree() {
    for (int i = 0; i < alltoken; i++) {
        if (tokens[i]->type == 0) {
            stack[stackhead++] = tokens[i];
        }
        else {
            tokens[i]->leftchild = stack[stackhead - 2];
            tokens[i]->rightchild = stack[stackhead - 1];
            stackhead -= 2;
            stack[stackhead++] = tokens[i];
        }
    }
    if (stackhead > 0) {
        root = stack[stackhead - 1];
    }
}

void printToken(struct Token *token) {
    if (token->type == 0) {
        printf("%d", token->content.num);
    }
    else if (token->type == 1) {
        printf("%c", token->content.op);
    }
}

char str[1000];
int nowwhere;

struct Token *getToken() {
    struct Token *token = (struct Token *)malloc(sizeof(struct Token));
    while (str[nowwhere] == ' ') {
        nowwhere++;
    }
    if (str[nowwhere] >= '0' && str[nowwhere] <= '9') {
        token->type = 0;
        token->content.num = str[nowwhere] - '0';
        nowwhere++;
        while (str[nowwhere] >= '0' && str[nowwhere] <= '9') {
            token->content.num = token->content.num * 10 + str[nowwhere] - '0';
            nowwhere++;
        }
    }
    else {
        token->type = 1;
        token->content.op = str[nowwhere];
        nowwhere++;
    }
    token->leftchild = NULL;
    token->rightchild = NULL;
    // if (token->type == 0) {
    //     printf("new token: %d\n", token->content.num);
    // }
    // else {
    //     printf("new token: %c\n", token->content.op);
    // }
    return token;
}

struct Token *createToken(int type, int num, char op) {
    struct Token *p = (struct Token *)malloc(sizeof (struct Token));
    p->type = type;
    if (type == 0) {
        p->content.num = num;
    }
    else {
        p->content.op = op;
    }
    p->leftchild = NULL;
    p->rightchild = NULL;
    return p;
}

struct Token *curToken;

int parseExpr();
int parseTerm();
int parseFactor();

int parseExpr() {
    int result = parseTerm();
    char op = curToken->content.op;
    while (op == '+' || op == '-') {
        if (op == '+') {
            curToken = getToken();
            result += parseTerm();
            tokens[alltoken++] = createToken(1, 0, '+');
        }
        else if (op == '-') {
            curToken = getToken();
            result -= parseTerm();
            tokens[alltoken++] = createToken(1, 0, '-');
        }
        op = curToken->content.op;
    }
    return result;
}

int parseTerm() {
    int result = parseFactor();
    char op = curToken->content.op;
    while (op == '*' || op == '/') {
        if (op == '*') {
            curToken = getToken();
            result *= parseFactor();
            tokens[alltoken++] = createToken(1, 0, '*');
        }
        else if (op == '/') {
            curToken = getToken();
            result /= parseFactor();
            tokens[alltoken++] = createToken(1, 0, '/');
        }
        op = curToken->content.op;
    }
    return result;
}

int parseFactor() {
    int result;
    if (curToken->type == 0) {
        result = curToken->content.num;
        curToken = getToken();
        tokens[alltoken++] = createToken(0, result, 0);
    }
    else { // curToken->type == 1, curToken->content.op == '('
        curToken = getToken();
        result = parseExpr();
        curToken = getToken(); // skip ')'
    }
    return result;
}

int main() {
    // Recursive-Descent Parsing
    gets(str);
    curToken = getToken();
    int result = parseExpr(str);
    // for (int i = 0; i < alltoken; i++) {
    //     printToken(tokens[i]);
    //     printf(" ");
    // }
    // printf("\n");
    makeTree();
    if (root != NULL) {
        printToken(root);
        if (root->leftchild != NULL) {
            printf(" ");
            printToken(root->leftchild);
        }
        if (root->rightchild != NULL) {
            printf(" ");
            printToken(root->rightchild);
        }
    }
    printf("\n");
    printf("%d", result);
    return 0;
}