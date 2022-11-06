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
    char inputAddress[300] = "C:/Users/Lukas/Documents/Uni/Sem 1/Intro Programming/ENGG1410-MiniProject1/C Source/testFile.txt";
    char outputAddress[100] = "C:/Users/Lukas/Documents/Uni/Sem 1/Intro Programming/ENGG1410-MiniProject1/C Source/testFile";

    char outputFileType[100];
    getFileType(encrytMode, outputFileType); // set the file type to either .txt or .crp
    strcat(outputAddress, outputFileType);   // add on the file extension

    // create the FILE pointer
    FILE *inputFile;
    FILE *outputFile;
    // create the char that hold the current working character
    char workingChar;

    // open the file so it can be read
    inputFile = fopen(inputAddress, "r");
    outputFile = fopen(outputAddress, "w"); // open the output in such a way it can be written to

    // check if there were anny issues opening the file
    if (NULL == inputFile || NULL == outputFile)
    {
        printf("ERROR opening the file\n");
    }
    else // if there was no error, read the file
    {
        // check if the end of the file has been reached
        while (!feof(inputFile))
        {
            // get the next char
            workingChar = fgetc(inputFile);

            // check if it is a negative 1 (-1)
            if ((int)workingChar != -1)
            {

                // print that bad boy out
                printf("%d ", workingChar);
                fprintf(outputFile, "%c", workingChar);
            }
        }

        // don't forget to close the file
        fclose(outputFile);
        fclose(inputFile);
    }

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