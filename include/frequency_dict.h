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
    // DictElem* lookupTable[52][53];
    DictElem* firstWord;
    DictElem* lastWord;
    int wordCnt;
    int capacity;
} FreqDict;

typedef struct FreqList_
{
    DictElem** list;
    int wordCnt;
    int capacity;
} FreqList;


////////////////////////////////////////////////////////////
// METHODS DECLARATION
////////////////////////////////////////////////////////////

FreqDict* DictInit();
DictElem* WordInit(char*);
FreqList* ListInit();
void DictAddWord(FreqDict*, char*);
DictElem* DictFindWord(FreqDict*, char*);
int AsciiCompare(char*, char*);
int ListAddElem(FreqList*, DictElem*);

////////////////////////////////////////////////////////////
// METHODS DEFINITION
////////////////////////////////////////////////////////////

FreqDict* DictInit()
{
    FreqDict* pDict = (FreqDict*)malloc(sizeof(FreqDict));
    // int first, second;
    // for (first = 0; first < 52; first++)
    //     for (second = 0; second < 53; second++)
    //         pDict->lookupTable[first][second] = NULL;
    pDict->firstWord = pDict->lastWord = NULL;
    pDict->wordCnt = 0;
    return pDict;
}

// Initialize word struct
DictElem* WordInit(char* word)
{
    DictElem* pNewElem = (DictElem*)malloc(sizeof(DictElem));
    pNewElem->word = word;
    pNewElem->frequency = 0;
    pNewElem->next = NULL;
    return pNewElem;
}


FreqList* ListInit()
{
    FreqList* pList = (FreqList*)malloc(sizeof(FreqList));
    pList->wordCnt = 0;
    pList->capacity = 0;
    pList->list = (DictElem**)malloc(sizeof(DictElem*) * pList->capacity);
    return pList;
}

// Add word to dictionary
void DictAddWord(FreqDict* dict, char* buf)
{
    char* word = (char*)malloc(sizeof(char) * (strlen(buf) + 1));
    strcpy(word, buf);
    DictElem* pElem = WordInit(word);
    if (dict->firstWord == NULL)
    {
        dict->firstWord = pElem;
        dict->lastWord = pElem;
        dict->wordCnt++;
        return;
    }
    dict->lastWord->next = pElem;
    dict->lastWord = pElem;
    dict->wordCnt++;
    return;
}

// Compare two words in lexicographical order
int AsciiCompare(char* str1, char* str2)
{
    int idx = 0;
    while (str1[idx] == str2[idx])
    {
        if (str1[idx] == '\0') return 0;
        idx++;
    }
    if (str1[idx] < str2[idx]) return 1;
    else return -1;
}

// Add DictElem address to the frequently-used list
int ListInsertSort(FreqList* list, DictElem* elem)
{
    printf("[ %s ] has nonzero frequency. \n", elem->word);
    if (list->wordCnt)
    {
        int idx;
        for (idx = list->wordCnt - 1; idx >= 0 && list->list[idx]->frequency < elem->frequency; idx--)
            list->list[idx+1] = list->list[idx];
        for ( ; idx >= 0 && list->list[idx]->frequency == elem->frequency && AsciiCompare(list->list[idx]->word, elem->word) == -1; idx--)
            list->list[idx+1] = list->list[idx];
        list->list[idx+1] = elem;
        list->wordCnt++;
    }
    else
    {
        list->list[list->wordCnt++] = elem;
    }

    if (list->wordCnt == list->capacity)
    {
        list->capacity *= 2;
        list->list = (DictElem**)realloc(list->list, sizeof(DictElem*) * list->capacity);
    }
}


#endif