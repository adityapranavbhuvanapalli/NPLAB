#include<stdio.h>
#include<stdlib.h>
#define inf 999

int cost[10][10],n;
int parent[10];
int dijkstra (int s, int d)	//s - source , d - destination
{
    

    int i,minind,num=2,min=inf;
	int visited[n],dist[n];
	//Initialise
    for(i=0;i<n;i++)
    {
    	visited[i]=0;
    	dist[i]=cost[s][i];		//Initial cost from source
		if(cost[s][i]!=inf)	parent[i] = s;
    }
    visited[s]=1;	//Because source is already visited 

	//Dijkstra
    while(num<=n)
    {
        min=inf;
		//Finding index of min path not visited 
        for(i=0;i<n;i++)
        {
            if(visited[i]==0 && dist[i]<min)
            {
                min=dist[i];
                minind=i;
            }
        }
	
        visited[minind]=0;
        num++;

		//Updating the cost
        for(i=0;i<n;i++)
        {
            if(dist[minind] + cost[minind][i]<dist[i] && visited[i]==0)
            {
                dist[i]=dist[minind]+cost[minind][i];
				parent[i]=minind;
            }
        }
    }
    return dist[d];
}

int main()
{
    int i,j,min,d,node;
    int src;
    printf("Enter number of nodes : ");
    scanf("%d",&n);
    printf("Enter the Cost Matrix : (0 for inf)\n");
    for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
        {
             scanf("%d",&cost[i][j]);
             if(cost[i][j]==0 && i!=j)
             {
                cost[i][j]=inf;
             }
        } 
    }
    printf("Link State Protocol");
    for(i=0;i<n;i++)
    {
        printf("\n**** From Node = %d****\n",i);
        printf("Node\tCost\n");
        for(j=1;j<=n;j++)
            if(cost[i][j]!=0 && cost[i][j]!=inf)
                printf("%d\t%d\n",j,cost[i][j]);
    }

    printf("Enter the source : ");
    scanf(" %d",&src);

    for(i=0;i<n;i++)                                                                           
    {
        min=dijkstra(src,i);
        printf("Min path from %d to %d = %d\t",src,i,min);
		node=i;
		printf("%d", node);
        while( node != (src))
        {
            printf(" <- %d", parent[node]);
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
