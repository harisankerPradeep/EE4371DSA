#include "include/add.h"

int main()
{
	int N;
	scanf("%d", &N);
	for(int i=0;i<N;i++)
	{
		int a, b;
		scanf("%d\t%d", &a, &b);
		int c = a+b;
		printf("%d\n", c);
	}
	return 0;
}
