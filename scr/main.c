#include<unistd.h>
#include<stdlib.h>
#include <pthread.h>
#include"quick_sort.h"
#include"queue.h"
#include<stdio.h>

/*
errors:
-11 неправильное количество аргументов
-121 ошибка при считывании высоты матрицы (лишние символы)
-122 -||- для длины матрицы 
-123 -||- для элементов матрицы
-124 -||- для высоты окна
-125 -||- длины окна
-126 -||- количество повторов
-13 лишние символы
-14 неожиданный конец файла
-15 неправильные размеры окна
-21 нехватка места для матрицы
-22 нехватка места для буффера
-23 ошибка в потоке
-24 нехватка памяти для буфера 
-25 нехватка памяти для аргументов
*/

struct thread_args{
		int * line, **b;// working line and buffer
		int i, j;// coordinates of element in matrix
		int h,l;//window hight and length
};
int filter(thread_args& t){
//	printf("%d\n", t.h*t.l-1);
	quick_sort(t.line, 0, t.h*t.l-1);
	t.b[t.i][t.j]=t.line[t.h*t.l/2];
	free(t.line);
	free(&t);
	return 0;
}
int main(int argc, char**argv){
	if(argc!=2){ 
		write(STDOUT_FILENO, "Wrong number of arguments.\n",sizeof("Wrong number of arguments.\n") ); 
		return -11;
	}
	char buffer;
	do{
		if(read(STDIN_FILENO, &buffer, sizeof(char)) == 0){
					return -14;
				}
	}while(buffer==' ' || buffer=='\n');
	int matrix_hig=0;
	write(STDOUT_FILENO, "Input hight of matrix.\n",sizeof("Input hight of matrix.\n") ); 
	while(buffer<='9'&&buffer>='0'){
		matrix_hig=matrix_hig*10+buffer-'0';
		if(read(STDIN_FILENO, &buffer, sizeof(char)) == 0){
			return -14;
		}	
	}
	if(matrix_hig==0){
		write(STDOUT_FILENO, "Wrong input.\n",sizeof(char)*12 ); 
		while(read(STDIN_FILENO, &buffer, sizeof(char))!=0 && buffer!='\n');
		return -121;
	}
	if(buffer!=' ' && buffer!='\n'){
		write(STDOUT_FILENO, "Wrong input.\n",sizeof(char)*12 ); 
		while(read(STDIN_FILENO, &buffer, sizeof(char))!=0 && buffer!='\n');
		return -13;
	}
	int matrix_len=0;
	write(STDOUT_FILENO, "Input lenght of matrix.\n",sizeof("Input lenght of matrix.\n") ); 
	while(buffer==' ' || buffer=='\n'){
		if(read(STDIN_FILENO, &buffer, sizeof(char)) == 0){
					return -14;
				}
	}
	while(buffer<='9'&&buffer>='0'){
		matrix_len=matrix_len*10+buffer-'0';
		if(read(STDIN_FILENO, &buffer, sizeof(char)) == 0){
					return -14;
				}
	}
	if(matrix_len==0){
		write(STDOUT_FILENO, "Wrong input.\n",sizeof(char)*12 ); 
		while(read(STDIN_FILENO, &buffer, sizeof(char))!=0 && buffer!='\n');
		return -122;
	}
	if(buffer!=' ' && buffer!='\n'){
		write(STDOUT_FILENO, "Wrong input.\n",sizeof(char)*12 ); 
		while(read(STDIN_FILENO, &buffer, sizeof(char))!=0 && buffer!='\n');
		return -13;
	}
	int k=0, minus=0; 
	int **matrix=(int **)malloc(sizeof(int*)*matrix_hig);
	if(matrix==NULL){
		free(matrix);
		write(STDOUT_FILENO, "Cant malloc matirx.\n",sizeof("Cant malloc matirx.\n") ); 
		return -21;
	}
	write(STDOUT_FILENO, "Input matrix.\n",sizeof("Input matrix.\n") ); 
	
	for(int i=0; i<matrix_hig; ++i){ 
		matrix[i]=(int*) malloc(sizeof(int)*matrix_len);
		if(matrix[i]==NULL){
			for(int j=0; j<i; ++j) free(matrix[j]);
			free(matrix);
			write(STDOUT_FILENO, "Cant malloc matirx.\n",sizeof("Cant malloc matirx.\n") ); 
			return -21;
		}
	}
	for(int i=0; i<matrix_hig; ++i){
		for(int j=0; j<matrix_len; ++j){
			k=0; minus=0;
			while(buffer==' ' || buffer=='\n'){
				if(read(STDIN_FILENO, &buffer, sizeof(char)) == 0){
					for(int i=0; i<matrix_hig; ++i) free(matrix[i]);
					free(matrix);
					return -14;
				}
			}
			if(buffer=='-'){
				minus=1;
				if(read(STDIN_FILENO, &buffer, sizeof(char)) == 0){
					for(int i=0; i<matrix_hig; ++i) free(matrix[i]);
					free(matrix);
					return -14;
				}
			}
			while(buffer<='9'&&buffer>='0'){
				k=k*10+buffer-'0';
				if(read(STDIN_FILENO, &buffer, sizeof(char)) == 0){
					for(int i=0; i<matrix_hig; ++i) free(matrix[i]);
					free(matrix);
					return -14;
				}
			}
			if(minus) k*=-1;
			if(buffer!=' ' && buffer!='\n'){
				write(STDOUT_FILENO, "Wrong input.\n",sizeof(char)*12 ); 
				while(read(STDIN_FILENO, &buffer, sizeof(char))!=0 && buffer!='\n');
				for(int i=0; i<matrix_hig; ++i) free(matrix[i]);
				free(matrix);
				return -13;
			}
			matrix[i][j]=k;
		}
	}
	if(buffer!=' ' && buffer!='\n'){
		write(STDOUT_FILENO, "Wrong input.\n",sizeof(char)*12 ); 
		while(read(STDIN_FILENO, &buffer, sizeof(char))!=0 && buffer!='\n');
		for(int i=0; i<matrix_hig; ++i) free(matrix[i]);
		free(matrix);
		return -13;
	}
	int window_hig=0;
	write(STDOUT_FILENO, "Input hight of window.\n",sizeof("Input hight of window.\n") ); 
	while(buffer==' ' || buffer=='\n'){
		if(read(STDIN_FILENO, &buffer, sizeof(char)) == 0){
			for(int i=0; i<matrix_hig; ++i) free(matrix[i]);
			free(matrix);
			return -14;
		}
	}
	while(buffer<='9'&&buffer>='0'){
		window_hig=window_hig*10+buffer-'0';
		if(read(STDIN_FILENO, &buffer, sizeof(char)) == 0){
			for(int i=0; i<matrix_hig; ++i) free(matrix[i]);
			free(matrix);
			return -14;
		}
	}
	if(window_hig==0){
		write(STDOUT_FILENO, "Wrong input.\n",sizeof(char)*12 ); 
		while(read(STDIN_FILENO, &buffer, sizeof(char))!=0 && buffer!='\n');
		for(int i=0; i<matrix_hig; ++i) free(matrix[i]);
		free(matrix);
		return -124;
	}
	if(buffer!=' ' && buffer!='\n'){
		write(STDOUT_FILENO, "Wrong input.\n",sizeof(char)*12 );
		while(read(STDIN_FILENO, &buffer, sizeof(char))!=0 && buffer!='\n'); 
		for(int i=0; i<matrix_hig; ++i) free(matrix[i]);
		free(matrix);
		return -13;
	}
	int window_len=0;
	write(STDOUT_FILENO, "Input length of window.\n",sizeof("Input length of window.\n") ); 
	while(buffer==' ' || buffer=='\n'){
		if(read(STDIN_FILENO, &buffer, sizeof(char)) == 0){
			for(int i=0; i<matrix_hig; ++i) free(matrix[i]);
			free(matrix);
			return -14;
		}
	}
	while(buffer<='9'&&buffer>='0'){
		window_len=window_len*10+buffer-'0';
		if(read(STDIN_FILENO, &buffer, sizeof(char)) == 0){
			for(int i=0; i<matrix_hig; ++i) free(matrix[i]);
			free(matrix);
			return -14;
		}
	}
	if(window_len==0){
		write(STDOUT_FILENO, "Wrong input.\n",sizeof(char)*12 ); 
		while(read(STDIN_FILENO, &buffer, sizeof(char))!=0 && buffer!='\n');
		for(int i=0; i<matrix_hig; ++i) free(matrix[i]);
		free(matrix);
		return -125;
	}
	if(buffer!=' ' && buffer!='\n'){
		write(STDOUT_FILENO, "Wrong input.\n",sizeof(char)*12 ); 
		while(read(STDIN_FILENO, &buffer, sizeof(char))!=0 && buffer!='\n');
		for(int i=0; i<matrix_hig; ++i) free(matrix[i]);
		free(matrix);
		return -13;
	}
	int repits=0;
	write(STDOUT_FILENO, "Input number of repits.\n",sizeof("Input number of repits.\n") ); 
	while(buffer==' ' || buffer=='\n'){
		if(read(STDIN_FILENO, &buffer, sizeof(char)) == 0){
			for(int i=0; i<matrix_hig; ++i) free(matrix[i]);
			free(matrix);
			return -14;
		}
	}
	while(buffer<='9'&&buffer>='0'){
		repits=repits*10+buffer-'0';
		if(read(STDIN_FILENO, &buffer, sizeof(char)) == 0){
			break;
		}
	}
	if(repits==0){
		write(STDOUT_FILENO, "Wrong number of repits.\n",sizeof("Wrong number of repits.\n") ); 
		while(read(STDIN_FILENO, &buffer, sizeof(char))!=0 && buffer!='\n');
		for(int i=0; i<matrix_hig; ++i) free(matrix[i]);
		free(matrix);
		return -126;
	}
	if(matrix_hig<window_hig || matrix_len<window_len){
		write(STDOUT_FILENO, "Wrong size of window.\n",sizeof("Wrong size of window.\n") ); 
		while(read(STDIN_FILENO, &buffer, sizeof(char))!=0 && buffer!='\n');
		for(int i=0; i<matrix_hig; ++i) free(matrix[i]);
		free(matrix);
		return -15;
	}
//==================================================================	
	pthread_t* thread;
	queue threads;
	threads.create(atoi(argv[1]));
	int **m_buffer=(int **)malloc(sizeof(int*)*matrix_hig);
	if(m_buffer==NULL){
		for(int i=0; i<matrix_hig; ++i) free(matrix[i]);
		free(matrix);
		write(STDOUT_FILENO, "Cant malloc buffer.\n",sizeof("Cant malloc buffer.\n") ); 
		return -22;
	}
	for(int i=0; i<matrix_hig; ++i){ 
		m_buffer[i]=(int*) malloc(sizeof(int)*matrix_len);
		if(m_buffer[i]==NULL){
			for(int j=0; j<i; ++j) free(m_buffer[j]);
			free(m_buffer);
			for(int i=0; i<matrix_hig; ++i) free(matrix[i]);
			free(matrix);
			write(STDOUT_FILENO, "Cant malloc buffer.\n",sizeof("Cant malloc buffer.\n") ); 
			return -22;
		}
	}
	for(int i=0; i<matrix_hig; ++i) for(int j=0; j<matrix_len; ++j){
		if(!(i>=window_hig/2 && i<matrix_hig-window_hig+window_hig/2+1) || !(j>=window_len/2 && j<matrix_len-window_len+window_len/2+1) ) m_buffer[i][j]=matrix[i][j];
	}
	thread_args* t;
	int *check=(int*) malloc(sizeof(int));
	if(check==NULL){
		write(STDOUT_FILENO, "Cant malloc buffer.\n",sizeof("Cant malloc buffer.\n") );
		for(int j=0; j<matrix_hig; ++j) free(m_buffer[j]);
		free(m_buffer);
		for(int i=0; i<matrix_hig; ++i) free(matrix[i]);
		free(matrix);
		return -24;
	}
					
	int i=window_hig/2; int j=window_len/2;
	for(int k=0; k<repits; ++k){
		for(int i=window_hig/2; i<matrix_hig-window_hig+window_hig/2+1; ++i){
			for(int j=window_len/2; j<matrix_len-window_len+window_len/2+1; ++j){
				if(threads.size()==threads.max_size()){
				//wait threads 
					pthread_t* n =threads.pop();
					pthread_join(*(n), (void**) &check);
					free(n);
					if(*check!=0){
						write(STDOUT_FILENO, "Error in thread.\n",sizeof("Error in thread.\n"));
						while(threads.size()>0) pthread_join(*(threads.pop()), (void**) &check);
						for(int j=0; j<matrix_hig; ++j) free(m_buffer[j]);
						free(m_buffer);
						for(int i=0; i<matrix_hig; ++i) free(matrix[i]);
						free(matrix);
						return -23;
					}
				}
				int pos; pos=0;
				int* line=(int*)malloc(sizeof(int)*window_hig*window_len);
				if(line==NULL){
					write(STDOUT_FILENO, "Cant malloc line buffer.\n",sizeof("Cant malloc line buffer.\n"));
					while(threads.size()>0) pthread_join(*(threads.pop()), (void**) &check);
					for(int j=0; j<matrix_hig; ++j) free(m_buffer[j]);
					free(m_buffer);
					for(int i=0; i<matrix_hig; ++i) free(matrix[i]);
					free(matrix);
					return -24;
				}
				for(int ii=i-window_hig/2; ii<i+window_hig-window_hig/2; ++ii)
					for(int jj=j-window_len/2; jj<j+window_len-window_len/2; ++jj) line[pos++]=matrix[ii][jj];
				thread=(pthread_t*) malloc(sizeof(pthread_t));
				t=( thread_args*) malloc(sizeof(thread_args));
				if(t==NULL){
					write(STDOUT_FILENO, "Cant malloc thread argumens.\n",sizeof("Cant malloc thread argumens.\n"));
					while(threads.size()>0) pthread_join(*(threads.pop()), (void**) &check);
					for(int j=0; j<matrix_hig; ++j) free(m_buffer[j]);
					free(m_buffer);
					for(int i=0; i<matrix_hig; ++i) free(matrix[i]);
					free(matrix);
					return -25;
				}
				t->line=line;
				t->b=m_buffer;
				t->i=i;
				t->j=j;
				t->h=window_hig;
				t->l=window_len;
				if(pthread_create(thread, NULL, (void* (*) (void*))filter, (void*) t)!=0){
					write(STDOUT_FILENO, "Error in thread.\n",sizeof("Error in thread.\n"));
					while(threads.size()>0){ 
						pthread_t* n =threads.pop();
						pthread_join(*(n), NULL);
						free(n);
					}
					for(int j=0; j<matrix_hig; ++j) free(m_buffer[j]);
					free(m_buffer);
					for(int i=0; i<matrix_hig; ++i) free(matrix[i]);
					free(matrix);
					return -23;
				}
				threads.push(thread);
			}
			while(threads.size()>0){
				pthread_t* n =threads.pop();
				pthread_join(*(n), NULL);
				free(n);
				if(*check!=0){
					write(STDOUT_FILENO, "Error in thread.\n",sizeof("Error in thread.\n"));
					while(threads.size()>0) pthread_join(*(threads.pop()), (void**) &check);
					for(int j=0; j<matrix_hig; ++j) free(m_buffer[j]);
					free(m_buffer);
					for(int i=0; i<matrix_hig; ++i) free(matrix[i]);
					free(matrix);
					return -23;
				}
			}
		}
		int **tmp=m_buffer;
		m_buffer=matrix;
		matrix=tmp;
	} 
	for(int i=0; i<matrix_hig; ++i){ for(int j=0; j<matrix_len; ++j) printf("%d ", matrix[i][j]); printf("\n"); }
//====================================================================
	free(check);
	threads.destroy();
	for(int i=0; i<matrix_hig; ++i) free(m_buffer[i]);
	free(m_buffer);
	for(int i=0; i<matrix_hig; ++i) free(matrix[i]);
	free(matrix);
	return 0;
		
}
