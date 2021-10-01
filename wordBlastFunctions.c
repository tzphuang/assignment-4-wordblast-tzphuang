/**************************************************************
* Class:  CSC-415-03 Fall 2021
* Name: Tony Huang
* Student ID: 915090688
* GitHub ID: tzphuang
* Project: Assignment 4 – Word Blast
*
* File: wordBlastFunctions.c
*
* Description: Program features many functions needed to run and maintain a linked node list
* 
*
**************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>

#include "wordBlastFunctions.h"

struct node {
   char* word;
   int count;
   struct node *next;
};

static struct node *head = NULL; //head node of the linked node list
static struct node *current = NULL;

//mutex lock created and initialized so we know the state of it
pthread_mutex_t myMutexLock = PTHREAD_MUTEX_INITIALIZER;

void insertNewWord(char* newWord) {
   //printf("inside insertNewWord\n");
   

   bool checker = isWordInArray(newWord); //returns word count or -1 if newWord isnt in the linkedlist

   if(checker){ 
      //else the newWord being inserted is already in the linkedlist 
      //instead of making a new node, increment the word instead
      incrementCount(newWord);
   }
   else{
      //newWord is not in the list so create a node for it 
      //create a link
      struct node *link = (struct node*) malloc(sizeof(struct node));
      
      link->word = newWord;

      //int startingInt = 1;
      //link->count = &startingInt;
      link->count = 1;
      
      pthread_mutex_lock(&myMutexLock);
         
      //point it to old first node
      link->next = head;
      
      //point first to new first node
      head = link;

      pthread_mutex_unlock(&myMutexLock);
   }
   
}

bool isEmpty() {
   return head == NULL;
}

//gets count for searched word in linked list
int getCount(char* searchWord) {
   //printf("inside getCount\n");

   if(head == NULL) {
      return -1;
   }
   
   if(isWordInArray(searchWord)){ //if searchWord is in the array
      struct node* current;
      for(current = head; current != NULL; current = current->next) 
      {
         if(0 == strcmp(current->word, searchWord)){
            return current->count;
         }
      }
   }
}

void incrementCount(char* searchWord){ 
   //printf("inside incrementNewWord\n");
   
   //if list is empty
   if(head == NULL) {
      return;
   }

   if(isWordInArray(searchWord)){ //if searchWord is in the array
      struct node* current;
      for(current = head; current != NULL; current = current->next) 
      {
         if(0 == strcmp(current->word,searchWord)){
            current->count = current->count + 1;
            return;
         }
      }
   }

}

bool isWordInArray(char* searchWord){
   //printf("inside isWordInArray\n");
   int compareInt;
   struct node *current;
	
   //transverses the linkedlist comparing
   for(current = head; current != NULL; current = current->next) {
      compareInt = strcmp(current->word,searchWord);
      if(compareInt == 0){
         
         return true;
      }
   }
   return false;
}

//gets the length of the array of nodes
int getLength() {
   //printf("inside getLength\n");
   int length = 0;
   struct node *current;
	
   for(current = head; current != NULL; current = current->next) {
      length++;
   }
	
   return length;
}


void sort() {
   //printf("inside sort\n");

   int i, j, k;
   char* tempWord;
   int tempKey;
   struct node *current;
   struct node *next;
	
   int size = getLength();
   k = size ;
	
   for ( i = 0 ; i < size - 1 ; i++, k-- ) {
      current = head;
      next = head->next;
		
      for ( j = 1 ; j < k ; j++ ) {   

         if ( current->count < next->count ) { //this sort comparison produces greatest to least
            //current->count > next->count ----- this sort comparison produces least to greatest
            tempWord = current->word;
            current->word = next->word;
            next->word = tempWord;

            tempKey = current->count;
            current->count = next->count;
            next->count = tempKey;
         }
			
         current = current->next;
         next = next->next;
      }
   }   
}

//display the list
void printList() {
   //printf("inside printList\n");
   struct node *currNode = head;
	
   //start from the beginning
   while(currNode != NULL) {
      printf("The current word: %15s, and count :%4d\n",currNode->word ,currNode->count);
      currNode = currNode->next;
   }
	
}

//void fillArrayList(char* bufferedString){
void *fillArrayList(void * bufferedString){
   //printf("inside fillArrayList\n");
   char* delim = "\"\'.“”‘’?:;-,—*($%)! \t\n\x0A\r";
   char* token;
   //concatenating void * ptr to char * as I know it is a char *
   char* savePtr = (char *) bufferedString; 

   while ((token = strtok_r(savePtr, delim, &savePtr))){
      if(6 <= strlen(token)){//for strings with 6 character or more
         //printf("inserting token %s\n", token);
         //pthread_mutex_lock(&myMutexLock);
         
         insertNewWord(token);
         
         //pthread_mutex_unlock(&myMutexLock);
      } 
   }

}

void printTopTen(){
   int topTen = 10;

   if(isEmpty()){
      printf("LinkedList was empty returning from PrintTopTen.\n");
      return;
   }

   int lengthOfArray = getLength();
   if(topTen > lengthOfArray){ //checks if the array is less than topTen to insure that function
                               //doesnt later break itself with the printf for loop
      topTen = lengthOfArray;
   }


   struct node *currNode = head;
	
   printf("Printing top %d words 6 characters or more.\n", topTen);
   for(int count = 1; count <= topTen; count++){
      printf("Number %d is %s with a count of %d\n",count ,currNode->word ,currNode->count);
      currNode = currNode->next;
   }
}
