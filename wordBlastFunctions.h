/**************************************************************
* Class:  CSC-415-03 Fall 2021
* Name: Tony Huang
* Student ID: 915090688
* GitHub ID: tzphuang
* Project: Assignment 4 – Word Blast
*
* File: wordBlastFunctions.h
*
* Description: Program is the header file needed for wordBlastFunctions.c
*
**************************************************************/

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

