#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

struct Node{
	double lat;
	double lon;
	struct Neighbor *head;
	struct Neighbor *tail;
	int set;
	int parent;
	double current_distance;
	double set_distance;
	int added_to_heap;
	int heap_pos;
	int bfsDone;
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
	int counted;
};
struct Queue{
	int dst;
	struct Queue *next;
	int *visited;
	int *path;	
	int cnt;
};
struct Queue* pop(struct Queue **head,struct Queue **tail){
	struct Queue *t = *head;
	*head = (*head)->next;
	return t;
}
void push(struct Queue **head,struct Queue **tail,int dst,int n,int *visited,int *path,int cnt,int e){
	struct Queue *t = malloc(sizeof(struct Queue));
	t->visited = malloc(sizeof(int)*n);
	t->path = malloc(sizeof(int)*n);
	for(int i=0;i<n;i++){
		(t->path)[i] = path[i];
		(t->visited)[i] = visited[i];
	}
	t->cnt = cnt;
	(t->visited)[dst] = 1; 
	(t->path)[cnt] = e;
	t->cnt++;
	t->dst = dst;
//	printf("path\n");
	for(int i=0;i<t->cnt;i++)
		printf("%d\n",(t->path)[i]);
	(*tail)->next = t;
	*tail = t;
	if(*head==NULL)
		*head = *tail;
	struct Queue *x = *head;
//	printf("while pushing\n");
//	while(x!=NULL){
//		printf("%d\n",x->dst);
//		x = x->next;
//	}
}
void allPathBFS(struct Node **nodes,struct Edge **edges,int src,int dst,int n){
	struct Queue *head;
	struct Queue *tail;	
	head = malloc(sizeof(struct Queue));
	head->visited = malloc(sizeof(int)*n);
	head->path = malloc(sizeof(int)*n);
	for(int i=0;i<n;i++){
		(head->path)[i]=0;
		(head->visited)[i]=0;
	}
	head->cnt = 1;
	head->dst = src;
	(head->visited)[src] = 1;
	tail = head;
	int cnt = 0;
	while(head!=NULL){
//		printf("popping\n");
		struct Queue *a = pop(&head,&tail);
		if(a->dst==dst){
			printf("found a path\n");
			int f=0;
			for(int i=1;i<a->cnt;i++){
				printf("%d\n",(a->path)[i]);
				if(edges[(a->path)[i]]->counted == 0){
					edges[(a->path)[i]]->counted++;
					f++;
				}
			}
			if(f==0)
				cnt++;
			if(cnt==10)
				break;
			continue;
		}
		struct Neighbor *tmp = nodes[a->dst]->head;
		while(tmp!=NULL){
			int b = tmp->dst;
			if((a->visited)[b]==0){
				//add to queue
//				printf("pushing %d %d %d\n",b,(tmp->e),(a->visited)[b]);
				struct Queue *x = head;
//				printf("before pushing\n");
//				while(x!=NULL){
//					printf("%d\n",x->dst);
//					x = x->next;
//				}
				push(&head,&tail,b,n,a->visited,a->path,a->cnt,(tmp->e));
				x = head;
				
//				printf("after pushing \n");
//				while(x!=NULL){
//					printf("%d\n",x->dst);
//					x = x->next;
//				}
			}
			tmp = tmp->next;
		}	
	}
}
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
	struct Edge** edges = malloc(sizeof(struct Edge*)*r);
	for(int i = 0; i<r; i++){
		edges[i] = malloc(sizeof(struct Edge));
		fscanf(fp,"%d %d %c %lf",&(edges[i]->src),&(edges[i]->dst),&(edges[i]->type),&(edges[i]->distance));
		//for src 
		edges[i]->counted = 0;
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
//	struct Neighbor *h = nodes[7]->head;
//	while(h!=NULL){
//		printf("%d-->",h->dst);
//		h = h->next;
//	}		

//	allPathBFS(nodes,edges,11558,880,n);
}
