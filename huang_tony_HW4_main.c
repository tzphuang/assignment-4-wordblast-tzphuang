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

    /*
    //Using stat structure to find how many bytes in file
    struct stat fileInfo;
    stat(argv[1], &fileInfo);
    int sizeOfFile = fileInfo.st_size; //st_size: Total size, in bytes 
    printf("Size of argv[1] file: %s is size: %d\n", argv[1], sizeOfFile);
    */


    //read in file in reference to string stored in argv[1]
    int currentFileDescriptor;
    currentFileDescriptor = open(argv[1], O_RDONLY);
  
	if(currentFileDescriptor == -1)
	{
		printf("Failed to open and read Argv[1]");
		exit(1);
	}

    //using lseek to find size of my file

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

    //**************************************************************
    // DO NOT CHANGE THIS BLOCK
    //Time stamp start
    struct timespec startTime;
    struct timespec endTime;

    clock_gettime(CLOCK_REALTIME, &startTime);
    //**************************************************************
    // *** TO DO ***  start your thread processing
    //                wait for the threads to finish
    

    // ***TO DO *** Process TOP 10 and display

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
    close(currentFileDescriptor);

    return 0;
    }
