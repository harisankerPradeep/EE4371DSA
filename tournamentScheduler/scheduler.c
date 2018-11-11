#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
//Based on SO answer by Chris Osaki (https://stackoverflow.com/questions/6648512/scheduling-algorithm-for-a-round-robin-tournament)
//Number the teams 1..n. (Here I'll take n=8.)
//
//Write all the teams in two rows.
//
//1 2 3 4
//8 7 6 5
//
//The columns show which teams will play in that round (1 vs 8, 2 vs 7, ...).
//
//Now, keep 1 fixed, but rotate all the other teams. In week 2, you get
//
//1 8 2 3
//7 6 5 4
//
//and in week 3, you get
//
//1 7 8 2
//6 5 4 3
//
//This continues through week n-1, in this case,
//
//1 3 4 5
//2 8 7 6

int main(){
	int n,m;
	scanf("%d",&n);
	scanf("%d",&m);

	int *a = malloc(sizeof(int)*(n/2));
	int *b = malloc(sizeof(int)*(n/2));
	int *c = malloc(sizeof(int)*(n-1)*2);
	//Rotation matrix
	for(int i=0;i<n-1;i++){
		c[i] = i+2;
		c[n-1+i] = i+2;
	}
	a[0]=1;
	for(int i=0;i<m;i++){
		for(int j=0;j<n/2;j++)
			b[j] = c[(2*n)-3-i-j];
		for(int j=1;j<n/2;j++)
			a[j] = c[n-2+j-i];
	       	for(int j=0;j<n/2;j++)
			printf("%d %d\n",a[j],b[j]);	
	}

}
