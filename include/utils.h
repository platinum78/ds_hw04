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

Text* TextRead(FILE*);

////////////////////////////////////////////////////////////
// METHODS DEFINITION
////////////////////////////////////////////////////////////

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

void CountWordFrequency(FreqDict* dict, Text* text)
{
    int dictWordCnt = dict->wordCnt; DictElem* pElem = dict->firstWord;
    int textWordCnt = text->length; TextWord* pWord = text->firstWord;
    int opCnt = 0; char firstChar_prev = '\0'; char firstChar_curr;

    while (pElem)
    {
        opCnt++;
        if (opCnt % 10000 == 0) printf("Currently processing %d / %d \n", opCnt, dictWordCnt);
        while (pWord)
        {
            if (strstr(pWord->word, pElem->word)) pElem->frequency++;
            pWord = pWord->next;
        }
        pWord = text->firstWord;
        pElem = pElem->next;
    }

    pElem = dict->firstWord;
    int nonzeroCnt = 0;
    while (pElem)
    {
        if (pElem->frequency) nonzeroCnt++;
        pElem = pElem->next;
    }
    printf("# of Nonzeroes: %d \n", nonzeroCnt);
}

#endif