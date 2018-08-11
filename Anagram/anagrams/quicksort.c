#include "include/add.h"
void quicksort(char **a,int start,int end){

	int i=start,j=start,k=0;
//	printf("Call _ \n");

	char *pivot = a[end-1];
	if(start>=end){
		return;
	}
	printf("before sort\n");
	for(int k=start;k<end;k++){
	printf("%s,",a[k]);
	}
	printf("\n");
	//i is the pointer for lesser than pivot
	//j is the pointer for greater than pivot
	for(k=start;k<end-1;k++){
		if(strcmp(a[k],pivot)>0){
			continue;}
		if(strcmp(a[k],pivot)<=0){
			char *tmp = a[j];
			a[j] = a[k];
			a[k] = tmp;
			j++;
			i++;
		}
	}
	printf("befor swap\n");
	for(int k=start; k<end;k++){
		printf("%s,",a[k]);
	}
	printf("\n");
	if(i+1 != end){
		char *tmp = a[i];
		a[i] = a[end-1];
		a[end-1] = tmp;
		printf("swapped %s,%s",tmp,a[i]);
	}
	else{
		quicksort(a,start,i);
		return;
	}

	printf("\n%s,%s,%s\n",a[i+1],a[j],pivot);	
	printf("after sort\n");
	for(int k=start; k<end;k++){
		printf("%s,",a[k]);
	}
	printf("\n");
	quicksort(a,start,i);
	quicksort(a,i+1,end);
}
int main(){
	//printf("Here!");	
	int N;
	char **input;
	scanf("%d",&N);
	input = (char **)malloc(N * sizeof(char*));
	if(input == NULL){
		printf("Allocation problem");
		exit(0);
	}
	for(int i = 0; i<N;i++){
		input[i] = (char *)malloc(31 * sizeof(char));
		scanf("%s",input[i]);
		printf("%s\n",input[i]);
	}
	quicksort(input, 0, N );
	printf("\n\n");
	for(int k=0;k<N;k++){
		printf("%s,\n",input[k]);
	}
}
