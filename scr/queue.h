#ifndef __QUEUE__
#define __QUEUE__
#include<stdlib.h>
#define type pthread_t 
struct queue{
	type** arr;
	int arr_size, sizze, beg;
	int max_size(){
		return arr_size;
	}
	int create(int n){
		if(n<=0) return -2;
		arr=(type** ) malloc(sizeof(type*)*n);
		if(arr==NULL) return -1;
		beg=0;
		arr_size=n;
		sizze=0;
		return 0;
	}
	int destroy(){
		if(arr==NULL) 	return 1;
		free(arr);
		arr==NULL; return 0; 
	}
	int push(type* elem){
		if(sizze==arr_size) return -1;
		if(arr==NULL) return -2;
		arr[(beg+sizze)%arr_size]=elem;
		++sizze;
		return 0;
	}
	type* pop(){
		if(sizze!=0 && arr!=NULL){// return t{};
		type* tmp=arr[beg];
		beg=(beg+1)%arr_size;
		sizze-=1;
		return tmp;}
	}
	int size(){
		return sizze;
	}
};
#endif
