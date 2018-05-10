#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <omp.h>

#define INFINITY 1001
#define MAX 10000
 
struct Compare { 
	int val;
	int index; 
};


int cost[MAX][MAX];
uint8_t visited[MAX];
int G[MAX][MAX];
int distance[MAX];

void dijkstra(int n,int startnode);

int main()
{	
	int i,j,n,u;
	#ifdef DEBUG
	printf("Enter no. of vertices:");
	#endif
	scanf("%d",&n);
	
	#ifdef DEBUG
	printf("\nEnter the adjacency matrix:\n");
	#endif
    
	for(i=0;i<n;i++)
        for(j=0;j<n;j++)
            scanf("%d",&G[i][j]);
   

	#ifdef DEBUG
    printf("\nEnter the starting node:");
	#endif
	
	scanf("%d",&u);
    dijkstra(n,u);
    
	#ifdef DEBUG
    printf("\nEnter the starting node:\n");
	for(i=0;i<n;i++)
		printf("Distancia do vertice %d: %d\n",i,distance[i]);
	#endif

	return 0;
}
 
void dijkstra(int n,int startnode)
{
	int count,nextnode,i,j;
	struct Compare mindistance;

    //pred[] stores the predecessor of each node
    //count gives the number of nodes seen so far
    //create the cost matrix
    for(i=0;i<n;i++)
        for(j=0;j<n;j++)
            if(G[i][j]==0)
                cost[i][j]=INFINITY;
            else
                cost[i][j]=G[i][j];
    
    //initialize pred[],distance[] and visited[]
    for(i=0;i<n;i++)
    {
        distance[i]=cost[startnode][i];
        visited[i]=0;
    }
    
    distance[startnode]=0;
    visited[startnode]=1;
    count=1;
   
	#pragma omp declare reduction(minimum : struct Compare : omp_out = omp_in.val < omp_out.val ? omp_in : omp_out)

    while(count<n-1)
    {
        mindistance.val=INFINITY;
        //nextnode gives the node at minimum distance
		#pragma omp parallel for reduction(minimum:mindistance)
		for(i=0;i<n;i++) {
            if(distance[i]<mindistance.val && !visited[i]) {
                mindistance.val=distance[i];
				mindistance.index = i;
            }
		}

		nextnode = mindistance.index;
            
        //check if a better path exists through nextnode            
        visited[nextnode]=1;
		//#pragma omp parallel for
        for(i=0;i<n;i++) {
            if(!visited[i]) {
                if(mindistance.val+cost[nextnode][i]<distance[i]) {
                    distance[i]=mindistance.val+cost[nextnode][i];
                }
			}
		}
    
		count++;
    }
	
}
