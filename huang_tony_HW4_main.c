/**************************************************************
* Class:  CSC-415-03 Fall 2021
* Name: Tony Huang
* Student ID: 915090688
* GitHub ID: tzphuang
* Project: Assignment 4 – Word Blast
*
* File: huang_tony_HW4_main.c
*
* Description:
*
**************************************************************/

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <pthread.h>

#include <string.h>
#include <stdbool.h>
#include "wordBlastFunctions.h"


// You may find this Useful
char * delim = "\"\'.“”‘’?:;-,—*($%)! \t\n\x0A\r";



int main (int argc, char *argv[])
    {
    //***TO DO***  Look at arguments, open file, divide by threads
    //             Allocate and Initialize and storage structures

    //read in file in reference to string stored in argv[1]
    int currentFileDescriptor;
    currentFileDescriptor = open(argv[1], O_RDONLY);
  
	if(currentFileDescriptor == -1)
	{
		printf("Failed to open and read Argv[1]");
		exit(1);
	}

    //using lseek to find size of my file in argv[1]
    int sizeOfFile;
    //seeks from 0 to the end of file and returns that offset
    sizeOfFile = lseek(currentFileDescriptor, (size_t)0, SEEK_END);
    //setting lseek pointer back to beginning of file which is 0
    lseek(currentFileDescriptor, (off_t)0, SEEK_SET);

    printf("Size of argv[1] file: %s is size: %d\n", argv[1], sizeOfFile);
    /*
    //checking to make sure my lseek went back to the beginning of the file
    char * firstFewWordsOfFile = malloc(sizeOfFile);
    read(currentFileDescriptor,firstFewWordsOfFile, 30);
    printf("First few words of file is: %s\n", firstFewWordsOfFile);
    free(firstFewWordsOfFile);*/

    //converting argv[2] which is a char* to an integer and storing inside threadCount
    char argvChar = *argv[2];
    int threadCount = argvChar - '0';
    printf("Word Frequency Count on %s with %d threads\n", argv[1], threadCount);


    //array of pointers to my strings with size of argv[2] ie: thread count
    char * readFileChunkArray[threadCount];

    //loop storing (1/thread count) of the file we have to each malloced memory
    for(int count = 0; count < threadCount; count++){
        //dynamically allocate memory to each char ptr of (size of file / number of threads)
        readFileChunkArray[count] = malloc((sizeOfFile/threadCount) + 1);

        //store each section of the file into its corresponding malloced memory
        read(currentFileDescriptor,readFileChunkArray[count], sizeOfFile/threadCount);

        //setting the last character inside the split file to null terminator '\0' 
        //so I know the string can be read properly
        readFileChunkArray[count][(sizeOfFile/threadCount) + 1] = '\0';
    }

    /*
    //checking to see if file was split correctly
    for(int count = 0; count < threadCount; count++){
        printf("File chunk number %d has length %ld\n", count, strlen(readFileChunkArray[count]));
        printf("%s\n",readFileChunkArray[count]);
    }*/

    //**************************************************************
    // DO NOT CHANGE THIS BLOCK
    //Time stamp start
    struct timespec startTime;
    struct timespec endTime;

    clock_gettime(CLOCK_REALTIME, &startTime);
    //**************************************************************
    // *** TO DO ***  start your thread processing
    //                wait for the threads to finish
    
    for(int count = 0; count < threadCount; count++){
        fillArrayList(readFileChunkArray[count]);
    }

    // ***TO DO *** Process TOP 10 and display

    sort();
    printTopTen();

    //**************************************************************
    // DO NOT CHANGE THIS BLOCK
    //Clock output
    clock_gettime(CLOCK_REALTIME, &endTime);
    time_t sec = endTime.tv_sec - startTime.tv_sec;
    long n_sec = endTime.tv_nsec - startTime.tv_nsec;
    if (endTime.tv_nsec < startTime.tv_nsec)
        {
        --sec;
        n_sec = n_sec + 1000000000L;
        }

    printf("Total Time was %ld.%09ld seconds\n", sec, n_sec);
    //**************************************************************


    // ***TO DO *** cleanup

    //for every malloc there is a corresponding free
    for(int count = 0; count < threadCount; count++){
        free(readFileChunkArray[count]);
    }

    //for every open file descriptor there is a corresponding close
    close(currentFileDescriptor);

    return 0;
    }
