/*
 * Lukas Krampitz
 * Novembre 6, 2022
 * The Main class that is able to use a very basic type of "encrytion" to modify files
 */
#include <stdio.h>
#include <string.h>

void getFileType(_Bool encrytMode, char outputFileType[100]);

int main(void)
{
    _Bool encrytMode = 1; // whether or not the program is encrypting or decrypting
    char inputAddress[100] = "src/javaTestMiniProj1/testFile.txt";
    char outputAddress[100];

    char outputFileType[100];
    getFileType(encrytMode, outputFileType); // set the file type to either .txt or .crp

    printf("Testing hello there");
    printf("%s", outputFileType);

    return 0;
}

/**
 * Based off of the mode the program is in: Either encryption or decryption.
 * Then determine the extension that should be used for the output file.
 */
void getFileType(_Bool encrytMode, char outputFileType[100])
{
    if (encrytMode)
    {
        strcpy(outputFileType, ".crp");
    }
    else
    {
        strcpy(outputFileType, ".txt");
    }
}