#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
	printf("here %s %s \n",head->town,head->next->end->value->town);		
	while(head!=NULL){
		printf("%s(%d) -->",head->town,head->island_number);
		struct neighbor *tmp = head->start;

		while(tmp!=NULL){
			printf("%s-->",tmp->town);
			tmp = tmp->next;
		}
		printf("\n");
		head = head->next;
	}

	return 0;
}
