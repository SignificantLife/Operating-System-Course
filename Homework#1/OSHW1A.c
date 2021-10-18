#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>

int ElemntCount(int ary[],int startIndex,int endIndex,int key){
    int count=0;
    for(int i=startIndex;i<endIndex;i++){
        if(ary[i]==key)
            count++;
    }
    return count;
}


int main(int argc,char *argv[]){
    
    int ArraySize;

    printf("Enter the Array Length :");
    scanf("%d",&ArraySize);
    int MyArray[ArraySize];
    

    for(int i=0;i<255;i++){
        MyArray[i]=rand()%50;
    }
    
    int size=sizeof(MyArray)/sizeof(MyArray[0]);


    int key;
    printf("Enter the number(0-49) that you want to search:");
    scanf("%d",&key);

    int startIndex=0,endIndex=255;
    int TotalCount=0;

    struct timeval start,end;

    gettimeofday(&start,NULL);

    TotalCount=ElemntCount(MyArray,startIndex,endIndex,key);
    printf("Integer %d occurs %d times in the array\n",key,TotalCount);

    gettimeofday(&end,NULL);

    long seconds=(end.tv_sec - start.tv_sec);
    long micros=((seconds*1000000)+end.tv_usec)-(start.tv_usec);

    printf("Single Process ------------------- \n");
    printf("Array Length is %d \n",size);
    printf("The execution time is %ld seconds and %ld micros\n", seconds, micros);
    return 0;
}