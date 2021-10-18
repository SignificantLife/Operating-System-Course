# Operating System Homework #1
## Platform
I used VS Code and the remote WSL1 extension to run the program
## Hint
The unit used for the result analysis is Microsecond （µs）
- 1 s = 1000000 µs
- 1 µs = 1.0E-6 s
The generating array is a set of integers not exceeding 50
## Program execution content 
- Find the frequency of user input values in the array（I always enter a value of 10）
- The user can decide the length of the array and the number of processes/threads
## Source code
- OSHW1A.c：Single Process
- OSHW1B.c：Multi-Process
- OSHW1C.c：Multi-Thread
- OSHW1D.c：Multi-Thread with mutex
## Single-process Terminal Command
- gcc OSHW1A.c -lpthread -Wall -std=c99 -o OSHW1A
- taskset -c 0,1,2,3,4,5,6,7 ./OSHW1A(bind the 8 logical cores of the CPU)
## Multi-process Terminal Command
- gcc OSHW1B.c -lpthread -Wall -std=c99 -o OSHW1B
- taskset -c 0,1,2,3,4,5,6,7 ./OSHW1B(bind the 8 logical cores of the CPU)
## Multi-thread Terminal Command
- gcc OSHW1C.c -lpthread -Wall -std=c99 -o OSHW1C
- taskset -c 0,1,2,3,4,5,6,7 ./OSHW1C (bind the 8 logical cores of the CPU)
## Multi-thread(with mutex) Terminal Command
- gcc OSHW1D.c -lpthread -Wall -std=c99 -o OSHW1D
- taskset -c 0,1,2,3,4,5,6,7 ./OSHW1D (bind the 8 logical cores of the CPU)
