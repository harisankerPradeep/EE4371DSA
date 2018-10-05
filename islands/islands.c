#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
struct neighbor{
	struct vertex *value;
	char *town;
	struct neighbor *next;
	int weight;
};
struct vertex{
	char *town;
	int island_number;
	struct neighbor *start;
	struct neighbor *end;
	struct vertex *next;
	int current_distance;
	int set;
	int set_distance;
};
int is = 0;

void insert(struct vertex **h,char *o,char *d, int w){
	struct vertex *head = *h;

	if(head->town==NULL){
		head->town = malloc(strlen(o)+1);
		strcpy(head->town,o);
		head->island_number = ++is;

		struct neighbor *n = malloc(sizeof(struct neighbor));
		n->town = malloc(strlen(d)+1);
		strcpy(n->town,d);
		n->weight = w;
		head->start = n;
		head->end = n;

		struct vertex *ne = malloc(sizeof(struct vertex));
		ne->town = malloc(strlen(d)+1);
		strcpy(ne->town,d);
		ne->island_number = is;

		n = malloc(sizeof(struct neighbor));
		n->town = malloc(strlen(o)+1);
		strcpy(n->town,o);
		n->weight = w;
		n->value = head;

		ne->start = n;
		ne->end = n;

		head->next = ne;
		head->end->value = ne;
		return;
	}

	int flag = 0;
	int entered = 0;
	struct vertex *last;
	struct vertex *jic = NULL;
	while(head!=NULL){
		if(strcmp(head->town,o)==0){
			flag++;
			struct neighbor *n = malloc(sizeof(struct neighbor));
			n->town = malloc(strlen(d)+1);
			strcpy(n->town,d);
			n->weight = w;
			if(jic!=NULL){
				n->value = jic;
				jic->end->value = head;
			}
			else
				jic = head;
			head->end->next = n;
			head->end = n;
			entered = 1;
			
		}
		if(strcmp(head->town,d)==0){
			flag++;
			struct neighbor *n = malloc(sizeof(struct neighbor));
			n->town = malloc(strlen(o)+1);
			strcpy(n->town,o);
			n->weight = w;
			if(jic!=NULL){
				n->value = jic;
				jic->end->value = head;
			}
			else
				jic = head;

			head->end->next = n;
			head->end = n;
			entered = 2;
		}
		if(flag == 2){
			return;
		}
		last = head;
		head = head->next;
	}

	if(flag==1){
		head = malloc(sizeof(struct vertex));
		if(entered==2){
			head->town = malloc(strlen(o)+1);
			strcpy(head->town,o);

			struct neighbor *n = malloc(sizeof(struct neighbor));
			n->town = malloc(strlen(d)+1);
			strcpy(n->town,d);
			n->weight = w;
			if(jic!=NULL){
				n->value = jic;
				jic->end->value = head;
			}
			else
				jic = head;

			head->start = n;
			head->end = n;
		}
		if(entered==1){
			head->town = malloc(strlen(d)+1);
			strcpy(head->town,d);

			struct neighbor *n = malloc(sizeof(struct neighbor));
			n->town = malloc(strlen(o)+1);
			strcpy(n->town,o);
			n->weight = w;
			if(jic!=NULL){
				n->value = jic;
				jic->end->value = head;
			}
			else
				jic = head;

			head->start = n;
			head->end = n;
		}
		last->next = head;
		return;
	}
	
	if(flag==0){
		head = malloc(sizeof(struct vertex));

		head->town = malloc(strlen(o)+1);
		strcpy(head->town,o);

		struct neighbor *n = malloc(sizeof(struct neighbor));
		n->town = malloc(strlen(d)+1);
		strcpy(n->town,d);
		n->weight = w;
		head->start = n;
		head->end = n;

		struct vertex *ne = malloc(sizeof(struct vertex));
		ne->town = malloc(strlen(d)+1);
		strcpy(ne->town,d);

		n = malloc(sizeof(struct neighbor));
		n->town = malloc(strlen(o)+1);
		strcpy(n->town,o);
		n->weight = w;
		n->value = head;

		ne->start = n;
		ne->end = n;

		head->next = ne;
		head->end->value = ne;
		last->next = head;
		return;
	}
		

}

void split(struct vertex **h){
	struct vertex *head = *h;
	head->island_number = ++is;
	head = head->next;
	while(head!=NULL){
		struct neighbor *tmp = head->start;
		int f = 0;
		while(tmp!=NULL){
			if(tmp->value->island_number!=0){
				head->island_number = tmp->value->island_number;
				f++;
				break;
			}
			tmp = tmp->next;
		}

		if(f==0){
			head->island_number = ++is;
		}
		head = head->next;
	}

}
void push(int *heap,struct vertex **p,int w,struct vertex *v,int end,int cnt){
	heap[end] = w;
	p[end] = v;

	int i = end;
	while(i>0){
		if(heap[i/2]>heap[i]){
			int tmp = heap[i];
			heap[i] = heap[i/2];
			heap[i/2] = tmp;

			struct vertex *t = p[i];
			p[i] = p[i/2];
			p[i/2] = t;
			i = i/2;
		}
		else
			break;

	}

//	printf("pushing...\n");
//	for(i=0;i<end+1;i++)
//		printf("(%d %s)",heap[i],p[i]->town);
//	printf("\n");
}

