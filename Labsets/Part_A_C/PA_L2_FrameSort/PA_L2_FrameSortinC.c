#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#include <math.h>
typedef struct 
{
	char a[100];
	int seqNo,randNo,size;
}frame;

void sort(frame f[100],int n,char ch)
{
	for(int i=1;i<n;i++)
	{
		frame v=f[i];
		int j=i-1;
		while(j>=0 && ( (f[j].seqNo>v.seqNo && ch=='s') || (f[j].randNo>v.randNo && ch=='r') ) )
		{
			f[j+1]=f[j];
			j--;
		}
		f[j+1]=v;
	}
	printf("SeqNo\tRanNo\tSeg\tSize\n");
	for(int i=0;i<n;i++)
	{
		printf("%d\t%d\t%s\t%d\n",f[i].seqNo,f[i].randNo,f[i].a,f[i].size);
	}
	printf("\n");
}

int main()
{
	char a[100];
	int mb;
	srand(time(NULL));
	printf("Enter string 	: ");scanf("%s",a);
	printf("Max block size 	: ");scanf("%d",&mb);
	frame f[100];
	int i=0,j,k=0;
	printf("\nFrames divided into : \n");
	printf("SeqNo\tRanNo\tSeg\tSize\n");
	while(k<strlen(a))
	{
		f[i].seqNo=i+1;
		f[i].randNo=rand()%1000;
		f[i].size=rand()%(mb)+1;
		for(j=0;j<f[i].size;j++)
		{
			f[i].a[j]=a[k+j];
		}
		f[i].a[k+j]='\0';
		printf("%d\t%d\t%s\t%d\n",f[i].seqNo,f[i].randNo,f[i].a,f[i].size);
		k+=f[i].size;
		i++;
	}
	printf("\nFrames sent and received as \n");
	sort(f,i,'r');
	printf("Unsorted string\n");
	for(int n=0;n<i;n++)
		printf("%s",f[n].a);
	printf("\n");
	printf("\nFrames sorted as \n");
	sort(f,i,'s');
	printf("Sorted string\n");
	for(int n=0;n<i;n++)
		printf("%s",f[n].a);
	printf("\n");
	return 0;
}
