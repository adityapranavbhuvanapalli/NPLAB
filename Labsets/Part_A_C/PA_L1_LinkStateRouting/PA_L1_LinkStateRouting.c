#include<stdio.h>
#include<stdlib.h>
#define inf 999

int cost[10][10],n;
int parent[10];
int dijkstra (int s, int d)	//s - source , d - destination
{
    struct path
    {
        int len;
        enum {no,yes} visited;	//no - 0 , yes - 1
    }state[10];

    int i,minind,j,num=2,min=inf;

	//Initialise
    for(i=1;i<=n;i++)
    {
        state[i].visited=no;
        state[i].len=cost[s][i];	//Initial cost from source
		if(cost[s][i]!=inf)	parent[i] = s;
    }
    state[s].visited=yes;	//Because source is already visited 

	//Dijkstra
    while(num<=n)
    {
        min=inf;
		//Finding index of min path not visited 
        for(i=1;i<=n;i++)
        {
            if(state[i].visited==no && state[i].len<min)
            {
                min=state[i].len;
                minind=i;
            }
        }
	
        state[minind].visited=yes;
        num++;

		//Updating the cost
        for(j=1;j<=n;j++)
        {
            if(state[minind].len + cost[minind][j]<state[j].len && state[j].visited==no)
            {
                state[j].len=state[minind].len+cost[minind][j];
				parent[j]=minind;
            }
        }
    }
    return state[d].len;
}

int main()
{
    int i,j,min,d,node;
    char src;
    printf("Enter number of nodes : ");
    scanf("%d",&n);
    printf("Enter the Cost Matrix : (0 for inf)\n");
    for(i=1;i<=n;i++)
    {
        for(j=1;j<=n;j++)
        {
             scanf("%d",&cost[i][j]);
             if(cost[i][j]==0 && i!=j)
             {
                cost[i][j]=inf;
             }
        } 
    }
    printf("Link State Protocol");
    for(i=1;i<=n;i++)
    {
        printf("\n**** From Node = %c****\n",64+i);
        printf("Node\tCost\n");
        for(j=1;j<=n;j++)
            if(cost[i][j]!=0 && cost[i][j]!=inf)
                printf("%c\t%d\n",64+j,cost[i][j]);
    }

    printf("Enter the source : ");
    scanf(" %c",&src);

    for(i=1;i<=n;i++)                                                                           
    {
        min=dijkstra(src-64,i);
        printf("Min path from %c to %c = %d\t",src,64+i,min);
		node=i;
		printf("%c", 64+node);
        while( node != (src-64))
        {
            printf(" <- %c", 64+parent[node]);
            node = parent[node];
        }
		printf("\n");
    }
    return 0;
}


/*
****************OUTPUT**********************

Enter number of nodes : 9
Enter the Cost Matrix : (0 for inf)
0     4     999   999   999   999   999   8     999
4     0     8     999   999   999   999   11    999
999   8     0     7     999   4     999   999   2
999   999   7     0     9     14    999   999   999
999   999   999   9     0     10    999   999   999
999   999   4     14    10    0     2     999   999
999   999   999   999   999   2     0     1     6
8     11    999   999   999   999   1     0     7
999   999   2     999   999   999   6     7     0
Link State Protocol
**** From Node = A****
Node	Cost
B	4
H	8

**** From Node = B****
Node	Cost
A	4
C	8
H	11

**** From Node = C****
Node	Cost
B	8
D	7
F	4
I	2

**** From Node = D****
Node	Cost
C	7
E	9
F	14

**** From Node = E****
Node	Cost
D	9
F	10

**** From Node = F****
Node	Cost
C	4
D	14
E	10
G	2

**** From Node = G****
Node	Cost
F	2
H	1
I	6

**** From Node = H****
Node	Cost
A	8
B	11
G	1
I	7

**** From Node = I****
Node	Cost
C	2
G	6
H	7
Enter the source : D
Min path from D to A = 19		A <- B <- C <- D
Min path from D to B = 15		B <- C <- D
Min path from D to C = 7		C <- D
Min path from D to D = 0		D
Min path from D to E = 9		E <- D
Min path from D to F = 11		F <- C <- D
Min path from D to G = 13		G <- F <- C <- D
Min path from D to H = 14		H <- G <- F <- C <- D
Min path from D to I = 9		I <- C <- D


********************************************
*/
