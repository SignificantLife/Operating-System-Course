#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>


int ElemntCount(int ary[],int startIndex,int endIndex,int key){
    int count=0;
    for(int i=startIndex;i<endIndex;i++){
        if(ary[i]==key)
            count++;
    }
    return count;
}

int main()
{
    //Generate the Array
    int processes;
    int ArraySize;

    printf("Enter the Array Length :");
    scanf("%d",&ArraySize);
     int MyArray[ArraySize];

    printf("Enter the number of processes :");
    scanf("%d",&processes);


    for(int i=0;i<ArraySize;i++){
        MyArray[i]=rand()%50;
    }
    
    //Array Length
    int size=sizeof(MyArray)/sizeof(MyArray[0]);
    
    int key;
    printf("Enter the number(0-49) that you want to search:");
    scanf("%d",&key);

    //Divide the Array into 5 segments ->fork()
    int startIndex,endIndex;
    int TotalCount=0;
    int l;

    //execution time
    struct timeval start,end;
    
    
    for (l = 0; l < processes; l++) {
        gettimeofday(&start,NULL);
        int pid=fork();
        if (pid< 0) {
            fprintf(stderr,"fork failed\n");
            exit(1);
        }
        else if (pid == 0) {
           startIndex=l*(size/processes);
           endIndex=startIndex+(size/processes);
           int c=ElemntCount(MyArray,startIndex,endIndex,key);
           return(c);
        }
        else {
            int status;
            wait(&status);
            TotalCount+=WEXITSTATUS(status);
        }
        gettimeofday(&end,NULL);
    }
    
    long seconds=(end.tv_sec - start.tv_sec);
    long micros=((seconds*1000000)+end.tv_usec)-(start.tv_usec);
    printf("Multi-Process ------------------- \n");
    printf("Array Length is %d \n",size);
    printf("Number of Processes is %d \n",processes);
    printf("Integer %d occurs %d times in the array\n",key,TotalCount);
    printf("The execution time is %ld seconds and %ld micros\n", seconds, micros);
    
    return 0;

}