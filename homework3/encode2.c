#include <stdio.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
char original_key[50];
typedef struct Block{
	char ori;
	char to;
	struct Block *next;
}Block;
int a[200];

Block* find_pre(Block* target,Block* start)
{
	Block* current=start;
	while(current->next!=target)
	{
		current=current->next;
	}
	return current;
}

char *quchong(char miyao[100])
{
	int l=strlen(miyao);
	for(int i=0;i<l;i++)
	{
		for(int j=0;j<i;j++)
		{
			if(miyao[i]==miyao[j])
			{
				for(int t=i+1;t<l;t++)
				{
					miyao[t-1]=miyao[t];
				}
				l-=1;
				i-=1;
			}
		}
	}
	miyao[l]='\0';
	printf("%s\n", miyao);
	return miyao;
}

int main()
{
	gets(original_key);
	char* quchong_key=quchong(original_key);
	int l=strlen(quchong_key);
	Block* block=(Block*)malloc(sizeof(Block));
	Block* key[200];
	for (int i=0;i<200;i++)
	{
        key[i]=(Block*)malloc(sizeof(Block));
    }
	for(int i=0;i<l;i++)
	{
		key[i]->ori=quchong_key[i];
		a[(int)quchong_key[i]]=1;
	}
	for(int i=l;i<95;i++)
	{
		for(int j=32;j<127;j++)
		{
			if(a[j]==0)
			{
				key[i]->ori=(char)j;
				a[j]=1;
				break;
			}
		}
	}
	for(int i=0;i<94;i++)
	{
		key[i]->next=key[i+1];
	}
	key[94]->next=key[0];
    for (int i = 0; i < 95; i++) {
        printf("%c", key[i]->ori);
    }
    printf("\n");
	Block* current=key[0];
    char oric = current->ori;
	for(int i=0;i<94;i++)
	{
		int k=(int)current->ori;
		Block* pre=find_pre(current,current);
		pre->next=current->next;
		Block* too=pre->next;
		for(int j=0;j<k - 1;j++)
		{
			too=too->next;
		}
		current->to=too->ori;
		current=too;
	}
    current->to = oric;
	for (int i = 0; i < 95; i++) {
        printf("%c", key[i]->ori);
    }
    printf("\n");
	for(int i=0;i<95;i++)
	{
		printf("%c",key[i]->to);
	}
	FILE *in = fopen("C:\\Users\\24502\\Desktop\\Projects\\DS2025\\homework3\\in.txt", "r");
    FILE *out = fopen("C:\\Users\\24502\\Desktop\\Projects\\DS2025\\homework3\\in_crpyt.txt", "w");
	// FILE *in=fopen("in.txt","r");
	// FILE *out=fopen("in_crpyt.txt","w");
	char buffer[500];
	while(fgets(buffer,sizeof(buffer),in))
	{
		int o=strlen(buffer);
		for(int i=0;i<o;i++)
		{
			for(int j=0;j<95;j++)
			{
				if(buffer[i]==key[j]->ori)
				{
					buffer[i]=key[j]->to;
                    break;
				}
			}
		}
		fwrite(buffer,1,o,out);
	}
	fclose(in);
	fclose(out);
	return 0;
}
