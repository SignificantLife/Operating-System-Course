#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/time.h>


int counter;
pthread_mutex_t lock;

int loop=-1;
int startIndex,endIndex;
int key;  
int ArraySize;
int threads;

void* trythis(void* re_arr)
{
	pthread_mutex_lock(&lock);

    int *arr=(int *)re_arr;
    int count=0;

	unsigned long i = 0;
	counter += 1;
	printf("\n Job %d has started\n", counter);

    int threadLoop=++loop;
    startIndex=threadLoop*(ArraySize/threads);
    endIndex=startIndex+(ArraySize/threads);
	 for(i = startIndex;i < endIndex;i++) {
        if(arr[i]==key)
            count++;
    }
	
    printf("\n Job %d has finished\n", counter);
	pthread_mutex_unlock(&lock);

	return count;
}

int main(void)
{
	//Input Array Length
    //int ArraySize;
    printf("Enter the Array Length :");
    scanf("%d",&ArraySize);
    int MyArray[ArraySize];


    //Generate Array
    for(int i=0;i<ArraySize;i++){
        MyArray[i]=rand()%50;
    }
    
    //Make Sure the Array Length
    int size=sizeof(MyArray)/sizeof(MyArray[0]);


    //Input Number of Threads
    printf("Enter the number of threads :");
    scanf("%d",&threads);

    //input value
    //int key;
    printf("Enter the number(0-49) that you want to search:");
    scanf("%d",&key);


    int TotalCount=0;
    
    int i = 0;
	int error;

    pthread_t tid[threads];


	if (pthread_mutex_init(&lock, NULL) != 0) {
		printf("\n mutex init has failed\n");
		return 1;
	}

    //execution time
    struct timeval start,end;
	gettimeofday(&start,NULL);
    while (i < threads) {
		error = pthread_create(&(tid[i]),NULL,&trythis, (void *)MyArray);
		if (error != 0)
			printf("\nThread can't be created :[%s]",
				strerror(error));
		i++;
	}

    for(int i=0;i<threads;i++){
        int returnValue;
        pthread_join(tid[i], &returnValue); // 等待子執行緒執行完成
        TotalCount+=returnValue;
    }

	pthread_mutex_destroy(&lock);
    gettimeofday(&end,NULL);
    long seconds=(end.tv_sec - start.tv_sec);
    long micros=((seconds*1000000)+end.tv_usec)-(start.tv_usec);

    printf("Multi-Thread(with mutex) ------------------- \n");
    printf("Array Length is %d \n",size);
    printf("Number of Threads is %d \n",threads);
    printf("Integer %d occurs %d times in the array\n",key,TotalCount);
    printf("The execution time is %ld seconds and %ld micros\n", seconds, micros);

	return 0;
}
