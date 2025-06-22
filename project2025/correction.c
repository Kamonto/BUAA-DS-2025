#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAXHASH 999983
#define INF 114514
#define MAX_WORD_LEN 100
#define MAX_WORD_NUM 2000
#define BUFFER_SIZE 4096

int **Dp, MaxDP=3300;								//for dynamic programming

int min3(int a, int b, int c) {
    int min = a < b ? a : b;
    return min < c ? min : c;
}

int initDP() {		
    int i;
    Dp = (int **)malloc(MaxDP*sizeof(int *));
    for(i=0; i<MaxDP; i++)
    Dp[i] = (int *)malloc(MaxDP*sizeof(int));
	return 0;	
}

int editdistDP(char *str1, char *str2, int maxAllowedDistance) {
    int i,j;
    int len1, len2;
    static int flag=0;
	
    (flag++) ? 1 : initDP(); 
    len1 = strlen(str1)+1; len2 = strlen(str2)+1;
    int delta = (len1 > len2) ? (len1 - len2) : (len2 - len1);
    if (delta > maxAllowedDistance) {
        return delta;
    }
    if (len1 >= MaxDP || len2 >= MaxDP) {
        fprintf(stderr,"DP memory error!\n"); 
        exit(-1); 
    }
    for (i = 0; i <= len1; i++) {
        Dp[i][0] = i;
    }
    for (j = 0; j <= len2; j++) {
        Dp[0][j] = j;
    }
    for (i = 1; i <= len1; i++) {
        int begin = (1 > i - maxAllowedDistance) ? 1 : i - maxAllowedDistance;
        int end = (len2 < i + maxAllowedDistance) ? len2 : i + maxAllowedDistance;
        for (j = begin; j <= end; j++) {
            if (str1[i - 1] == str2[j - 1]){
                Dp[i][j] = Dp[i - 1][j - 1];
            }
            else {
                int replaceDp = Dp[i - 1][j - 1];
                int insertDp = (j > begin) ? Dp[i][j - 1] : INF;
                int deleteDp = (j < end) ? Dp[i - 1][j] : INF;
                Dp[i][j] = 1 + min3(replaceDp, insertDp, deleteDp);
            }
        }
    }
    return Dp[len1][len2];
}

struct Bird {
    char bird[MAX_WORD_LEN];
    int hashCode;
    struct NextBird *nextBird;
    struct Bird *nextHash;
};

struct Bird *hashMap[1000000];

struct NextBird {
    struct Bird *birdP;
    struct NextBird *next;
};

int hashCode(char *bird) {
    int res = 0;
    for (int i = 0; bird[i] != '\0'; i++) {
        res = (res * 26 + bird[i] - 'a') % MAXHASH;
    }
    return res;
}

void insertHashMap(struct Bird *p, int hash) {
    if (hashMap[hash] == NULL) {
        hashMap[hash] = p;
    }
    else {
        struct Bird *tail = hashMap[hash];
        while (tail->nextHash != NULL) {
            tail = tail->nextHash;
        }
        tail->nextHash = p;
    }
}

struct Bird *checkBird(char *bird, int hash) {
    for (struct Bird *p = hashMap[hash]; p != NULL; p = p->nextHash) {
        if (!strcmp(p->bird, bird)) {
            return p;
        }
    }
    return NULL;
}

char nowBird[MAX_WORD_LEN];
int allNowBird;

char wrongBird[MAX_WORD_NUM][MAX_WORD_LEN];
struct Bird *wrongLastBirdP[MAX_WORD_NUM];
int allWrongBird;

struct Bird *nowBirdP = NULL;
struct Bird *lastBirdP = NULL;

void dealBirdWhenRight() {
    struct NextBird *p = (struct NextBird *)malloc(sizeof(struct NextBird));
    p->birdP = nowBirdP;
    p->next = NULL;
    if (lastBirdP->nextBird == NULL) {
        lastBirdP->nextBird = p;
        return;
    }
    struct NextBird *tail = lastBirdP->nextBird;
    while (1) {
        if (tail->birdP == nowBirdP) {
            return;
        }
        if (tail->next == NULL) {
            break;
        }
        tail = tail->next;
    }
    tail->next = p;
}

