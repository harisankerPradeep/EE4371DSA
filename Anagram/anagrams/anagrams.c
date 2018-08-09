#include "include/add.h"
int checkAnagram(char a[],char b[]){
		int a_count[26] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
		int b_count[26] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
		int c = 0,flag = 0;
		while(a[c] != '\0'){
			if(a[c] == '\''){
				c++;
				continue;
			}	
			a_count[a[c]-'a']++;
			c++;
		}
		c = 0;	
		while(b[c] != '\0'){
			if(b[c] == '\''){
				c++;
				continue;
			}	
			b_count[b[c]-'a']++;
			c++;
		}
		c = 0;
		while(c<26){
			if(a_count[c]!=b_count[c]){
				return 0;
			}
			c++;
		}
		return 1;
				
}
int compare(const void *a,const void *b){
	const char *pa = *(const char**)a;
	const char *pb = *(const char**)b;
	return strcmp(pa,pb);
}
struct Sibling{
	char *val;
	struct Sibling *sibling;
};
struct Node{
	char *val;
	struct Node *child;
	struct Sibling *sibling_head; 
	int sib_num;
	struct Sibling *sibling_tail;
};
int main(){
	int N;
	char **input;
	
	scanf("%d",&N);
	input = malloc(N * sizeof(char*));
	for(int i = 0; i<N;i++){
		input[i] = malloc(31 * sizeof(char));
		scanf("%s",input[i]);
	}
	qsort((void*)input, N, sizeof(input[0]), compare);
	struct Node *head = malloc(sizeof(struct Node));
	head->val = input[0];
	
	int usage[N];
	for(int i=0;i<N;i++){
		usage[i] = 0;
	}
	//printf("hello! %d",checkAnagram("acts","cast"));
	int cnt = 0;
	struct Node *prev = head;
	struct Node *node = head;
	int flag = 0;
	for(int i=0;i<N;i++){
		flag = 0;
		if(i==0){
			node = head;
		}
		else{
			if(usage[i] != 0){
				continue;
			}
			node = malloc(sizeof(struct Node));
		       	node->val = input[i];
			//printf("%s\n\n",prev->val);
			prev->child = node;
			prev = node;
		}
		for(int j=i+1;j<N;j++){
			if(usage[j]!=0){
				continue;
			}
//			printf("here! %s %s \n",input[i],input[j]);
			int result = checkAnagram(input[i],input[j]);
			if(result == 1){
				usage[j]++;
				//printf("%s,%s\n",input[i],input[j]);
				node->sib_num++;				
				if(flag==0){
					cnt++;
					flag++;
				}
				if(node->sibling_head == NULL){
					node->sibling_head = malloc(sizeof(struct Sibling));
					(node->sibling_head)->val = input[j];
					node->sibling_tail = node->sibling_head;
					continue;
				}
				struct Sibling *sib = malloc(sizeof(struct Sibling));
				sib->val = input[j];
				(node->sibling_tail)->sibling = sib;
				(node->sibling_tail) = sib;
					
			}
			else{
				continue;
			}
		}
		struct Node *prev = node;
	}
	node = head;
	printf("%d",cnt);
	while(node != NULL){
		if(node->sib_num == 0){
			node = node->child;
			continue;
		}
		printf("\n%d\n%s",(node->sib_num+1),node->val);
		struct Sibling *sib = node->sibling_head;
		while(sib != NULL){
		printf("\n%s",sib->val);
			sib = sib->sibling;
		}
		node = node->child;
	}	
	return 0;
}
