#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//below for system call for linux to open files
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

//blew for sytem call for close to close files
#include <unistd.h>
#include <stdbool.h>

#include "wordBlastFunctions.h"

int main(void) {

  //@~@~@~read~@~@~@
  int currentFileDescriptor;
  currentFileDescriptor = open("WarAndPeace.txt", O_RDONLY);
  
	if(currentFileDescriptor == -1)
	{
		printf("Failed to open and read DecOfInd.txt");
		exit(1);
	}

  int bufferSize = 4000002;
	char buffer[bufferSize];
  char* bufPtr = buffer;
  int totalBytesReadFromFile = 4000000;
  bufPtr[totalBytesReadFromFile] = '\0';

	read(currentFileDescriptor, bufPtr, totalBytesReadFromFile);

  //printf("%s\n",bufPtr);
  fillArrayList(bufPtr);
  sort();
  //printList();
  printTopTen();

  close(currentFileDescriptor);
  
  return 0;
}
