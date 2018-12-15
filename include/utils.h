#ifndef __UTILS_H__
#define __UTILS_H__

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "./textstorage.h"
#include "./frequency_dict.h"


////////////////////////////////////////////////////////////
// METHODS DECLARATION
////////////////////////////////////////////////////////////

int TextCountNum(FILE*);
Text* TextRead(FILE*);
int strinclude(char* str, char* substr);

////////////////////////////////////////////////////////////
// METHODS DEFINITION
////////////////////////////////////////////////////////////

int TextCountNum(FILE* input)
{
    char cCharBuf;
    char cStrBuf[20];
    int cursor = 0;
    while (1)
    {
        cCharBuf = fgetc(input);
        if (!isdigit(cCharBuf)) break;
        cStrBuf[cursor++] = cCharBuf;
    }
    cStrBuf[cursor] = '\0';
    return atoi(cStrBuf);
}

Text* TextRead(FILE* input)
{
    Text* text = TextInit();
    char cCharBuf;
    char cStrBuf[100];
    int nStrCursor = 0;

    while (!feof(input))
    {
        cCharBuf = fgetc(input);
        if (isalpha(cCharBuf)) cStrBuf[nStrCursor++] = cCharBuf;
        else
        {
            cStrBuf[nStrCursor] = '\0';
            if (nStrCursor) TextAddWord(text, cStrBuf);
            nStrCursor = 0;
        }
        cStrBuf[nStrCursor + 1] = '\0';
    }

    return text;
}

void TextWordPrint(Text* text)
{
    TextWord* pWord = text->firstWord;
    while (pWord)
    {
        printf("%s \n", pWord->word);
        pWord = pWord->next;
    }
}

void TextWordWrite(Text* text, FILE* output)
{
    TextWord* pWord = text->firstWord;
    while (pWord)
    {
        fprintf(output, "%s \n", pWord->word);
        pWord = pWord->next;
    }
}

FreqDict* DictRead(FILE* dict)
{
    FreqDict* dictionary = DictInit();
    char cCharBuf;
    char cStrBuf[100];
    int nStrCursor = 0;

    while (!feof(dict))
    {
        cCharBuf = fgetc(dict);
        if (cCharBuf != '\n') cStrBuf[nStrCursor++] = cCharBuf;
        else
        {
            cStrBuf[nStrCursor] = '\0';
            if (nStrCursor) DictAddWord(dictionary, cStrBuf);
            nStrCursor = 0;
        }
        cStrBuf[nStrCursor + 1] = '\0';
    }

    return dictionary;
}

void DictWrite(FreqDict* dict, FILE* output)
{
    DictElem* pElem = dict->firstWord;
    while (pElem)
    {
        fprintf(output, "%s \n", pElem->word);
        pElem = pElem->next;
    }
}

void CountWordFrequency(FILE* output, FreqDict* dict, Text* text, int num)
{
    int dictWordCnt = dict->wordCnt; DictElem* pElem = dict->firstWord;
    int textWordCnt = text->length; TextWord* pWord = text->firstWord;
    int opCnt = 0; char firstChar_prev = '\0'; char firstChar_curr;
    FreqList* freqList = ListInit();

    while (pElem)
    {
        opCnt++;
        if (opCnt % 10000 == 0) printf("Currently processing %d / %d \n", opCnt, dictWordCnt);
        while (pWord)
        {
            if (strinclude(pWord->word, pElem->word)) pElem->frequency++;
            pWord = pWord->next;
        }
        pWord = text->firstWord;
        pElem = pElem->next;
    }

    pElem = dict->firstWord;
    int nonzeroCnt = 0;
    while (pElem)
    {
        if (pElem->frequency)
        {
            ListInsertSort(freqList, pElem);
            nonzeroCnt++;
        }
        pElem = pElem->next;
    }
    printf("# of Nonzeroes: %d \n", nonzeroCnt);

    int idx; int maxIter = ((freqList->wordCnt < num) ? freqList->wordCnt : num);
    int idxBuf; char* cpBuf;
    for (idx = 0; idx < maxIter; idx++)
    {
        cpBuf = freqList->list[idx]->word;
        idxBuf = freqList->list[idx]->frequency;
        printf("%s %d \n", cpBuf, idxBuf);
        // fprintf(output, "%s %d \n", cpBuf, idxBuf);
    }
    int currentFreq = freqList->list[idx - 1]->frequency;
    for (; idx < freqList->wordCnt && freqList->list[idx]->frequency == currentFreq; idx++)
    {
        cpBuf = freqList->list[idx]->word;
        idxBuf = freqList->list[idx]->frequency;
        printf("%s %d \n", cpBuf, idxBuf);
        // fprintf(output, "%s %d \n", cpBuf, idxBuf);
    }
}

int strinclude(char* str, char* substr)
{
    int str_len = strlen(str);
    int substr_len = strlen(substr);
    // printf("Testing if  [ %15s ] includes [ %15s ]: ", str, substr);
    if (str_len < substr_len)
    {
        // printf("Not included. \n");
        return 0;
    }
    
    int idx;
    int str_cursor = 0;
    int substr_cursor = 0;
    for (idx = 0; idx < str_len - substr_len + 1; idx++)
    {
        str_cursor = idx;
        substr_cursor = 0;
        while (str[str_cursor] == substr[substr_cursor] || 
               str[str_cursor] - substr[substr_cursor] == 'A' - 'a' ||
               str[str_cursor] - substr[substr_cursor] == 'a' - 'A')
        {
            if (substr[substr_cursor + 1] == '\0')
            {
                // printf("Included! \n");
                return 1;
            }
            substr_cursor++; str_cursor++;
        }
    }
    // printf("Not included. \n");
    return 0;
}

#endif