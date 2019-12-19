#include <stdio.h>
#include <stdlib.h>

int cost[20][20],n;
void dijkstra(int s)
{
	int dist[n],visited[n],parent[n],num=0,minind,temp,min;
	visited[s]=1;
	for(int i=0;i<n;i++)
	{
		dist[i]=cost[s][i];
		visited[i]=0;
		if(dist[i]!=999) parent[i]=s;
	}
	
	while(num<n-1)
	{
		min=999;
		for(int i=0;i<n;i++)
		{
			if(dist[i]<min && visited[i]==0)
			{
				min=dist[i];
				minind=i;
			}
		}
		
		visited[minind]=1;
		
		for(int i=0;i<n;i++)
		{
			if(dist[minind]+cost[minind][i]<dist[i] && visited[i]==0)
			{
				dist[i]=dist[minind]+cost[minind][i];
				parent[i]=minind;
			}
		}
		num++;
	}
	printf("Distances and Paths : \n");
	for(int i=0;i<n;i++)
	{
		printf("Distance from %d to %d = %d\t",s,i,dist[i]);
		printf("PATH : ",i);
		temp=i;
		while(temp!=s)
		{
			printf("%d<-",temp);
			temp=parent[temp];
		}
		printf("%d\n",temp);
	}
}
int main()
{
	int src;
	printf("n = "); scanf("%d",&n);
	printf("Cost Matrix :\n");
	for(int i=0;i<n;i++)
		for(int j=0;j<n;j++)
			scanf("%d",&cost[i][j]);
	
	printf("Link State Protocol");
    for(int i=0;i<n;i++)
    {
        printf("\n**** From Node = %d****\n",i);
        printf("Node\tCost\n");
        for(int j=0;j<n;j++)
            if(cost[i][j]!=0 && cost[i][j]!=999)
                printf("%d\t%d\n",j,cost[i][j]);
    }
	
	printf("Source s = ");scanf("%d",&src); 
	dijkstra(src);
	return 0;
}
