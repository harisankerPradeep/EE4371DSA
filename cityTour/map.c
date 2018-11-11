#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

struct Node{
	double lat;
	double lon;
	struct Neighbor *head;
	struct Neighbor *tail;
};
struct Neighbor{
	int dst;
	int e;
	struct Neighbor *next;
};
struct Edge{
	char type;
	int src;
	int dst;
	double distance;
};
int main(){
	int n;
	FILE *fp;
	fp = fopen("./tn_graph.txt","r");
	fscanf(fp,"%d",&n);
	struct Node **nodes = malloc(sizeof(struct Node*)*n);
	for(int i = 0;i< n;i++){
		double a,b;
		fscanf(fp,"%lf %lf",&a,&b);
		nodes[i] = malloc(sizeof(struct Node));
		nodes[i]->lat = a;
		nodes[i]->lon = b;
	}
	int r;
	fscanf(fp,"%d",&r);
	struct Edge** edges = malloc(sizeof(struct Edge*)*n);
	for(int i = 0; i<n; i++){
		edges[i] = malloc(sizeof(struct Edge));
		fscanf(fp,"%d %d %c %lf",&(edges[i]->src),&(edges[i]->dst),&(edges[i]->type),&(edges[i]->distance));
		//for src 
		int src = edges[i]->src;
		int dst = edges[i]->dst;
		if(nodes[src]->head==NULL){
			struct Neighbor *n = malloc(sizeof(struct Neighbor));
			n->dst = dst;
			n->e = i;
			nodes[src]->head = n;
			nodes[src]->tail = n;
//			struct Neighbor *h = nodes[src]->head;
//			printf("start here %d : ",src);
//			while(h!=NULL){
//				printf("%d-->",h->dst);
//				h = h->next;
//			}
//			printf("\n");
		}
		else{
			struct Neighbor *n = malloc(sizeof(struct Neighbor));
			n->dst = dst;
			n->e = i;
			(nodes[src]->tail)->next = n;
			nodes[src]->tail = n;
//			struct Neighbor *h = nodes[src]->head;
//			printf("%d : ",src);
//			while(h!=NULL){
//				printf("%d-->",h->dst);
//				h = h->next;
//			}
//			printf("\n");
		}
		//for dst	
		if(nodes[dst]->head==NULL){
			struct Neighbor *n = malloc(sizeof(struct Neighbor));
			n->dst = src;
			n->e = i;
			nodes[dst]->head = n;
			nodes[dst]->tail = n;
//			struct Neighbor *h = nodes[dst]->head;
//			printf("start here %d : ",dst);
//			while(h!=NULL){
//				printf("%d-->",h->dst);
//				h = h->next;
//			}
//			printf("\n");

		}
		else{
			struct Neighbor *n = malloc(sizeof(struct Neighbor));
			n->dst = src;
			n->e = i;
			(nodes[dst]->tail)->next = n;
			nodes[dst]->tail = n;
//			struct Neighbor *h = nodes[dst]->head;
//			printf("start here %d : ",dst);
//			while(h!=NULL){
//				printf("%d-->",h->dst);
//				h = h->next;
//			}
//			printf("\n");

		}
	}		
	struct Neighbor *h = nodes[7]->head;
//	while(h!=NULL){
//		printf("%d-->",h->dst);
//		h = h->next;
//	}		
}
