#include <stdio.h>
#include <stdlib.h>

int main(){
	int N;
	scanf("%d",&N);
	int *start = malloc(sizeof(int)*N);
	int *duration = malloc(sizeof(int)*N);
	
	int max_time = 0;
	for(int i=0;i<N;i++){
		scanf("%d %d",&start[i],&duration[i]);
		if((start[i]+duration[i])>max_time)
			max_time = start[i]+duration[i];
	}
	int min = start[0];
	int *t = malloc(sizeof(int)*(max_time-min));
	
	int max_task=0;
	double total=0;
	for(int i=0;i<N;i++)
		for(int j=start[i];j<start[i]+duration[i];j++){
			t[j-min]++;
			total+=1;
			if(max_task<t[j-min])
				max_task = t[j-min];
		}
		
	total = total/max_time;
	printf("%d\n%d\n%.4f\n",max_time,max_task,total);
	return 0;
}
