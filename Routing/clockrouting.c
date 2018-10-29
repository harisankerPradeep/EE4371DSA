#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

struct neighbor{
	int pos;
	struct neighbor *next;
};
struct edges{
	int weight;
	int a;
	int b;
};

int comparator(const void *p, const void *q){
	struct edges *a = *(struct edges**)p;
	struct edges *b = *(struct edges**)q;
	int l = a->weight; 
	int r = b->weight;  
	return (l - r); 
} 
int find(int *p,int x){
	if(p[x]==-1)	
		return x;
	else
		find(p,p[x]);
}

int detectCycles(struct edges **e, int *chosenEdges, int t, int size){
	int *p = malloc(sizeof(int)*(t+1));
	for(int i=0;i<t+1;i++)
		p[i] = -1;
	for(int i=0;i<size;i++){
		if(chosenEdges[i]==0)
			continue;
		struct edges *x = e[i];
		if(find(p,x->a)==find(p,x->b))
			return 1;
		else{
			int xset = find(p,x->a);
			int yset = find(p,x->b);
			p[xset]=yset;
		}
	}
	return 0;
}
int main(){
	int h;
	int b;

	scanf("%d %d",&b,&h);
	int x1;
	int y1;
	scanf("%d %d",&x1,&y1);
	int t;
	scanf("%d",&t);
	int *x = malloc(sizeof(int)*(t+1));
	int *y = malloc(sizeof(int)*(t+1));
	int *set = malloc(sizeof(int)*(t+1));
	struct neighbor **n = malloc(sizeof(struct neighbor*)*(t+1));
	x[0] = x1;
	y[0] = y1;
	set[0] = 0;
	for(int i = 1;i<t+1; i++){
		scanf("%d %d",&x[i],&y[i]);	
		set[i] = 0;
	}

	//To perform kruskal's
	int size = (int)((t*(t+1))/2);
	struct edges **e = malloc(sizeof(struct edges*)*(size));
	int cnt = 0;
	int *chosenEdges = malloc(sizeof(int)*(size));
	for(int i = 0;i<t+1;i++)
		for(int j=i+1;j<t+1;j++){
			e[cnt] = malloc(sizeof(struct edges));
			e[cnt]->weight = abs(x[i]-x[j])+abs(y[i]-y[j]);
			e[cnt]->a = i;
			e[cnt]->b = j;
			chosenEdges[cnt] = 0;
			cnt++;
		}

	for(int i = 0;i<size;i++)
		printf("%d-->%d : %d \n",e[i]->a,e[i]->b,e[i]->weight);
	
	qsort((void*)e, size, sizeof(struct edges*), comparator); 	
	printf("-------------------------\n");
	for(int i = 0;i<size;i++)
		printf("%d-->%d : %d \n",e[i]->a,e[i]->b,e[i]->weight);

	// Performing Kruskal's	
	int numOfedges = 0;
		
	while(numOfedges<t){
		for(int i=0;i<size;i++){
			struct edges* p = e[i];
			chosenEdges[i]++;
			if(detectCycles(e,chosenEdges,t,size)==1){
				chosenEdges[i]--;
				continue;
			}
			struct neighbor *head;
			
			if(n[p->a]==NULL){
				n[p->a] = malloc(sizeof(struct neighbor));
				n[p->a]->pos = p->b;
			}
			else{
//				printf("here!i\n");
				head = n[p->a];
				struct neighbor *prev;
				while(head!=NULL && prev!=NULL){
					prev = head;
					head = head->next;
					
				}
				head = malloc(sizeof(struct neighbor));
				head->pos = p->b;
				prev->next = head;
//				head = n[p->a];
//				while(head!=NULL){
//					printf("%d %d\n",p->a,head->pos);
//					head = head->next;
//				}
			}
			
			if(n[p->b]==NULL){
				n[p->b] = malloc(sizeof(struct neighbor));
				n[p->b]->pos = p->a;
			}
			else{
//				printf("here!i\n");
				head = n[p->b];
				struct neighbor *prev;
				while(head!=NULL){
					prev = head;
					head = head->next;
				}
				head = malloc(sizeof(struct neighbor));
				head->pos = p->a;
				prev->next = head;
			}			
			set[p->a]++;
			set[p->b]++;
			numOfedges++;
			printf(" number %d \n",numOfedges);
			for(int j=0;j<t+1;j++){
				printf("%d \n",j);
				head = n[j];
				if(n[j]==NULL){
					printf("no neighbors yet\n");
					continue;
				}
				while(head!=NULL){
					printf("%d %d\n",j,head->pos);
					head = head->next;
				}
			}
		}
		//print result of kruskal
		int len = 0;
		for(int i=0;i<size;i++){
			if(chosenEdges[i]==0)
				continue;
			struct edges *x = e[i];
			printf("%d %d\n",x->a,x->b);
			len += x->weight;
		}
		printf("total weight: %d %d",len,numOfedges);
	}	
}
