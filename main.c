#include <stdio.h>
#include "./include/utils.h"
#include "./include/textstorage.h"

int main(void)
{
    printf("Opening file... ");
    FILE* input = fopen("./io/input.txt", "r");
    FILE* dictionary = fopen("./io/dict.txt", "r");
    FILE* output = fopen("./io/output.txt", "w");
    FILE* dict_output = fopen("./io/dict_output.txt", "w");
    printf("finished. \n");

    printf("Reading dictionary... ");
    FreqDict* dict = DictRead(dictionary);
    DictWrite(dict, dict_output);
    printf("finished. \n");

    printf("Reading text... ");
    Text* text = TextRead(input);
    TextWordWrite(text, output);
    printf("Finished. \n");

    CountWordFrequency(dict, text);
    TextWordWrite(text, output);
}