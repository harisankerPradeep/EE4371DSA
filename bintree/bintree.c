#include <stdio.h>
#include <stdlib.h>

struct Node{
	int val;
	struct Node* left;
	struct Node* right;
};
void insert(struct Node* head,int x){
	if (x>(head->val)){
		if (head->right == NULL){
			struct Node* new = malloc(sizeof(struct Node*));
			(new->val) = x;
			(head->right) = new;
		}
		else
			insert(head->right,x);
	}
	else{
		if(head->left == NULL){
			struct Node* new = malloc(sizeof(struct Node*));
			new->val = x;
			(head->left) = new;
		}
		else
			insert(head->left,x);
	}
}
void inorder(struct Node* head){
	if(head->left!=NULL)
		inorder((head->left));
	printf("%d\n",head->val);
	if(head->right!=NULL)
		inorder((head->right));
}
void preorder(struct Node* head){
	printf("%d\n",head->val);
	if(head->left!=NULL)
		preorder((head->left));
	if(head->right!=NULL)
		preorder((head->right));
}
void postorder(struct Node* head){
	if(head->left!=NULL)
		postorder((head->left));
	if(head->right!=NULL)
		postorder((head->right));
	printf("%d\n",head->val);
}
int main() 
{
	// Read in the number of values in array as first entry
	int N;
	scanf("%d", &N);
	struct Node* head = malloc(sizeof(struct Node*));
	int x ;
	// Read in the data
	for (int i=0; i<N; i++) {
		scanf("%d", &x);
		if(i==0){
			head->val = x;
			continue;
		}
		insert(head,x);
	}
	inorder(head);
	preorder(head);
	postorder(head);
	return 0;
}
