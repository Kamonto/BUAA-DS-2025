//�ļ�ѹ��-Huffmanʵ��
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXSIZE 32

struct tnode {					//Huffman���ṹ
	char c;		
	int weight;					//���ڵ�Ȩ�أ�Ҷ�ڵ�Ϊ�ַ������ĳ��ִ���
	struct tnode *left,*right;
} ; 
int Ccount[128]={0};			//���ÿ���ַ��ĳ��ִ�������Ccount[i]��ʾASCIIֵΪi���ַ����ִ��� 
struct tnode *Root=NULL; 		//Huffman���ĸ��ڵ�
char HCode[128][MAXSIZE]={{0}}; //�ַ���Huffman���룬��HCode['a']Ϊ�ַ�a��Huffman���루�ַ�����ʽ�� 
int Step=0;						//ʵ�鲽�� 
FILE *Src, *Obj;
	
void statCount();				//����1��ͳ���ļ����ַ�Ƶ��
void createHTree();				//����2������һ��Huffman�������ڵ�ΪRoot 
void makeHCode();				//����3������Huffman������Huffman����
void atoHZIP(); 				//����4������Huffman���뽫ָ��ASCII���ı��ļ�ת����Huffman���ļ�

void print1();					//�������1�Ľ��
void print2(struct tnode *p);	//�������2�Ľ�� 
void print3();					//�������3�Ľ��
void print4();					//�������4�Ľ��

int main()
{
	// if((Src=fopen("C:\\Users\\24502\\Desktop\\Projects\\DS2025\\homework5\\input.txt","r"))==NULL) {
	if((Src=fopen("input.txt","r"))==NULL) {
		fprintf(stderr, "%s open failed!\n", "input.txt");
		return 1;
	}
	// if((Obj=fopen("C:\\Users\\24502\\Desktop\\Projects\\DS2025\\homework5\\output.txt","w"))==NULL) {
	if((Obj=fopen("output.txt","w"))==NULL) {
		fprintf(stderr, "%s open failed!\n", "output.txt");
		return 1;
	}
	scanf("%d",&Step);					//���뵱ǰʵ�鲽�� 
	
	statCount();						//ʵ�鲽��1��ͳ���ļ����ַ����ִ�����Ƶ�ʣ�
	if(Step==1) 
		print1(); 			//���ʵ�鲽��1���	
	createHTree();						//ʵ�鲽��2�������ַ�Ƶ��������Ӧ��Huffman��
	if(Step==2) 
		print2(Root); 		//���ʵ�鲽��2���	
	makeHCode();				   		//ʵ�鲽��3������RootΪ���ĸ���Huffman��������ӦHuffman����
	if(Step==3) 
		print3(); 			//���ʵ�鲽��3���
	if(Step>=4) 
		atoHZIP(),print4(); 	//ʵ�鲽��4����Huffman��������ѹ���ļ��������ʵ�鲽��4���	

	fclose(Src);
	fclose(Obj);

    return 0;
} 

//��ʵ�鲽��1����ʼ 

char text[1000];
int alltext;

void statCount()
{
	char c;
	while (fscanf(Src, "%c", &c) != EOF) {
		if (c != '\n') {
			text[alltext++] = c;
			Ccount[(int)c] += 1;
		}
	}
	Ccount[0] = 1;
}

//��ʵ�鲽��1������

//��ʵ�鲽��2����ʼ

struct tnode *tnodes[1000];
int alltnode;

