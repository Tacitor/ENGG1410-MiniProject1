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
void encrypt(FILE *inputFile, FILE *outputFile);
void decrypt(FILE *inputFile, FILE *outputFile);
int hexToDecimal(char val16s, char val1s);
int digitHexToDecimal(char digit);

int test = 3; //temp test NEED TO REMOVE THIS AFTER TESTIN IS DONE

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

    if (inputAddress[0] == '\0')
    { // check to see if the string is empty or null
        printf("ERROR: No file to encrypt");
    }
    else // there was a file to encrypt encluded
    {

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
        // check if there were anny issues opening the file
        if (NULL == inputFile)
        {
            printf("\nERROR opening the input file. Might not exists.\n");
        }
        else // if a good input file was given
        {

            outputFile = fopen(outputAddress, "w"); // open the output in such a way it can be written to

            // check if there were anny issues opening the file
            if (NULL == outputFile)
            {
                printf("\nERROR opening the output file\n");
            }
            else // if there was no error, read the file
            {
                // check if we are encrypting or decrypting
                if (encrytMode)
                {
                    // encrypt
                    encrypt(inputFile, outputFile);
                }
                else
                {
                    // decrypt
                    decrypt(inputFile, outputFile);
                }
            }
            // don't forget to close the file
            fclose(outputFile);
        }
        fclose(inputFile);
    }
    return 0;
}

/**
 * Given an input file and an output file decrypt the input and store it in the output.
 * Also its not really decryption, its a convertion to DECimal followed by a bitshift, but hey close enough.
 */
void decrypt(FILE *inputFile, FILE *outputFile)
{
    char workingChars[2]; // create the string that holds the current working set of hex characters
    int outChar;          // the decryped version of the workingChar

    // check if the end of the file has been reached
    while (!feof(inputFile))
    {
        // get the next two chars
        workingChars[0] = fgetc(inputFile);
        workingChars[1] = fgetc(inputFile);

        // check if it is a negative 1 (-1) (which is sometimes at the end of windows files)
        if ((int)workingChars[0] != -1 || (int)workingChars[1] != -1)
        {

            // =-=-=-=-=now lets decrypt the file=-=-=-=-=-=

            // check if there is a tab
            if (workingChars[0] == 'T' || workingChars[1] == 'T')
            {
                // if yes then write a TT
                outChar = 9;
            }
            else if ((int)workingChars[0] == 10)
            {                 // check for a line feed
                outChar = 10; // set it to a LF
            }
            else
            {
                // convert to decimal
                outChar = hexToDecimal((int)workingChars[0], (int)workingChars[1]);

                if (test > 0)
                {
                    test--;

                    printf("\nworkingChars[0]: %c", workingChars[0]);
                    printf("\nworkingChars[1]: %c", workingChars[1]);

                    printf("\nworkingCharsInHEX[1]: %d", digitHexToDecimal((int)workingChars[0]));
                    printf("\nworkingCharsInHEX[0]: %d", digitHexToDecimal((int)workingChars[1]));

                    printf("\nOutput: %d\n", outChar);
                }

                // get the char as an int and shift it
                outChar += +16;

                // check if it's greater than 127
                if (outChar > 127)
                {
                    // do the thing
                    outChar = (outChar - 144) + 32;
                }
            }

            // write it to the file
            fprintf(outputFile, "%c", outChar);
        }
    }
}

/**
 * Given an input file and an output file encrypt the input and store it in the output.
 * Also its not really encryption, its a bitshift followed by an convertion to HEX, but hey close enough.
 */
void encrypt(FILE *inputFile, FILE *outputFile)
{
    char workingChar;       // create the char that hold the current working character
    int outChar;            // the encryped version fo the workingChar
    char outCharAsFinal[2]; // either the TT sequence or the HEX version of the encrypted ascii data

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
 * Take in a two digit hexadecimal value and convert it to decimal
 */
int hexToDecimal(char val16s, char val1s)
{
    int decimal = 0;

    decimal += (digitHexToDecimal(val16s) * 16);
    decimal += digitHexToDecimal(val1s);

    return decimal;
}

/**
 * Take in a hex digit, and return its value in decimal.
 */
int digitHexToDecimal(char digit)
{
    if ((digit - '0') < 10)
    {
        return (int)(digit - '0');
    }
    else
    {
        switch (digit)
        {
        case 65:
            return 10;
        case 66:
            return 11;
        case 67:
            return 12;
        case 68:
            return 13;
        case 69:
            return 14;
        case 70:
            return 15;
        default:
            return digit; // not single digit (In Hex) input was given (or I'm just shit at code)
        }
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