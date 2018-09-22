#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Node{
	double val;
	struct Node* child;
};
double pop(struct Node** head){
	struct Node *tmp = *head;
	*head = ((*head)->child);
	return (tmp)->val;
}
struct Node* push(struct Node* head,double a){//head = push;
	struct Node *tmp = malloc(sizeof(struct Node));
	tmp->val = a;
	tmp->child = head;
	head = tmp;
	return head;
}

void solve(char s[]){
	char* token; 
	char* rest = s; 
	struct Node *head = malloc(sizeof(struct Node));
	int cnt = 0;
	int n = 0;
	while((token = strtok_r(rest, " ", &rest))){
		struct Node* tmp = head;
		
		if(cnt==0){
			head->val = (double)atof(token);
			head->child = NULL;
			cnt++;
			n++;
			continue;
		}
		if (strcmp(token,"+")==0 || strcmp(token,"-")==0 || strcmp(token,"*")==0 || strcmp(token,"/")==0){
			n--;
			if(n<=0){
				printf("ERROR\n");
				return;
			}
			double b = pop(&head);
			double a = pop(&head);
			if(strcmp(token,"+")==0)
				head = push(head,(double)(a+b));
			if(strcmp(token,"-")==0)
				head = push(head,(double)(a-b));
			if(strcmp(token,"*")==0)
				head = push(head,(double)(a*b));
			if(strcmp(token,"/")==0)
				if(b!=0)
					head = push(head,(double)(a/b));
				else{
					printf("ERROR\n");
					return;
				}
		}
		else{
			double a = atof(token);
			head = push(head,a);
			n++;
		}
		cnt++;

	}
	if(n==1)
		printf("%.4f\n",pop(&head));
	else{
		printf("ERROR\n");
		return;
	}
}
int main(){
	char a[300];
	while (fgets(a, 300, stdin)) {
		a[strcspn(a,"\r\n")] = 0;
		solve(a);
	}
}
