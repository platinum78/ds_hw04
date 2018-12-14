#ifndef __TEXTSTORAGE_H__
#define __TEXTSTORAGE_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

////////////////////////////////////////////////////////////
// STRUCTURES DEFINITION
////////////////////////////////////////////////////////////

typedef struct TextWord_
{
    char* word;
    struct TextWord_* next;
} TextWord;

typedef struct Text_
{
    TextWord* firstWord;
    TextWord* lastWord;
    int length;
} Text;


////////////////////////////////////////////////////////////
// METHODS DECLARATION
////////////////////////////////////////////////////////////

Text* TextInit();
TextWord* TextWordInit(char*);
void TextAddWord(Text*, char*);


////////////////////////////////////////////////////////////
// METHODS DEFINITION
////////////////////////////////////////////////////////////

Text* TextInit()
{
    Text* pText = (Text*)malloc(sizeof(Text));
    pText->length = 0;
    pText->firstWord = NULL;
    pText->lastWord = NULL;
    return pText;
}

TextWord* TextWordInit(char* buf)
{
    TextWord* pTextWord = (TextWord*)malloc(sizeof(TextWord));
    pTextWord->word = buf;
    pTextWord->next = NULL;
    return pTextWord;
}

void TextAddWord(Text* text, char* buf)
{
    char* word_buf = (char*)malloc(sizeof(char) * (strlen(buf) + 1));
    strcpy(word_buf, buf);
    // printf("%s \n", word_buf);
    TextWord* word = TextWordInit(word_buf);

    // If the text was empty
    if (text->length == 0)
    {
        text->firstWord = word;
        text->lastWord = word;
        text->length++;
        return;
    }

    // If the text was not empty
    text->lastWord->next = word;
    text->lastWord = word;
    text->length++;
    return;
}

#endif