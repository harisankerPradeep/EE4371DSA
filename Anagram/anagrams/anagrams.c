#include "include/add.h"
void swap(char *a, char *b){
	if(!a || !b)
	    return;
	char temp = *(a);
	*(a) = *(b);
	*(b) = temp;
}
void swapString(char *str1, char *str2){
	char *temp = (char *)malloc((strlen(str1) + 1) * sizeof(char));
	strcpy(temp, str1);
	strcpy(str1, str2);
	strcpy(str2, temp);
	free(temp);
}
void quicksort(char a[],int start,int end){
	int i=start,j=start,k=0;
	char pivot = a[end-1];
	if(start>=end){
		return;
	}
	for(k=start;k<end-1;k++){
		if(a[k]>pivot){
			continue;}
		if(a[k]<=pivot){
			swap(&a[j],&a[k]);
			j++;
			i++;
		}
	}
	if(i+1 != end){
		swap(&a[i],&a[end-1]);
	}
	else{
		quicksort(a,start,i);
		return;
	}
	quicksort(a,start,i);
	quicksort(a,i+1,end);
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
	char **sortd = malloc(N * sizeof(char*));
	for(int i = 0; i<N;i++){
		input[i] = malloc(31 * sizeof(char));
		scanf("%s",input[i]);
		char tmp[31];
		strcpy(tmp,input[i]);	
		quicksort(tmp,0,strlen(tmp));
		sortd[i] = malloc(31*sizeof(char));
		strcpy(sortd[i],tmp);
	}
	int *count = malloc(N*sizeof(int));
	int *flags = malloc(N*sizeof(int));	
	int fpt = 0;
	int total_count = 0;
	for(int i=0;i<N;i++){
		for(int j=i+1;j<N;j++){
			if(strcmp(sortd[i],sortd[j])==0){
				count[i]++;
//				printf("%s,%s \n",input[j],input[i]);				
				if(flags[i] == 0){
					fpt++;
					flags[j] = fpt;
					flags[i] = fpt;
					total_count++;
				}
				else{
					if(flags[j] == 0){
						flags[j] = flags[i];
					}
				}
				if(strcmp(input[j],input[i])<0){
					swapString(input[i],input[j]);
				}
			}
			else{
				if(strcmp(input[j],input[i])<0){
//					printf("swapping for sorting %s,%s \n",input[j],input[i]);				
//					swapString(input[i],input[j]);
//					swapString(sortd[i],sortd[j]);
//					int tmp = flags[i];
//					flags[i] = flags[j];
//					flags[j] = tmp;
//					tmp  = count[i];
//					count[i] = count[j];
//					count[j] = tmp;
				}
			}
		}

	}

	printf("%d",total_count);
	int *done = malloc(total_count*sizeof(int));
	for(int i=0;i<N;i++){
		if(flags[i] == 0)
			continue;
		if(done[flags[i]] == 1)
			continue;
		printf("\n%d\n%s",count[i]+1,input[i]);
		for(int j=i+1;j<N;j++){
			if(flags[j] == flags[i]){
				printf("\n%s",input[j]);
				done[flags[i]] = 1;
			}
		}
	}
	printf("\n");
	return 0;
}
