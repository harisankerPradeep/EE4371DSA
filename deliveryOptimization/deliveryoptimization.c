#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

struct Node{
	double lat;
	double lon;
};
struct Edge{
	char type;
	int src;
	int dst;
	double distance;
};
int main(){
	printf("Hello World!\n");
	int n;
	FILE *fp;
	fp = fopen("./tn_graph.txt","r");
	fscanf(fp,"%d",&n);
	struct Node **nodes = malloc(sizeof(struct Node*)*n);
	for(int i = 0;i< n;i++){
		double a,b;
		fscanf(fp,"%lf %lf",&a,&b);
		printf("%d %lf %lf\n",n,a,b);
		nodes[i] = malloc(sizeof(struct Node));
		nodes[i]->lat = a;
		nodes[i]->lon = b;
	}
	int r;
	fscanf("%d",&r);
	struct Edge** edges = malloc(sizeof(struct Edge*)*n);
	for(int i = 0; i<n; i++){
		edges[i] = malloc(sizeof(struct Edge));
		fscanf("%d %d %c %lf",&(edges[i]->src),&(edges[i]->src),	
	}		
	return 0;
}
