#include <stdio.h>
#include "./include/utils.h"
#include "./include/textstorage.h"

int main(void)
{
    printf("Opening file... ");
    FILE* input = fopen("./io/hw4_input.txt", "r");
    FILE* dictionary = fopen("./io/dict.txt", "r");
    FILE* output = fopen("./io/hw4_output.txt", "w");
    printf("finished. \n");

    printf("Reading dictionary... ");
    FreqDict* dict = DictRead(dictionary);
    printf("finished. \n");

    printf("Reading text... ");
    int freqCnt = TextCountNum(input);
    printf("%d \n", freqCnt);
    Text* text = TextRead(input);
    printf("Finished. \n");

    fprintf(output, "\n");
    CountWordFrequency(output, dict, text, freqCnt);
    fclose(input);
    fclose(dictionary);
    fclose(output);
}