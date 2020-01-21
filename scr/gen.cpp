#include<stdlib.h>
#include<ctime>
#include<stdio.h>
int main(){
	srand(time(NULL));
	int h, l;
	scanf("%d", &h);
	scanf("%d", &l);
	for(int i=0; i<h; ++i){ 
		for(int j=0; j<l; ++j) printf("%d ", rand()%100);
		printf("\n");
	}
}
