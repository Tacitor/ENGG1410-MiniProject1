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
void getNameBeforeDot(int inSize, char in[inSize], int outSize, char out[outSize]);

/**
 * The main method
 */
int main(int argc, char *argv[])
{
    _Bool encrytMode = 1; // whether or not the program is encrypting or decrypting. Default to encryption mode
    int inputAddressSize = 100;
    int outputAddressSize = inputAddressSize + 5; // make it a little longer to accont for the fact file extensions will be appended
    char inputAddress[inputAddressSize];
    char outputAddress[outputAddressSize];
    memset(inputAddress, '\0', sizeof(inputAddress));
    memset(outputAddress, '\0', sizeof(outputAddressSize)); // set them to empty strings. So that it can be tested to see if the user included a file to encrypt or not.";

    // loop through the cli arguments. Get the encrption mode and the target file
    for (int i = 1; i < argc; i++) // skip the name of the .exe
    {
        //  check if "-E" or "-e" were passed for ecryption mode
        if (!strcmp(argv[i], "-E") || !strcmp(argv[i], "-e"))
        {
            // set mode to encrption
            encrytMode = 1;
        }
        //  check if "-d" or "-D" were passed for decryption mode
        else if (!strcmp(argv[i], "-D") || !strcmp(argv[i], "-d"))
        {
            // set mode to encrption
            encrytMode = 0;
        }
        else // if neither a flag for encryption or decryption assume its a file to operate on
        {
            strcpy(inputAddress, argv[i]);
            // preform a little direct memory manipulation to get a substring of the file name
            getNameBeforeDot(inputAddressSize, inputAddress, outputAddressSize, outputAddress);
        }
    }

    char outputFileType[100];
    getFileType(encrytMode, outputFileType); // set the file type to either .txt or .crp
    strcat(outputAddress, outputFileType);   // add on the file extension

    // debug the file addresses.
    // printf("\nInput Address: \t\t%s", inputAddress);
    // printf("\nOutput Address: \t%s", outputAddress);

    // create the FILE pointer
    FILE *inputFile = NULL;
    FILE *outputFile = NULL;

    // open the file so it can be read
    inputFile = fopen(inputAddress, "r");
    outputFile = fopen(outputAddress, "w"); // open the output in such a way it can be written to
    char workingChar;                       // create the char that hold the current working character
    int outChar;                            // the encryped version fo the workingChar
    char outCharAsFinal[2];                 // either the TT sequence or the HEX version of the encrypted ascii data

    // check if there were anny issues opening the file
    if (NULL == inputFile || NULL == outputFile)
    {
        printf("\nERROR opening the file\n");
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
                {                             // check for a line feed
                    outCharAsFinal[0] = 10;   // set it to a LF
                    outCharAsFinal[1] = '\0'; // clear the other indexes
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
 * preform a little direct memory manipulation to get a substring of the file name
 * As a little Java boy this hurts my head
 */
void getNameBeforeDot(int inSize, char in[inSize], int outSize, char out[outSize])
{
    int dotLocation = -1; // is there a dot in the input filename. -1 is there is no dot, else its the position.

    // loop through the input file name
    for (int i = 0; i < inSize; i++)
    {
        // check each index to see if it has a dot (.)
        if (in[i] == '.')
            dotLocation = i; // if there is save that index. This should also grab the last index if there are multiple dots
    }

    // make sure the outstring has enough room for both the base and the file extension (overestimate it a little for safety)
    if ((outSize + 3) >= inSize)
    {
        // check if there is a dot
        if (dotLocation == -1)
        {

            // no dot? set the base path to the same
            strcpy(out, in);
        }
        else
        {
            // debug the detection of the dot in the file name
            // printf("\ndotLocation: %d\ninSize: %d", dotLocation, inSize);

            // yes dot? grab only everything before the dot
            memcpy(out, &in[0], dotLocation); // the hurtful memory fuckery
            out[dotLocation] = '\0';
        }
    }
    else
    {
        printf("\n\nERROR: Sorry but that file name is too long");
    }
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

/**
 * Take in a decimal number (Up to 255) and convert it to Hexadecimal
 */
void decimalToHex(int num, char outCharAsFinal[])
{
    int quotient;
    int remainder;

    quotient = num / 16;
    remainder = num % 16;

    outCharAsFinal[1] = digitDecimalToHex(remainder);
    outCharAsFinal[0] = digitDecimalToHex(quotient % 16);
    // set the next as the end of the string
    outCharAsFinal[2] = '\0';

    return;
}

/**
 * Take in a decimal number (up to 15) and convert it to a single hexadecimal digit
 */
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