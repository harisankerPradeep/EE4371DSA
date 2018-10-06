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
	int added_in_heap;
};
int is = 0;

void insert(struct vertex **h,char *o,char *d, int w){
	struct vertex *head = *h;

	if(head->town==NULL){
		head->town = malloc(20);
		strcpy(head->town,o);

		struct neighbor *n = malloc(sizeof(struct neighbor));
		n->town = malloc(20+1);
		strcpy(n->town,d);
		n->weight = w;
		head->start = n;
		head->end = n;

		struct vertex *ne = malloc(sizeof(struct vertex));
		ne->town = malloc(20+1);
		strcpy(ne->town,d);

		n = malloc(sizeof(struct neighbor));
		n->town = malloc(20+1);
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
			n->town = malloc(20+1);
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
			n->town = malloc(20+1);
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
			head->town = malloc(20+1);
			strcpy(head->town,o);

			struct neighbor *n = malloc(sizeof(struct neighbor));
			n->town = malloc(20+1);
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
			head->town = malloc(20+1);
			strcpy(head->town,d);

			struct neighbor *n = malloc(sizeof(struct neighbor));
			n->town = malloc(20+1);
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

		head->town = malloc(20+1);
		strcpy(head->town,o);

		struct neighbor *n = malloc(sizeof(struct neighbor));
		n->town = malloc(20+1);
		strcpy(n->town,d);
		n->weight = w;
		head->start = n;
		head->end = n;

		struct vertex *ne = malloc(sizeof(struct vertex));
		ne->town = malloc(20+1);
		strcpy(ne->town,d);

		n = malloc(sizeof(struct neighbor));
		n->town = malloc(20+1);
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

void set_isn(struct vertex *h,int isn){
	if(h->island_number!=0)
		return;
	h->island_number = isn;
	//printf("setting %s to %d\n",h->town,h->island_number);
	struct neighbor *tmp = h->start;
	while(tmp!=NULL){
		set_isn(tmp->value,isn);
		tmp = tmp->next;
	}
}
void push(int *heap,struct vertex **p,int w,struct vertex *v,int end,int cnt){
	heap[end] = w;
	p[end] = v;

	int i = end;
	while(i>0){
		int j = (i-1)/2;
		if(heap[j]>heap[i]){
			int tmp = heap[i];
			heap[i] = heap[j];
			heap[j] = tmp;

			struct vertex *t = p[i];
			p[i] = p[j];
			p[j] = t;
			i = j;
		}
		else
			break;

	}

	printf("pushing... %s \n",v->town);
	for(i=0;i<end+1;i++)
		printf("(%d %s)",heap[i],p[i]->town);
	printf("\n");
}
void replace(int *heap,struct vertex **p,int w,struct vertex *v,int end,int cnt){
	int i = 0;
	for(i=0;i<end;i++)
		if(strcmp(p[i]->town,v->town)==0)
			break;

	heap[i] = w;
	p[i] = v;

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

	printf("replacing... %s \n",v->town);
	for(i=0;i<end;i++)
		printf("(%d %s)",heap[i],p[i]->town);
	printf("\n");
}
struct vertex* extract(int *heap, struct vertex **p,int end,int cnt){
	struct vertex *v = p[0];
	v->set = 1;
	v->set_distance = heap[0];
	heap[0] = heap[end-1];
	p[0] = p[end-1];

	int i = 0;
	while(i<(end-1)){
		if(((2*i)+1)<(end-1) && heap[((2*i)+1)]<heap[i]&&((2*i)+2)<(end-1)&& heap[((2*i)+2)]<heap[i]){
			if(heap[(2*i)+1]<heap[(2*i)+2]){
				int tmp = heap[i];
				heap[i] = heap[((2*i)+1)];
				heap[((2*i)+1)] = tmp;

				struct vertex *t = p[i];
				p[i] = p[((2*i)+1)];
				p[((2*i)+1)] = t;
				i = (2*i)+1;
			}
			else{
				int tmp = heap[i];
				heap[i] = heap[(2*i)+2];
				heap[(2*i)+2] = tmp;

				struct vertex *t = p[i];
				p[i] = p[(2*i)+2];
				p[(2*i)+2] = t;
				i = (2*i)+2;
			}

		}
		else if(((2*i)+1)<(end-1) && heap[((2*i)+1)]<heap[i]){
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


	printf("extracting.. (%s,%d) \n",v->town,v->set_distance);
	for(i=0;i<end-1;i++)
		printf("(%d %s)",heap[i],p[i]->town);
	printf("\n");

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
			head->set_distance = INT_MAX;
			head->set = 0;
			head->added_in_heap = 0;
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
				if(tmp->value->added_in_heap==0){
					push(heap,p,d+(tmp->weight),tmp->value,end,cnt);
					end++;
					f++;
					tmp->value->added_in_heap=1;
					tmp->value->current_distance = d+(tmp->weight);
				}
				else{
					printf(" %d is replacing %d\n",d+(tmp->weight),tmp->value->current_distance);
					replace(heap,p,d+(tmp->weight),tmp->value,end,cnt);
					tmp->value->current_distance = d+(tmp->weight);

				}
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
			printf("%s %d",head->town,head->set_distance);
			d += head->set_distance;
		}
		head = head->next;	
	}
	return d;
//	printf("\nhere!  %s wit %d\n",v->town,d);
	
	
}

int cmpr(const void *a, const void *b) { 
	 return strcmp(*(char **)a, *(char **)b);
}

int main(){
	int v;
	int e;
	scanf("%d %d",&v,&e);

	struct vertex *head = malloc(sizeof(struct vertex));
	struct vertex *tmph = head;
	for(int i=0;i<e;i++){
		char *o = malloc(sizeof(char)*20);
		char *d = malloc(sizeof(char)*20);
		int w;
		scanf("%s %s %d",o,d,&w);		
		insert(&head,o,d,w);
	}
	is = 0;
	
	
	while(head!=NULL){
//		printf("set_isn of %s \n",head->town);
		if(head->island_number==0){
			set_isn(head,++is);
		}
		head = head->next;
	}
	head = tmph;
	while(head!=NULL){
		printf("%s(%d) -->",head->town,head->island_number);
		struct neighbor *tmp = head->start;

		while(tmp!=NULL){
			printf("%s-%d->",tmp->town,tmp->weight);
			tmp = tmp->next;
		}
		printf("\n");
		head = head->next;
	}
	head = tmph;
	int min_distance[is];
	for(int i=0;i<is;i++)
		min_distance[i] = INT_MAX;
	struct vertex **capital = malloc(sizeof(struct vertex*)*is);
	struct vertex *tmp = head;
	while(tmp!=NULL){
		int d = dijkstra(&head,&tmp);
		printf("finished dijkstras of %s isn %d  with %d\n",tmp->town,tmp->island_number,d);
		printf("new calculated = %d; existing =%d \n",d,min_distance[(tmp->island_number)-1]);
		if(min_distance[(tmp->island_number)-1]>d){
			min_distance[tmp->island_number-1] = d;
			capital[tmp->island_number-1] = tmp;
			printf("capital replacement of island %d with %s",tmp->island_number,tmp->town);
		}
		else if(min_distance[tmp->island_number-1]==d){
			if(strcmp(tmp->town,(capital[tmp->island_number-1])->town)<0){
				min_distance[tmp->island_number-1] = d;
				capital[tmp->island_number-1] = tmp;
				printf("capital replacement of island %d with %s",tmp->island_number,tmp->town);
			}
		}
		tmp = tmp->next;
	}
//	printf("Result \n");
	char **capital_names = malloc(sizeof(char *)*is);
	for(int i=0;i<is;i++){
		capital_names[i] = capital[i]->town;
//		printf("%s\n",(capital_names[i]));	
	}
	qsort(capital_names, is, sizeof(char *), cmpr);
	printf("Result \n");
	for(int i=0;i<is;i++)
		printf("%s\n",(capital_names[i]));	
	return 0;
}
