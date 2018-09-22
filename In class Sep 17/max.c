#include <stdio.h>
#include <stdlib.h>

int main() 
{
    // Read in the number of values in array as first entry
    int N = 9999990;
    scanf("%d", &N);
    int *x = malloc(sizeof(int)*N); 

    // Read in the data
    int index = 1;
    for (int i=0; i<N; i++) {
		
        scanf("%d", &x[i]);
	if(x[i]==index)
		index++;
	else{
		printf("%d\n",index);
		index = x[i];
	}
    }

    // Compute the max subsequence sum

    return 0;
}