void dealBirdWhenWrong() {
    for (int i = 0; i < allWrongBird; i++) {
        if (wrongLastBirdP[i] == lastBirdP && !strcmp(wrongBird[i], nowBird)) {
            return;
        }
    }
    strcpy(wrongBird[allWrongBird], nowBird);
    wrongLastBirdP[allWrongBird] = lastBirdP;
    allWrongBird++;
}

void dealBird() {
    if (allNowBird > 0) {
        nowBird[allNowBird] = '\0';
        int hash = hashCode(nowBird);
        nowBirdP = checkBird(nowBird, hash);
        if (lastBirdP != NULL) {
            if (nowBirdP != NULL) {
                dealBirdWhenRight();
            }
            else {
                dealBirdWhenWrong();
            }
        }
        allNowBird = 0;
        lastBirdP = nowBirdP;
    }
}

int qsortrule(const void *P1, const void *P2) {
    struct Bird **p1 = (struct Bird **)P1;
    struct Bird **p2 = (struct Bird **)P2;
    if (strcmp((*p1)->bird, (*p2)->bird) < 0) {
        return -1;
    }
    else {
        return 1;
    }
}

int main() {
    // FILE *dict = fopen("C:\\Users\\24502\\Desktop\\Projects\\DS2025\\project2025\\dict.txt", "r");
    FILE *dict = fopen("dict.txt", "r");
    // FILE *in = fopen("C:\\Users\\24502\\Desktop\\Projects\\DS2025\\project2025\\in.txt", "r");
    FILE *in = fopen("in.txt", "r");
    // FILE *in = stdin;
    // freopen("C:\\Users\\24502\\Desktop\\Projects\\DS2025\\project2025\\out.txt", "w", stdout);

    struct Bird *p = (struct Bird *)malloc(sizeof(struct Bird));
    while (fscanf(dict, "%s", p->bird) != EOF) {
        int hash = hashCode(p->bird);
        p->hashCode = hash;
        p->nextBird = NULL;
        p->nextHash = NULL;
        insertHashMap(p, hash);
        p = (struct Bird *)malloc(sizeof(struct Bird));
    }

    char c;
    char buffer[BUFFER_SIZE];
    size_t allbuffer;
    while ((allbuffer = fread(buffer, sizeof(char), BUFFER_SIZE, in)) > 0) {
        for (size_t i = 0; i < allbuffer; i++) {
            c = buffer[i];
            if (isalpha(c)) {
                nowBird[allNowBird++] = tolower(c);
            }
            else {
                dealBird();
                if (c != ' ' && c != '\t') {
                    lastBirdP = NULL;
                }
            }
        }
    }
    dealBird();
    
    for (int i = 0; i < allWrongBird; i++) {
        struct Bird *lastP = wrongLastBirdP[i];
        if (lastP->nextBird == NULL) {
            printf("%s: %s -> No suggestion\n", lastP->bird, wrongBird[i]);
            continue;
        }
        int minDistance = INF;
        struct Bird *whereMinDistance[1000] = {NULL};
        int allMinDistance = 0;
        for (struct NextBird *p = lastP->nextBird; p != NULL; p = p->next) {
            int dp = editdistDP(p->birdP->bird, wrongBird[i], minDistance);
            if (dp < minDistance) {
                minDistance = dp;
                allMinDistance = 0;
                whereMinDistance[allMinDistance++] = p->birdP;
            }
            else if (dp == minDistance) {
                whereMinDistance[allMinDistance++] = p->birdP;
            }
        }
        qsort(whereMinDistance, allMinDistance, sizeof(struct Bird *), qsortrule);
        printf("%s: %s -> %s", lastP->bird, wrongBird[i], whereMinDistance[0]->bird);
        for (int j = 1; j < allMinDistance; j++) {
            printf(",%s", whereMinDistance[j]->bird);
        }
        printf("\n");
    }

    fclose(dict);
    fclose(in);
    return 0;
}
