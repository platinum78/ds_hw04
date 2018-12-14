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
} FreqDict;


////////////////////////////////////////////////////////////
// METHODS DECLARATION
////////////////////////////////////////////////////////////

FreqDict* DictInit();
DictElem* WordInit(char*);
void DictAddWord(FreqDict*, char*);
DictElem* DictFindWord(FreqDict*, char*);
int LexiCompare(char*, char*);

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

// Add word to dictionary
/*
void DictAddWord_(FreqDict* dict, char* buf)
{
    // Uniqueness of each word is assumed; no preliminary search will be done.
    DictElem* pNewElem = WordInit(buf);
    // Get the indices of first and second character
    int firstCharIdx = ((buf[0] >= 'A' && buf[0] <= 'Z') ? buf[0] - 'A' :  ((buf[0] >= 'a' && buf[0] <= 'z') ? buf[0] - 'a' : -1));
    int secondCharIdx = 52;
    if (buf[1] != '\0') int secondCharIdx = ((buf[0] >= 'A' && buf[0] <= 'Z') ? buf[0] - 'A' :  ((buf[0] >= 'a' && buf[0] <= 'z') ? buf[0] - 'a' : -1));
    
    // Get the pointer for head
    DictElem* pHead = dict->lookupTable[firstCharIdx][secondCharIdx];
    DictElem* pElem; DictElem* pNext;
    if (pHead)
    {
        pElem = pHead;
        pNext = pElem->next;
        while (LexiCompare(pElem->word, buf) == 1)
        {
            // Case: inserting new word to the end
            if (pNext == NULL)
            {
                pElem->next = pNewElem;   
                break;
            }

            // Case: inserting new word in the middle
            pNewElem->next = pElem->next;
            pElem->next = pNewElem;
        }
    }
} */

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

// Find word from dictionary
/*
DictElem* DictFindWord(FreqDict* dict, char* query)
{
    // Get the indices of first and second character
    int firstCharIdx = ((query[0] >= 'A' && query[0] <= 'Z') ? query[0] - 'A' :  ((query[0] >= 'a' && query[0] <= 'z') ? query[0] - 'a' : -1));
    int secondCharIdx = 52;
    if (strlen(query) > 1) int secondCharIdx = ((query[0] >= 'A' && query[0] <= 'Z') ? query[0] - 'A' :  ((query[0] >= 'a' && query[0] <= 'z') ? query[0] - 'a' : -1));
    
    // Get the pointer in the lookup table
    DictElem* pHead = dict->lookupTable[firstCharIdx][secondCharIdx];
    DictElem* pElem = pHead; DictElem* pNext = pElem->next;
    
    // Find the word that matches the query
    int found = 0;
    int cmpCursor = 2;
    for (cmpCursor = 2; cmpCursor < strlen(query); cmpCursor++)
    {
        while (!found)
        {
            // Same character at same position
            if (query[cmpCursor] == pElem->word[cmpCursor])
            {
                if (query[cmpCursor] == '\0') found = 1;        // Terminate search if both characters are null
                else cmpCursor++;                               // Proceed to next position if not null
            }
            else if (query[cmpCursor] > pElem->word[cmpCursor])
            {
                pElem = pNext;
                pNext = pNext->next;
            }
        }
    }
} */

// Compare two words in lexicographical order
int LexiCompare(char* str1, char* str2)
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


#endif