void createHTree()
{
	for (int i = 0; i < 128; i++) {
		if (Ccount[i] > 0) {
			struct tnode *p = (struct tnode *)malloc(sizeof(struct tnode));
			p->c = (char)i;
			p->weight = Ccount[i];
			p->left = NULL;
			p->right = NULL;
			tnodes[alltnode++] = p;
		}
	}
	for (int i = 1; i < alltnode; i++) {
		for (int j = 0; j < alltnode - i; j++) {
			if (tnodes[j]->weight < tnodes[j + 1]->weight || 
				(tnodes[j]->weight == tnodes[j + 1]->weight && tnodes[j]->c < tnodes[j + 1]->c)) {
				struct tnode *temp = tnodes[j];
				tnodes[j] = tnodes[j + 1];
				tnodes[j + 1] = temp;
			}
		}
	}
	while (alltnode > 1) {
		struct tnode *p = (struct tnode *)malloc(sizeof(struct tnode));
		p->c = '\0';
		p->left = tnodes[alltnode - 1];
		p->right = tnodes[alltnode - 2];
		p->weight = p->left->weight + p->right->weight;
		alltnode -= 2;
		tnodes[alltnode++] = p;
		for (int i = alltnode - 1; i > 0; i--) {
			if (tnodes[i]->weight >= tnodes[i - 1]->weight) {
				struct tnode *temp = tnodes[i];
				tnodes[i] = tnodes[i - 1];
				tnodes[i - 1] = temp;
			}
			else {
				break;
			}
		}
	}
	Root = tnodes[0];
}

//��ʵ�鲽��2������

//��ʵ�鲽��3����ʼ

char nowHCode[1000];
int allnowHCode;

void make(struct tnode *now) {
	if (now == NULL) {
		return;
	}
	if (now->left == NULL && now->right == NULL) {
		for (int i = 0; i < allnowHCode; i++) {
			HCode[(int)(now->c)][i] = nowHCode[i];
		}
		return;
	}
	nowHCode[allnowHCode++] = '0';
	make(now->left);
	allnowHCode--;
	nowHCode[allnowHCode++] = '1';
	make(now->right);
	allnowHCode--;
	return;
}

void makeHCode()
{
	make(Root);
} 

//��ʵ�鲽��3������

//��ʵ�鲽��4����ʼ

char preout[10000];
int allpreout;

void atoHZIP()
{
	for (int i = 0; i < alltext; i++) {
		char c = text[i];
		int HCodelen = strlen(HCode[(int)c]);
		for (int j = 0; j < HCodelen; j++) {
			preout[allpreout++] = HCode[(int)c][j];
		}
	}
	int HCodelen = strlen(HCode[0]);
	for (int i = 0; i < HCodelen; i++) {
		preout[allpreout++] = HCode[0][i];
	}
	unsigned char nowout = '\0';
	int count = 0;
	for (int i = 0; i < allpreout; i++) {
		if (preout[i] == '1') {
			nowout = ((nowout << 1) | 1);
		}
		else {
			nowout = (nowout << 1);
		}
		count = (count + 1) % 8;
		if (count == 0) {
			printf("%x", nowout);
			fprintf(Obj, "%c", nowout);
			nowout = '\0';
		}
	}
	if (count != 0) {
		nowout = (nowout << (8 - count));
		printf("%x", nowout);
		fprintf(Obj, "%c", nowout);
	}
}

//��ʵ�鲽��4������

void print1()
{
	int i;
	printf("NUL:1\n");
	for(i=1; i<128; i++)
		if(Ccount[i] > 0)
			printf("%c:%d\n", i, Ccount[i]);
}

void print2(struct tnode *p)
{
	if(p != NULL){
		if((p->left==NULL)&&(p->right==NULL)) 
			switch(p->c){
				case 0: printf("NUL ");break;
				case ' ':  printf("SP ");break;
				case '\t': printf("TAB ");break;
				case '\n':  printf("CR ");break;
				default: printf("%c ",p->c); break;
			}
		print2(p->left);
		print2(p->right);
	}
}

void print3()
{
	int i;
	
	for(i=0; i<128; i++){
		if(HCode[i][0] != 0){
			switch(i){
				case 0: printf("NUL:");break;
				case ' ':  printf("SP:");break;
				case '\t': printf("TAB:");break;
				case '\n':  printf("CR:");break;
				default: printf("%c:",i); break;
			}
			printf("%s\n",HCode[i]);
		}
	}
} 

void print4()
{
	long int in_size, out_size;
	
	fseek(Src,0,SEEK_END);
	fseek(Obj,0,SEEK_END);
	in_size = ftell(Src);
	out_size = ftell(Obj);
	
	printf("\nԭ�ļ���С��%ldB\n",in_size);
	printf("ѹ�����ļ���С��%ldB\n",out_size);
	printf("ѹ���ʣ�%.2f%%\n",(float)(in_size-out_size)*100/in_size);
}
