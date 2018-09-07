#include <stdio.h>
#include <stdlib.h>

typedef int d_t;

void swap(d_t& x, d_t& y)
{
    d_t t = x;
    x = y;
    y = t;
}

d_t kthmin(d_t *x, int k, int left, int right)
{
    return -100000; // replace with correct code
}

int main(int argc, char **argv)
{
    // Read in the number of values in array as first entry
    int N;
    scanf("%d", &N);
    int *x = new int[N];

    // Read in the data
    for (int i=0; i<N; i++) {
        scanf("%d", &x[i]);
    }

    int k = atoi(argv[1]);
    if ((k<1) || (k > N)) {
        printf("ERROR: k out of bounds\n");
        exit(1);
    }
    int res = kthmin(x, k-1, 0, N-1);
    printf("%d\n", res);
  
    return 0;
}