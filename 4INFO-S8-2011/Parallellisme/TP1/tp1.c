#include <stdio.h>
#include <pthread.h>

pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex2 = PTHREAD_MUTEX_INITIALIZER;

void* do_loop(void* data){
	
	int* ptr = data;

	while(1){
		if(*ptr == 1)
			pthread_mutex_lock( &mutex1 );
		else
			pthread_mutex_lock( &mutex2 );
			
			
		printf("do_looooooooooooop %d\n", *ptr);
		
		
		if(*ptr == 1)
			pthread_mutex_unlock( &mutex2 );
		else
			pthread_mutex_unlock( &mutex1 );
	}
	
	pthread_exit(NULL);
}

int main(int argc, char* argv[]){

	int thr_id;
	pthread_t p_thread;
	int a = 1;
	int b = 2;
	pthread_attr_t attr;

	pthread_mutex_lock( &mutex1 );
	
	pthread_attr_init(&attr);
	thr_id = pthread_create(&p_thread, &attr, do_loop, (void*) &a);
	
	do_loop((void*) &b);
}
