#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>


struct Task{
	int R;
	int T;
	int D;
	int set;
	int parent;
	int time_left;
	int failed;
	int added_to_heap;
	int heap_pos;
	int process_number;
};

//variable noting end pos of heap
int end = 0;
void extract(int *heap, int *p, struct Task **tasks){//to extract min from heap
	if(end==1){
		end--;
		return;
	}
	if(end<1){
		return;
	}
	// Move the last element of the heap to the first position
	p[0] = p[end-1];
	heap[0] = heap[end-1];
	tasks[p[end-1]]->heap_pos = 0;
	heap[end-1] = INT_MAX;
	end--;
	int i=0;
	while(i<end){
		int a = (2*i)+1;
		int b = (2*i)+2;
		if(a>end || b>end)
			break;
		if(heap[i]>heap[a] && heap[i]>heap[b]){
			if(heap[a]<=heap[b]){
				double tmp = heap[a];
				heap[a] = heap[i];
				heap[i] = tmp;

				int t = p[i];
				p[i] = p[a];
				p[a] = t;
				tasks[p[i]]->heap_pos = i;
				tasks[p[a]]->heap_pos = a;

				i = a;
			}
			else{
				double tmp = heap[b];
				heap[b] = heap[i];
				heap[i] = tmp;

				int t = p[i];
				p[i] = p[b];
				p[b] = t;
				tasks[p[i]]->heap_pos = i;
				tasks[p[b]]->heap_pos = b;

				
				i = b;
			}
		}
		else if(heap[i]>heap[a] && heap[i]<=heap[b]){
			double tmp = heap[a];
			heap[a] = heap[i];
			heap[i] = tmp;

			int t = p[i];
			p[i] = p[a];
			p[a] = t;
			tasks[p[i]]->heap_pos = i;
			tasks[p[a]]->heap_pos = a;


			i = a;
		}
		else if(heap[i]>heap[b] && heap[i]<=heap[a]){
			double tmp = heap[b];
			heap[b] = heap[i];
			heap[i] = tmp;

			int t = p[i];
			p[i] = p[b];
			p[b] = t;
			tasks[p[i]]->heap_pos = i;
			tasks[p[b]]->heap_pos = b;


			i = b;
		}
		else{
			break;
		}

	}
}
void add(int *heap, int *p, struct Task **tasks, int dst, double d){//to add values to heap
	heap[end] = d;	
	p[end] = dst;
	tasks[dst]->heap_pos = end;
	int i = end;
       	end++;
	while(i>0){
		int a = (i-1)/2;
		if(heap[a]>heap[i]){
			double tmp = heap[a];
			heap[a] = heap[i];
			heap[i] = tmp;

			int t = p[a];
			p[a] = p[i];
			p[i] = t;
			tasks[p[a]]->heap_pos = a;
			tasks[p[i]]->heap_pos = i;
			
			i = a;
		}
		else{
			break;
		}
	}
	tasks[dst]->added_to_heap = 1;	
}
void replace(int *heap, int *p, struct Task **tasks, int dst, double d){//To update values in the heap
	int i = tasks[dst]->heap_pos;
	heap[i] = d;	
	while(i>0){
		int a = (i-1)/2;
		if(heap[a]>heap[i]){
			double tmp = heap[a];
			heap[a] = heap[i];
			heap[i] = tmp;

			int t = p[a];
			p[a] = p[i];
			p[i] = t;
			tasks[p[i]]->heap_pos = i;
			tasks[p[a]]->heap_pos = a;

			i = a;
		}
		else{
			break;
		}
	}
}
int comparator(const void *p, const void *q){
	struct Task *a = *(struct Task**)p;
	struct Task *b = *(struct Task**)q;
	int l = a->R; 
	int r = b->R;  
	return (l - r); 
} 
int main(){

	int n;
	scanf("%d",&n);
	struct Task **tasks = malloc(sizeof(struct Task*)*(n));
	int start_time = INT_MAX;
	int last_entry = 0;
	for(int i = 0;i<n; i++){
		int r,t,d;
		tasks[i] = malloc(sizeof(struct Task));
		scanf("%d %d %d",&r,&t,&d);	
		tasks[i]->R = r;
		tasks[i]->T = t;
		tasks[i]->D = d;
		tasks[i]->time_left = t;
		tasks[i]->process_number = i+1;
		if(r<start_time)
			start_time = r;
		if(last_entry<r)
			last_entry = r;
	}
	qsort((void*)tasks, n, sizeof(struct Task*), comparator); 	

	int cnt = 0;
	int *p = malloc(sizeof(int)*n);
	int *heap = malloc(sizeof(int)*n);
	for(int i=0;i<n;i++){
		p[i] = INT_MAX;
		heap[i] = INT_MAX;
	}
	int f = 0;
	end = 0;
	// Starting from start_time for each second;
	for(int i=start_time; i<=last_entry; i++){
		//Add newly arrived processes.
		while(1){
			if(cnt>=n || tasks[cnt]->R != i)
				break;
			int d = tasks[cnt]->T;
//			for(int j=0;j<end;j++)
//				printf("before add%d %d\n",heap[j],p[j]);
			add(heap,p,tasks,cnt,d);
//			for(int j=0;j<end;j++)
//				printf("after%d %d\n",heap[j],p[j]);
			cnt++;
		}
		//Extract the process with shortest time left to complete	
		while(1){
			if(end==0)
				break;
			int pos = p[0];
			struct Task *t = tasks[pos];
			if(t->time_left+i>t->D){
				t->failed = 1;
				if(end==0){
					heap[0] = INT_MAX;
					p[0] = INT_MAX;
					break;
				}
//				for(int j=0;j<end;j++)
//					printf("before extract in failed %d %d\n",heap[j],p[j]);
				extract(heap,p,tasks);
//				for(int j=0;j<end;j++)
//					printf("after %d %d\n",heap[j],p[j]);

				continue;
			}
			t->time_left--;
			if(t->time_left==0){
//				for(int j=0;j<end;j++)
//					printf("before extract%d %d\n",heap[j],p[j]);
				extract(heap,p,tasks);
//				for(int j=0;j<end;j++)
//					printf("after %d %d\n",heap[j],p[j]);
//				printf("timeleft = 0\n");
				printf("%d %d %d\n",i,i+1,t->process_number);
				break;
			}
			else{
				replace(heap,p,tasks,pos,t->time_left);
				printf("%d %d %d \n",i,i+1,t->process_number);
				break;
			}
		}
		
	}
	int time = last_entry+1;
	f=0;
	while(end>0){
		int pos = p[0];
		extract(heap,p,tasks);
		struct Task *t = tasks[pos];
		printf("%d %d %d\n",time,time+t->time_left,t->process_number);
		time += t->time_left;
	}
	for(int i=0;i<n;i++){
		struct Task *t = tasks[i];
		if(t->failed){
			printf("%d %d %d\n",time,time+t->time_left,t->process_number);
			f++;
			time += t->time_left;
		}
	}	
}

