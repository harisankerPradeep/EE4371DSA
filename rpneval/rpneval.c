#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Node{
	float val;
	struct Node *child;
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
//	printf("popped %.4f\n",(tmp)->val);
	return (tmp)->val;
}
struct Node* push(struct Node* head,float a){//head = push;
	struct Node *tmp = malloc(sizeof(struct Node));
	tmp->val = a;
	tmp->child = head;
	head = tmp;
//	printf("pushed %.4f\n",head->val);
	return head;
}
void solve(char s[]){
	const char delim[2] = " ";
	char *token = strtok(s,delim);
	struct Node *head = malloc(sizeof(struct Node));
	int cnt = 0;
	while(token != NULL){
		
		if(cnt==0){
			head->val = (float)atoi(token);
//			printf("Here%s\n ",token);
			token = strtok(NULL,delim);
			cnt++;
			continue;
		}
		if (strcmp(token,"+")==0 || strcmp(token,"-")==0 || strcmp(token,"*")==0 || strcmp(token,"/")==0){
			float b = pop(&head);
			float a = pop(&head);
			if(strcmp(token,"+")==0)
				head = push(head,(float)(a+b));
			if(strcmp(token,"-")==0)
				head = push(head,(float)(a-b));
			if(strcmp(token,"*")==0)
				head = push(head,(float)(a*b));
			if(strcmp(token,"/")==0)
				if(b!=0)
					head = push(head,(float)(a/b));
				else{
					printf("ERROR\n");
					return;
				}

		}
		else{
			float a = (float) atoi(token);
			head = push(head,a);
		}
		token = strtok(NULL,delim);
		cnt++;
		
	}
	printf("%.4f\n",pop(&head));
}
int main(){
	char a[256];
	while (fgets(a, 256, stdin)) {
		a[strcspn(a,"\r\n")] = 0;
		char *tmp = malloc(sizeof(strlen(a)+1));
		strcpy(tmp,a);
		int l = check(a);
		if(l==1)
			solve(tmp);
	}
}
