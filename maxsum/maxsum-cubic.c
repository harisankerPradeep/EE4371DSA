#include <stdio.h>
#include <stdlib.h>

/*int maxsumCubic(int *x, int N) 
{
    int maxsum = 0;
    for (int i=0; i<N; i++) {
        for (int j=i; j<N; j++) {
            int thissum = 0;
            for (int k=i; k<=j; k++) {
                thissum += x[k];
            }
            if (thissum > maxsum) {
                maxsum = thissum;
                // printf("%d: %d %d\n", maxsum, i, j);
            }
        }
    }
    return maxsum;
}*/
int maxsumCubic(int *x, int N) 
{
	int start = 0;
	int end = N-1;
	for(int i = 0; i<N; i++)
		if(x[i]>0){
			start = i;
			break;
		}
	for(int i = N-1; i>=0; i--)
		if(x[i]>0){
			end = i;
			break;
		}
	int max_sum = 0;
	int sum = 0;
	for(int i= start; i<= end; i++){
		sum += x[i];
		if(sum>max_sum)
			max_sum = sum;
		if(sum<0)
			sum = 0;
	}
	return max_sum;
}

int main() 
{
    // Read in the number of values in array as first entry
    int N;
    scanf("%d", &N);
    int *x = malloc(sizeof(int)*N); 

    // Read in the data
    for (int i=0; i<N; i++) {
        scanf("%d", &x[i]);
    }

    // Compute the max subsequence sum
    int maxsum = maxsumCubic(x, N);
    printf("%d\n", maxsum);

    return 0;
}
