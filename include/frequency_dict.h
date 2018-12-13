#ifndef __FREQUENCY_H__
#define __FREQUENCY_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

////////////////////////////////////////////////////////////
// STRUCTURES DEFINITION
////////////////////////////////////////////////////////////

typedef struct DictElem_
{
    char* word;
    int frequency;
    struct DictElem_* next;
} DictElem;

typedef struct FreqDict_
{
    DictElem* lookupTable[52][53];
    int wordCnt;
} FreqDict;


////////////////////////////////////////////////////////////
// METHODS DECLARATION
////////////////////////////////////////////////////////////

FreqDict* DictInit();
void DictAddWord(FreqDict*, char*, int);
DictElem* DictFindWord(FreqDict*, char*);
int LexiCompare(char*, char*);

////////////////////////////////////////////////////////////
// METHODS DEFINITION
////////////////////////////////////////////////////////////

FreqDict* DictInit()
{
    FreqDict* pDict = (FreqDict*)malloc(sizeof(FreqDict));
    int first, second;
    for (first = 0; first < 52; first++)
        for (second = 0; second < 53; second++)
            pDict->lookupTable[first][second] = NULL;
    pDict->wordCnt = 0;
    return pDict;
}

// Add word to dictionary
void DictAddWord(FreqDict* dict, char* buf, int len)
{
    DictElem* pElem = (DictElem*)malloc(sizeof(DictElem));

    // Get the indices of first and second character
    int firstCharIdx = ((buf[0] >= 'A' && buf[0] <= 'Z') ? buf[0] - 'A' :  ((buf[0] >= 'a' && buf[0] <= 'z') ? buf[0] - 'a' : -1));
    int secondCharIdx = 52;
    if (len > 1) int secondCharIdx = ((buf[0] >= 'A' && buf[0] <= 'Z') ? buf[0] - 'A' :  ((buf[0] >= 'a' && buf[0] <= 'z') ? buf[0] - 'a' : -1));
    
    // Get the pointer for head
    DictElem* pHead = dict->lookupTable[firstCharIdx][secondCharIdx];
    DictElem* pElem, pNext;
    if (pHead)
    {
        pElem = pHead;
        while (LexiCompare())
    }
}

// Find word from dictionary
DictElem* DictFindWord(FreqDict* dict, char* query)
{
    int queryLen = strlen(query);
    int cursor;

    for (cursor = 0; cursor < queryLen; cursor++)
    {
        // If met NULL character, skip that word, since the word is ended already.
    }
}

// Compare two words in lexicographical order
int LexiCompare(char* str1, char* str2)
{
    int idx = 0;
    while (str1[idx] == str2[idx]) idx++;
    if (str1[idx] < str2[idx]) return 1;
    else return -1;
}


#endif