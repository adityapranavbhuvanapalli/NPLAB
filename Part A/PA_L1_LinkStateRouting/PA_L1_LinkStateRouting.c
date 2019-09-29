#include<stdio.h>
#include<stdlib.h>
#define inf 999

int cost[10][10],n;

int spath(int s,int d)
{
    struct path
    {
        int len;
        enum{tentative,confirmed}label;
    }state[10];

    int i,u,j,num=2,min=inf;
    for(i=1;i<=n;i++)
    {
        state[i].label=tentative;
        state[i].len=cost[s][i];
    }
    state[s].label=confirmed;
    while(num<=n)
    {
        min=inf;
        for(i=1;i<=n;i++)
        {
            if(state[i].label==tentative && state[i].len<min)
            {
                min=state[i].len;
                u=i;
            }
        }
        state[u].label=confirmed;
        num++;
        for(j=1;j<=n;j++)
        {
            if(state[u].len + cost[u][j]<state[j].len && state[j].label==tentative)
            {
                state[j].len=state[u].len+cost[u][j];
            }
        }
    }
    return state[d].len;
}

int main()
{
    int i,j,min,d;
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
        {   
            if(cost[i][j]!=0 && cost[i][j]!=inf)
                printf("%c\t%d\n",64+j,cost[i][j]);
        }
    }

    printf("Enter the source : ");
    scanf(" %c",&src);
    for(i=1;i<=n;i++)                                                                           
    {
        min=spath(src-64,i);
        printf("Min path from %c to %c =%d\n",src,64+i,min);
    }
    return 0;
}
