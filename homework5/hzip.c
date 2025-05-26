#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Huffman {
    char c;
    int weight;
    struct Huffman *leftchild;
    struct Huffman *rightchild;
};

struct Huffman *root = NULL;

int alltext;

int vis[150];

struct Huffman *huffmen[1000];
int allhuffman;

char huffmancodes[150][150];

char nowhuffmancode[150];
int allnowhuffmancode;

char preout[1000];
int allpreout;

void fillHuffmancodes(struct Huffman *now) {
    if (now == NULL) {
        return;
    }
    if (now->leftchild == NULL && now->rightchild == NULL) {
        for (int i = 0; i < allnowhuffmancode; i++) {
            huffmancodes[(int)(now->c)][i] = nowhuffmancode[i];
        }
        return;
    }
    nowhuffmancode[allnowhuffmancode++] = '0';
    fillHuffmancodes(now->leftchild);
    allnowhuffmancode--;
    nowhuffmancode[allnowhuffmancode++] = '1';
    fillHuffmancodes(now->rightchild);
    allnowhuffmancode--;
    return;
}

void toByte(char *s, FILE *out) {
    unsigned char nowout = '\0';
    int count = 0;
    int len = strlen(s);
    for (int i = 0; i < len; i++) {
        if (s[i] == '1') {
            nowout = ((nowout << 1) | 1);
        }
        else if (s[i] == '0') {
            nowout = (nowout << 1);
        }
        count = (count + 1) % 8;
        if (count == 0) {
			// printf("%x", nowout);
			fprintf(out, "%c", nowout);
			nowout = '\0';
		}
	}
	if (count != 0) {
		nowout = (nowout << (8 - count));
		// printf("%x", nowout);
		fprintf(out, "%c", nowout);
	}
}

int qsortrule(const void *P1, const void *P2) {
    struct Huffman **p1 = (struct Huffman **)P1;
    struct Huffman **p2 = (struct Huffman **)P2;
    if ((*p1)->weight > (*p2)->weight) {
        return -1;
    }
    else if ((*p1)->weight < (*p2)->weight) {
        return 1;
    }
    else if ((*p1)->c > (*p2)->c) {
        return -1;
    }
    else if ((*p1)->c < (*p2)->c) {
        return 1;
    }
    else {
        return 0;
    }
}

void hzip(char *name) {
    char nameWithtxt[100] = {'\0'};
    strcpy(nameWithtxt, name);
    strcat(nameWithtxt, ".txt");
    // FILE *in = fopen("C:\\Users\\24502\\Desktop\\Projects\\DS2025\\homework5\\myfile.txt", "r");
    FILE *in = fopen(nameWithtxt, "r");
    char nameWithhzip[100] = {'\0'};
    strcpy(nameWithhzip, name);
    strcat(nameWithhzip, ".hzip");
    // FILE *out = fopen("C:\\Users\\24502\\Desktop\\Projects\\DS2025\\homework5\\myfile.hzip", "w");
    FILE *out = fopen(nameWithhzip, "w");
    char c;
    while (fscanf(in, "%c", &c) != EOF) {
        vis[(unsigned int)c]++;
    }
    vis[0] = 1;
    for (int i = 0; i < 128; i++) {
        if (vis[i] > 0) {
            struct Huffman *p = (struct Huffman *)malloc(sizeof(struct Huffman));
            p->c = i;
            p->weight = vis[i];
            p->leftchild = NULL;
            p->rightchild = NULL;
            huffmen[allhuffman++] = p;
        }
    }
    qsort(huffmen, allhuffman, sizeof(struct Huffman *), qsortrule);
    int allhuffman_save = allhuffman;
    while (allhuffman > 1) {
        struct Huffman *p = (struct Huffman *)malloc(sizeof(struct Huffman));
        p->c = '\0';
        p->leftchild = huffmen[allhuffman - 1];
        p->rightchild = huffmen[allhuffman - 2];
        p->weight = p->leftchild->weight + p->rightchild->weight;
        allhuffman -= 2;
        huffmen[allhuffman++] = p;
        for (int i = allhuffman - 1; i > 0; i--) {
            if (huffmen[i]->weight >= huffmen[i - 1]->weight) {
                struct Huffman *temp = huffmen[i];
                huffmen[i] = huffmen[i - 1];
                huffmen[i - 1] = temp;
            }
            else {
                break;
            }
        }
    }
    root = huffmen[0];
    fillHuffmancodes(root);
    fprintf(out, "%c", (unsigned char)allhuffman_save);
    for (int i = 0; i < 128; i++) {
        if (vis[i] > 0) {
            fprintf(out, "%c", (unsigned char)i);
            fprintf(out, "%c", (unsigned char)strlen(huffmancodes[i]));
            toByte(huffmancodes[i], out);
        }
    }
    rewind(in);
    while (fscanf(in, "%c", &c) != EOF) {
        int len = strlen(huffmancodes[(int)c]);
        for (int j = 0; j < len; j++) {
            preout[allpreout++] = huffmancodes[(int)c][j];
            if (allpreout == 512) {
                toByte(preout, out);
                for (int k = 0; k < allpreout; k++) {
                    preout[k] = '\0';
                }
                allpreout = 0;
            }
        }
    }
    int len = strlen(huffmancodes[0]);
    for (int i = 0; i < len; i++) {
        preout[allpreout++] = huffmancodes[0][i];
    }
    toByte(preout, out);
    fclose(in);
    fclose(out);
}

