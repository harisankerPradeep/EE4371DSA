#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

// Perform dijkstras on each cities till the next city is reached

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
//variable noting end pos of heap
int end = 1;
void extract(double *heap, int *p, struct Node **nodes){//to extract min from heap
	if(end==1){
		end--;
		return;
	}
	if(end<1){
		return;
	}
	// Move the last element of the heap to the first position
	p[0] = p[end-1];
	heap[0] = heap[end-1];
	nodes[p[end-1]]->heap_pos = 0;
	heap[end-1] = INT_MAX;
	end--;
	int i=0;
	while(i<end){
		int a = (2*i)+1;
		int b = (2*i)+2;
		if(heap[i]>heap[a] && heap[i]>heap[b]){
			if(heap[a]<=heap[b]){
				double tmp = heap[a];
				heap[a] = heap[i];
				heap[i] = tmp;

				int t = p[i];
				p[i] = p[a];
				p[a] = t;
				nodes[p[i]]->heap_pos = i;
				nodes[p[a]]->heap_pos = a;

				i = a;
			}
			else{
				double tmp = heap[b];
				heap[b] = heap[i];
				heap[i] = tmp;

				int t = p[i];
				p[i] = p[b];
				p[b] = t;
				nodes[p[i]]->heap_pos = i;
				nodes[p[b]]->heap_pos = b;

				
				i = b;
			}
		}
		else if(heap[i]>heap[a] && heap[i]<=heap[b]){
			double tmp = heap[a];
			heap[a] = heap[i];
			heap[i] = tmp;

			int t = p[i];
			p[i] = p[a];
			p[a] = t;
			nodes[p[i]]->heap_pos = i;
			nodes[p[a]]->heap_pos = a;


			i = a;
		}
		else if(heap[i]>heap[b] && heap[i]<=heap[a]){
			double tmp = heap[b];
			heap[b] = heap[i];
			heap[i] = tmp;

			int t = p[i];
			p[i] = p[b];
			p[b] = t;
			nodes[p[i]]->heap_pos = i;
			nodes[p[b]]->heap_pos = b;


			i = b;
		}
		else{
			break;
		}

	}
}
void add(double *heap, int *p, struct Node **nodes, int dst, double d){//to add values to heap
	heap[end] = d;	
	p[end] = dst;
	nodes[dst]->heap_pos = end;
	int i = end;
       	end++;
	while(i>0){
		int a = (i-1)/2;
		if(heap[a]>heap[i]){
			double tmp = heap[a];
			heap[a] = heap[i];
			heap[i] = tmp;

			int t = p[a];
			p[a] = p[i];
			p[i] = t;
			nodes[p[a]]->heap_pos = a;
			nodes[p[i]]->heap_pos = i;
			
			i = a;
		}
		else{
			break;
		}
	}
	nodes[dst]->added_to_heap = 1;	
}
void replace(double *heap, int *p, struct Node **nodes, int dst, double d){//To update values in the heap
	int i = nodes[dst]->heap_pos;
	heap[i] = d;	
	while(i>0){
		int a = (i-1)/2;
		if(heap[a]>heap[i]){
			double tmp = heap[a];
			heap[a] = heap[i];
			heap[i] = tmp;

			int t = p[a];
			p[a] = p[i];
			p[i] = t;
			nodes[p[i]]->heap_pos = i;
			nodes[p[a]]->heap_pos = a;

			i = a;
		}
		else{
			break;
		}
	}
}
void dijkstras(int n,int src, int dst, struct Node **nodes, struct Edge **edges){//To perform dijkstras
	end = 1;
//	set all nodes as it's parent	
	for(int i=0;i<n;i++){
		nodes[i]->parent = i;
		nodes[i]->set = 0;
		nodes[i]->current_distance = INT_MAX;
	       	nodes[i]->set_distance = INT_MAX;
		nodes[i]->heap_pos = INT_MAX;
		nodes[i]->added_to_heap = 0;
	}
	
//	create a heap and array to point nodes from heap positions
	double *heap = malloc(sizeof(double)*n);
	int *p = malloc(sizeof(int)*n);
	for(int i=0;i<n;i++){
		heap[i] = INT_MAX;
		p[i] = INT_MAX;
	}	
// 	set src distance to 0 and its position in heap 0
	heap[0] = 0;
	p[src] = src;
	int tmp = p[src];
	p[src] = p[0];
	p[0] = tmp;
	nodes[src]->added_to_heap = 1;
	int reached = 0;
	while(!reached){
	// get the nearest node from heap
		double min_d = heap[0];
		int min_p = p[0];
		extract(heap,p,nodes);		
//		printf("extracted node %d end:%d heap_pos:%d \n",min_p,end,nodes[min_p]->heap_pos);
		if(min_p == dst){
			reached = 1;
			break;
		}
		// Relax the nearest node
		struct Node *a = nodes[min_p];
		struct Neighbor *head = a->head;
		a->set = 1;
		if(min_d!= a->current_distance)
			//printf("ERROR: %lf\n",(min_d-(a->current_distance)));
		a->set_distance = min_d;
		while(head!=NULL){
			int e = head->e;
			double d = edges[e]->distance;
			int pos = head->dst;
			//printf(" considering %d --> %d",min_p,pos); 
			if(nodes[pos]->set!=0){
				head = head->next;
				continue;
			}
			if(min_d+d<=nodes[pos]->current_distance){
				nodes[pos]->parent = min_p;
				nodes[pos]->current_distance = min_d + d;
				if(nodes[pos]->added_to_heap==0){
					add(heap,p,nodes,pos,min_d+d);
					//printf("added %d end: %d\n",pos,end);
				}
				else{
					replace(heap,p,nodes,pos,min_d+d);		
					//printf("updating %d\n",pos);	
				}
			}
			head = head->next;
		}
	}
	struct Node *child = nodes[dst];
	printf("%d\n",dst);
	while(1){
		if(child->parent == src){
			break;
		}
		printf("%d\n",child->parent);
		child = nodes[child->parent];
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
	int N;//Number of cities to cover;	
	scanf("%d",&N);
	int *cities = malloc(sizeof(int)*N);
	for(int i=0;i<N;i++)
		scanf("%d",&cities[i]);
	for(int i=1;i<N;i++){
		dijkstras(n,cities[i],cities[i-1],nodes,edges);}
	dijkstras(n,cities[0],cities[N-1],nodes,edges);
	printf("%d\n",cities[0]);
}
