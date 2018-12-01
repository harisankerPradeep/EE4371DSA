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
	int childEdge;
	double current_flow;
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
	int flow;
};
//variable noting end pos of heap
int end = 1;
int extract(double *heap, int *p, struct Node **nodes){//to extract min from heap
	if(end==1){
		end--;
		return 1;
	}
	if(end<1){
		return 0;
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
		if(a>end || b>end)
			break;
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
	return 1;
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
int dijkstras(int n,int src, int dst, struct Node **nodes, struct Edge **edges){//To perform dijkstras
	end = 1;
//	set all nodes as it's parent	
	for(int i=0;i<n;i++){
		nodes[i]->parent = i;
		nodes[i]->set = 0;
		nodes[i]->current_flow = INT_MAX;
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
	int stop = 0;
	while(!reached){
	// get the nearest node from heap
		double min_d = heap[0];
		int min_p = p[0];
		min_d = 0;
		int result = extract(heap,p,nodes);		
		if(result == 0){
			stop++;	
			break;
		}
//		printf("extracted node %d end:%d heap_pos:%d \n",min_p,end,nodes[min_p]->heap_pos);
		if(min_p == dst){
			reached = 1;
			break;
		}
		// Relax the nearest node
		struct Node *a = nodes[min_p];
		struct Neighbor *head = a->head;
		a->set = 1;
		if(min_d!= a->current_flow)
			//printf("ERROR: %lf\n",(min_d-(a->current_flow)));
		a->set_distance = min_d;
		while(head!=NULL){
			int e = head->e;
			double d = edges[e]->flow;
//			if(d>50)
//				d = 100;
//			if(d>20)
//				d = 50;
			d = 100 - d;			
			int pos = head->dst;
			//printf(" considering %d --> %d",min_p,pos); 
			if(nodes[pos]->set!=0 || d>=100){
				head = head->next;
				continue;
			}
			if(min_d+d<=nodes[pos]->current_flow){
				nodes[pos]->parent = min_p;
				nodes[pos]->childEdge = e;
				nodes[pos]->current_flow = min_d + d;
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
	if(stop!=0)
		return 0;
	//find the min flow in path found
	struct Node *child = nodes[dst];
	int min = INT_MAX;
	if(min>edges[child->childEdge]->flow)
		min = edges[nodes[child->parent]->childEdge]->flow;
	while(1){
		if(child->parent == src){
			break;
		}
		if(min>edges[child->childEdge]->flow)
			min = edges[child->childEdge]->flow;
		child = nodes[child->parent];
	}
	//print path with min flow
	child = nodes[dst];
	printf("%d %d %d %d\n",dst,child->parent,min,child->childEdge);
	while(1){
		if(child->parent == src){
			break;
		}
		printf("%d %d %d %d\n",child->parent,nodes[child->parent]->parent,min,nodes[child->parent]->childEdge);
//		printf("%d %d %d\n",child->parent,nodes[child->parent]->parent,min);
		child = nodes[child->parent];
	}
	//subtract the min flow from all edges	
	child = nodes[dst];
	edges[nodes[child->parent]->childEdge]->flow -= min;
	while(1){
		if(child->parent == src){
			break;
		}
		edges[nodes[child->parent]->childEdge]->flow -= min;
		child = nodes[child->parent];
	}
	return 1;	
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
		if(edges[i]->type == 'p')
			edges[i]->flow = 100;
		if(edges[i]->type == 's')
			edges[i]->flow = 50;
		if(edges[i]->type == 't')
			edges[i]->flow = 20;

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
	int a;int b;
	scanf("%d",&a);
	scanf("%d",&b);
//	struct Neighbor *h = nodes[11558]->head;
//	while(h!=NULL){
//		printf("%d %d-->",h->dst,edges[h->e]->flow);
//		h = h->next;
//	}		
	int result = 1;
	while(result)
		result = dijkstras(n,b,a,nodes,edges);
}