struct vertex* extract(int *heap, struct vertex **p,int end,int cnt){
	struct vertex *v = p[0];
	v->set = 1;
	v->set_distance = heap[0];
	heap[0] = heap[end-1];
	p[0] = p[end-1];

	int i = 0;
	while(i<(end-1)){
		if(((2*i)+1)<(end-1) && heap[((2*i)+1)]<heap[i]){
			int tmp = heap[i];
			heap[i] = heap[((2*i)+1)];
			heap[((2*i)+1)] = tmp;

			struct vertex *t = p[i];
			p[i] = p[((2*i)+1)];
			p[((2*i)+1)] = t;
			i = (2*i)+1;

		}
		else if(((2*i)+2)<(end-1) && heap[((2*i)+2)]<heap[i]){
			int tmp = heap[i];
			heap[i] = heap[(2*i)+2];
			heap[(2*i)+2] = tmp;

			struct vertex *t = p[i];
			p[i] = p[(2*i)+2];
			p[(2*i)+2] = t;
			i = (2*i)+2;
		}
		else
			break;
	}
//	printf("extracting...");
//	for(i=0;i<end-1;i++)
//		printf("(%d %s)",heap[i],p[i]->town);
//	printf("\n");

	return v;

}
int dijkstra(struct vertex **h,struct vertex **ve){
	struct vertex *head = *h;
	struct vertex *tmph = *h;
	struct vertex *v = *ve;
	struct vertex *tmpv = *ve;
	printf("here! we do %s\n",v->town);

	int cnt = 0;
	while(head!=NULL){
		if(head->island_number == v->island_number){
			cnt++;
			head->current_distance = INT_MAX;
			head->set = 0;
		}
		head = head->next;	
	}

	int heap[cnt];
	struct vertex **p = malloc(sizeof(struct vertex*)*cnt);
	int end = 0;
//	heap[0] = 0;
//	p[0] = v;
	v->set = 1;
	v->set_distance = 0;
	
	for(int i=0;i<cnt;i++){
		int f = 0;
		int d = v->set_distance;
		struct neighbor *tmp = v->start;
		while(tmp!=NULL){
			if(tmp->value->set!=1 && (d+(tmp->weight))<tmp->value->current_distance){
				push(heap,p,d+(tmp->weight),tmp->value,end,cnt);
				end++;
				f++;
			}
			tmp = tmp->next;
		}
		v = extract(heap,p,end,cnt);
		end--;
	}		


	head = tmph;
	int d = 0;
	while(head!=NULL){
		if(head->island_number == v->island_number){
//			printf("%s %d",head->town,head->set_distance);
			d += head->set_distance;
		}
		head = head->next;	
	}
	return d;
	printf("\nhere!  %s wit %d\n",v->town,d);
	
	
}


int comparator(const void *p, const void *q){ 
	char *l = ((struct vertex *)p)->town; 
	char *r = ((struct vertex *)q)->town;  
	return strcmp(l,r); 
} 


int main(){
	int v;
	int e;
	scanf("%d %d",&v,&e);

	struct vertex *head = malloc(sizeof(struct vertex));
	for(int i=0;i<e;i++){
		char *o = malloc(sizeof(char)*20);
		char *d = malloc(sizeof(char)*20);
		int w;
		scanf("%s %s %d",o,d,&w);		
		insert(&head,o,d,w);
	}
	is = 0;
	
	split(&head);
//	while(head!=NULL){
//		printf("%s(%d) -->",head->town,head->island_number);
//		struct neighbor *tmp = head->start;
//
//		while(tmp!=NULL){
//			printf("%s-->",tmp->town);
//			tmp = tmp->next;
//		}
//		printf("\n");
//		head = head->next;
//	}

	int min_distance[is];
	for(int i=0;i<is;i++)
		min_distance[i] = INT_MAX-10;
	struct vertex **capital = malloc(sizeof(struct vertex*)*is);
	struct vertex *tmp = head;
	while(tmp!=NULL){
		printf("\n mindist \n");
		for(int i=0;i<is;i++)
			printf("%d-->",min_distance[i]);
		int d = dijkstra(&head,&tmp);
		if(min_distance[(tmp->island_number)-1]>d){
			min_distance[tmp->island_number-1] = d;
			capital[tmp->island_number-1] = tmp;
		}
		else if(min_distance[tmp->island_number-1]==d){
			if(strcmp(tmp->town,(capital[tmp->island_number-1])->town)<0){
				min_distance[tmp->island_number-1] = d;
				capital[tmp->island_number-1] = tmp;
			}
		}
		tmp = tmp->next;
	}

	int size = sizeof(capital) / sizeof(capital[0]); 
	qsort((void*)capital, is, sizeof(capital[0]), comparator); 
	printf("Result \n");
	for(int i=0;i<is;i++)
		printf("%s\n",(capital[i])->town);	
	return 0;
}
