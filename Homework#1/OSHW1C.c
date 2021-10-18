#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/time.h>


int loop=-1;
int startIndex,endIndex;
int key;    
int ArraySize;
int threads;


// 子執行緒函數
void* child(void* re_arr) {
    int *arr=(int *)re_arr;
    int count=0;
    int threadLoop=++loop;
    startIndex=threadLoop*(ArraySize/threads);
    endIndex=startIndex+(ArraySize/threads);
    for(int i = startIndex;i < endIndex;i++) {
        if(arr[i]==key)
            count++;
    }
    pthread_exit(count); // 離開子執行緒
}

int main(){

    //Input Array Length
    //int ArraySize;
    printf("Enter the Array Length :");
    scanf("%d",&ArraySize);
    int MyArray[ArraySize];

    //Input Number of Threads
    printf("Enter the number of threads :");
    scanf("%d",&threads);

    for(int i=0;i<ArraySize;i++){
        MyArray[i]=rand()%50;
    }
    
    //Make Sure the Array Length
    int size=sizeof(MyArray)/sizeof(MyArray[0]);

    printf("Enter the number(0-49) that you want to search:");
    scanf("%d",&key);

    
    pthread_t thr[threads];
    int TotalCount=0;
     //execution time
    struct timeval start,end;
    gettimeofday(&start,NULL);

    for(int i=0;i<threads;i++) {
        pthread_create(&thr[i], NULL, (void *)child, (void *)MyArray); // 建立子執行緒
    }
    for(int i=0;i<threads;i++){
        int returnValue;
        pthread_join(thr[i], &returnValue); // 等待子執行緒執行完成
        TotalCount+=returnValue;
    }
    gettimeofday(&end,NULL);
    long seconds=(end.tv_sec - start.tv_sec);
    long micros=((seconds*1000000)+end.tv_usec)-(start.tv_usec);

    printf("Multi-Thread ------------------- \n");
    printf("Array Length is %d \n",size);
    printf("Number of Threads is %d \n",threads);
    printf("Integer %d occurs %d times in the array\n",key,TotalCount);
    printf("The execution time is %ld seconds and %ld micros\n", seconds, micros);

    return 0;

}