void uhzip(char *name) {
    char nameWithhzip[100] = {'\0'};
    strcpy(nameWithhzip, name);
    strcat(nameWithhzip, ".hzip");
    // FILE *in = fopen("C:\\Users\\24502\\Desktop\\Projects\\DS2025\\homework5\\myfile.hzip", "r");
    FILE *in = fopen(nameWithhzip, "r");
    char nameWithtxt[100] = {'\0'};
    strcpy(nameWithtxt, name);
    strcat(nameWithtxt, ".txt");
    // FILE *out = fopen("C:\\Users\\24502\\Desktop\\Projects\\DS2025\\homework5\\myfile.txt", "w");
    FILE *out = fopen(nameWithtxt, "w");
    char c;
    fscanf(in, "%c", &c);
    allhuffman = (int)(unsigned char)c;
    for (int i = 0; i < allhuffman; i++) {
        fscanf(in, "%c", &c);
        char c_save = c;
        fscanf(in, "%c", &c);
        int huffmancodelen = (int)(unsigned char)c;
        for (int j = 0; j < huffmancodelen; j++) {
            if (j % 8 == 0) {
                fscanf(in, "%c", &c);
            }
            huffmancodes[(int)(unsigned char)c_save][j] = ((c >> (7 - j % 8)) & 1) + '0';
            vis[(int)(unsigned char)c_save]++;
        }
    }
    root = (struct Huffman *)malloc(sizeof(struct Huffman));
    root->leftchild = NULL;
    root->rightchild = NULL;
    for (int i = 0; i < 128; i++) {
        if (vis[i] > 0) {
            struct Huffman *now = root;
            int huffmancodelen = strlen(huffmancodes[i]);
            for (int j = 0; j < huffmancodelen; j++) {
                if (huffmancodes[i][j] == '0') {
                    if (now->leftchild == NULL) {
                        struct Huffman *p = (struct Huffman *)malloc(sizeof(struct Huffman));
                        p->leftchild = NULL;
                        p->rightchild = NULL;
                        now->leftchild = p;
                        now = now->leftchild;
                    }
                    else {
                        now = now->leftchild;
                    }
                }
                else if (huffmancodes[i][j] == '1') {
                    if (now->rightchild == NULL) {
                        struct Huffman *p = (struct Huffman *)malloc(sizeof(struct Huffman));
                        p->leftchild = NULL;
                        p->rightchild = NULL;
                        now->rightchild = p;
                        now = now->rightchild;
                    }
                    else {
                        now = now->rightchild;
                    }
                }
            }
            now->c = i;
        }
    }
    struct Huffman *now = root;
    int isover = 0;
    while (isover == 0) {
        for (int i = 0; i < 64; i++) {
            if (fscanf(in, "%c", &c) != EOF) {
                for (int j = 0; j < 8; j++) {
                    preout[allpreout++] = ((c >> (7 - j)) & 1) + '0';
                }
            }
            else {
                isover = 1;
            }
        }
        for (int i = 0; i < allpreout; i++) {
            if (preout[i] == '0') {
                now = now->leftchild;
            }
            else if (preout[i] == '1') {
                now = now->rightchild;
            }
            if (now->leftchild == NULL && now->rightchild == NULL) {
                fprintf(out, "%c", now->c);
                now = root;
            }
        }
        allpreout = 0;
    }
    fclose(in);
    fclose(out);
}

char name[100];

int main(int argc, char *argv[]) {
    if (argc == 2) {
        int len = strlen(argv[1]);
        for (int i = 0; i < len && argv[1][i] != '.'; i++) {
            name[i] = argv[1][i];
        }
        hzip(name);
    }
    else if (argc == 3) {
        int len = strlen(argv[2]);
        for (int i = 0; i < len && argv[2][i] != '.'; i++) {
            name[i] = argv[2][i];
        }
        uhzip(name);
    }
    else {
        printf("Usage: hzip.exe [-u] <filename>");
    }
    return 0;
}