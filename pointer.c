#include <stdio.h>

int main(){
	int c[10][10];
	int i,j;
	for(i = 0;i<10;i++){
		for(j = 0;j<10;j++){
			c[i][j] = i*j;
			//printf("%d\t",c[i][j]);
		}
		//printf("\n");
	}	

	int* a = c;
	int b = 25;
	//a = c;
	printf("%p,%p\n",++a,a);
	
}
