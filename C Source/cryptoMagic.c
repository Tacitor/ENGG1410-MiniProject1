/*
 * Lukas Krampitz
 * Novembre 6, 2022
 * The Main class that is able to use a very basic type of "encrytion" to modify files
 */
#include <stdio.h>
#include <string.h>

void getFileType(_Bool encrytMode, char outputFileType[100]);
char digitDecimalToHex(int num);
void decimalToHex(int num, char leArray[2]);

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

    // open the file so it can be read
    inputFile = fopen(inputAddress, "r");
    outputFile = fopen(outputAddress, "w"); // open the output in such a way it can be written to
    char workingChar;                       // create the char that hold the current working character
    int outChar;                            // the encryped version fo the workingChar
    char outCharAsFinal[3];                 // either the TT sequence or the HEX version of the encrypted ascii data

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

                // =-=-=-=-=now lets encrypt the file=-=-=-=-=-=

                // check if there is a tab
                if (workingChar == 9)
                {
                    // if yes then write a TT
                    strcpy(outCharAsFinal, "TT");
                }
                else if (workingChar == 10)
                {                           // check for a line feed
                    outCharAsFinal[0] = 10;  // clear the other indexes
                    outCharAsFinal[1] = 0; // set it to a LF
                }
                else
                {
                    // get the char as an int and shift it
                    outChar = (int)workingChar - 16;

                    // check if it's less than 32
                    if (outChar < 32)
                    {
                        outChar = (outChar - 32) + 144;
                    }

                    // convert to hex
                    decimalToHex(outChar, outCharAsFinal);
                }

                fprintf(outputFile, "%s", outCharAsFinal);
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

void decimalToHex(int num, char outCharAsFinal[])
{
    int quotient;
    int remainder;

    quotient = num / 16;
    remainder = num % 16;

    outCharAsFinal[1] = digitDecimalToHex(remainder);
    outCharAsFinal[0] = digitDecimalToHex(quotient % 16);

    return;
}

char digitDecimalToHex(int num)
{
    if (num < 10)
    {
        return (num + '0');
    }
    else
    {
        switch (num)
        {
        case 10:
            return 'A';
        case 11:
            return 'B';
        case 12:
            return 'C';
        case 13:
            return 'D';
        case 14:
            return 'E';
        case 15:
            return 'F';
        default:
            return 'Z'; // not single digit (In Hex) input was given (or I'm just shit at code)
        }
    }
}