#include <stdio.h>

struct Token {
    int type; // type: 0: num, 1: op
    union {
        int num;
        char op;
    } content;
};

char str[1000];
int nowwhere;

struct Token getToken() {
    struct Token token;
    while (str[nowwhere] == ' ') {
        nowwhere++;
    }
    if (str[nowwhere] >= '0' && str[nowwhere] <= '9') {
        token.type = 0;
        token.content.num = str[nowwhere] - '0';
        nowwhere++;
        while (str[nowwhere] >= '0' && str[nowwhere] <= '9') {
            token.content.num = token.content.num * 10 + str[nowwhere] - '0';
            nowwhere++;
        }
    }
    else {
        token.type = 1;
        token.content.op = str[nowwhere];
        nowwhere++;
    }
    // if (token.type == 0) {
    //     printf("new token: %d\n", token.content.num);
    // }
    // else {
    //     printf("new token: %c\n", token.content.op);
    // }
    return token;
}

struct Token curToken;

double parseExpr();
double parseTerm();
double parseFactor();

double parseExpr() {
    double result = parseTerm();
    char op = curToken.content.op;
    while (op == '+' || op == '-') {
        if (op == '+') {
            curToken = getToken();
            result += parseTerm();
        }
        else if (op == '-') {
            curToken = getToken();
            result -= parseTerm();
        }
        op = curToken.content.op;
    }
    return result;
}

double parseTerm() {
    double result = parseFactor();
    char op = curToken.content.op;
    while (op == '*' || op == '/') {
        if (op == '*') {
            curToken = getToken();
            result *= parseFactor();
        }
        else if (op == '/') {
            curToken = getToken();
            result /= parseFactor();
        }
        op = curToken.content.op;
    }
    return result;
}

double parseFactor() {
    double result;
    if (curToken.type == 0) {
        result = (double)curToken.content.num;
        curToken = getToken();
    }
    else { // curToken.type == 1, curToken.content.op == '('
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
    printf("%.2f", parseExpr(str));
    return 0;
}