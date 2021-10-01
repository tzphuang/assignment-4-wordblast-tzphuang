#ifndef _WORDBLASTFUNCTIONS
#define _WORDBLASTFUNCTIONS


void insertNewWord(char* newWord);
bool isEmpty();
int getCount(char* searchWord);
void incrementCount(char* searchWord);
bool isWordInArray(char* searchWord);
int getLength();
void sort();
void printList();
//void fillArrayList(char* bufferedString);
void *fillArrayList(void * ptr);
void printTopTen();


#endif

