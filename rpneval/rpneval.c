#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Node{
	float val;
	struct Node* child;
};
int check(char a[]){
	int cnt = 0;		
	char *token = strtok(a," ");
	while(token != NULL){
		if (strcmp(token,"+")==0 || strcmp(token,"-")==0 || strcmp(token,"*")==0 || strcmp(token,"/")==0)
			cnt = cnt -1;
		else
			cnt++;
		if(cnt<=0){
			printf("ERROR\n");
			return 0;
		}
		token = strtok(NULL," ");
	}
	if(cnt==1)
		return 1;
	else{
		printf("ERROR\n");
		return 0;
	}
}
float pop(struct Node** head){
	struct Node *tmp = *head;
	*head = ((*head)->child);
	printf("popped %f \n",(tmp)->val);
	return (tmp)->val;
}
struct Node* push(struct Node* head,float a){//head = push;
	struct Node *tmp = malloc(sizeof(struct Node));
	tmp->val = a;
	tmp->child = head;
	head = tmp;
	printf("pushed %f\n",a);
	return head;
}

void solve(char s[]){
	const char delim[1] = " ";
	char* token; 
	char* rest = s; 
	struct Node *head = malloc(sizeof(struct Node));
	int cnt = 0;
	while((token = strtok_r(rest, " ", &rest))){
		struct Node* tmp = head;
		printf("token = %s\n",token);
		if(cnt>0){
		while(tmp!=NULL){
			printf("%f -->",tmp->val);
			if(tmp->child!=NULL){
				tmp = (tmp->child);
			}
			else{
				printf("\n");
				break;}
		}}
		if(cnt==0){
			head->val = (float)atof(token);
			head->child = NULL;
			cnt++;
			continue;
		}
		if (strcmp(token,"+")==0 || strcmp(token,"-")==0 || strcmp(token,"*")==0 || strcmp(token,"/")==0){
			float b = pop(&head);
			float a = pop(&head);
			printf("%f %s %f \n",a,token,b);
			if(strcmp(token,"+")==0)
				head = push(head,(a+b));
			if(strcmp(token,"-")==0)
				head = push(head,(a-b));
			if(strcmp(token,"*")==0)
				head = push(head,(a*b));
			if(strcmp(token,"/")==0)
				if(b!=0)
					head = push(head,(a/b));
				else{
					printf("ERROR\n");
					return;
				}
		}
		else{
			float a = atof(token);
			head = push(head,a);
		}
		cnt++;
		printf("\n");

	}
	printf("%.4f\n",pop(&head));
}
int main(){
	char a[300];
	while (fgets(a, 300, stdin)) {
		a[strcspn(a,"\r\n")] = 0;
		char *tmp = malloc(sizeof(strlen(a)+1));
		strcpy(tmp,a);
		int l = check(a);
		if(l==1)
			solve(tmp);
	}
}
