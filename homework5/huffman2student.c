//文件压缩-Huffman实现
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXSIZE 32

struct tnode {					//Huffman树结构
	char c;		
	int weight;					//树节点权重，叶节点为字符和它的出现次数
	struct tnode *left,*right;
} ; 
int Ccount[128]={0};			//存放每个字符的出现次数，如Ccount[i]表示ASCII值为i的字符出现次数 
struct tnode *Root=NULL; 		//Huffman树的根节点
char HCode[128][MAXSIZE]={{0}}; //字符的Huffman编码，如HCode['a']为字符a的Huffman编码（字符串形式） 
int Step=0;						//实验步骤 
FILE *Src, *Obj;
	
void statCount();				//步骤1：统计文件中字符频率
void createHTree();				//步骤2：创建一个Huffman树，根节点为Root 
void makeHCode();				//步骤3：根据Huffman树生成Huffman编码
void atoHZIP(); 				//步骤4：根据Huffman编码将指定ASCII码文本文件转换成Huffman码文件

void print1();					//输出步骤1的结果
void print2(struct tnode *p);	//输出步骤2的结果 
void print3();					//输出步骤3的结果
void print4();					//输出步骤4的结果

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
	scanf("%d",&Step);					//输入当前实验步骤 
	
	statCount();						//实验步骤1：统计文件中字符出现次数（频率）
	if(Step==1) 
		print1(); 			//输出实验步骤1结果	
	createHTree();						//实验步骤2：依据字符频率生成相应的Huffman树
	if(Step==2) 
		print2(Root); 		//输出实验步骤2结果	
	makeHCode();				   		//实验步骤3：依据Root为树的根的Huffman树生成相应Huffman编码
	if(Step==3) 
		print3(); 			//输出实验步骤3结果
	if(Step>=4) 
		atoHZIP(),print4(); 	//实验步骤4：据Huffman编码生成压缩文件，并输出实验步骤4结果	

	fclose(Src);
	fclose(Obj);

    return 0;
} 

//【实验步骤1】开始 

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

//【实验步骤1】结束

//【实验步骤2】开始

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

//【实验步骤2】结束

//【实验步骤3】开始

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

//【实验步骤3】结束

//【实验步骤4】开始

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

//【实验步骤4】结束

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
	
	printf("\n原文件大小：%ldB\n",in_size);
	printf("压缩后文件大小：%ldB\n",out_size);
	printf("压缩率：%.2f%%\n",(float)(in_size-out_size)*100/in_size);
}
