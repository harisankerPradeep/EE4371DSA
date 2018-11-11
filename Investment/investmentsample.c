#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

//Don't forget explanations

int main () {
	int t,n,f;
	double s;
	scanf("%lf\n",&s);
	scanf("%d\n",&t);
	scanf("%d\n",&n);
	scanf("%d\n",&f);
	double **r = malloc(sizeof(double *)*n);
	for(int i=0;i<t;i++){
		r[i] = malloc(sizeof(double)*n);
		char a[10000];
		scanf ("%[^\n]%*c", a);
		char* token = strtok(a, " ");
		int j=0;
		while (token) {
			r[i][j++] = (double)atof(token);
			token = strtok(NULL, " ");
		}
	}
	
// 	Initialy invest all money in the plan that has max returns on year 1
	double current = s;
	double rmax = r[0][0];
	double rcur = rmax;
	int pos = 0;
	for(int i=0;i<n;i++){
		if(r[0][i]>rmax){
			rmax = r[0][i];		
			rcur = rmax;
			pos = i;
		}
	}
	for(int i=0;i<n;i++){
		if(i!=pos)
			printf("0 ");
		else
			printf("%lf ",current);
	}
//	printf(" current r %lf\n",rcur);
	printf("\n");
	current = current * rcur;
// For subsequent years	
	for(int	i=1;i<t;i++){
		rmax = r[i][0];
		int p = 0,flag = 0;
		for(int j=0;j<n;j++){
			if(r[i][j]>rmax){
				p = j;
				rmax = r[i][j];
			}
		}
		rcur = r[i][pos];
		if((current*rcur)<((current-f)*rmax)){
			rcur = rmax;
			pos = p;
			current = current - f;
		}
		
		for(int j=0;j<n;j++){
			if(j!=pos)
				printf("0 ");
			else
				printf("%lf ",current);
		}
//		printf(" current r %lf\n",rcur);
		printf("\n");
		current = current * rcur;
	}	
}
