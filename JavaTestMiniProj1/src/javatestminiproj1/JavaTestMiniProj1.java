/*
 * Lukas Krampitz
 * October 31, 2022
 * The Main class that is able to use a very basic type of "encrytion" to modify files
 */
package javatestminiproj1;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.PrintWriter;
import java.util.Scanner;

/**
 *
 * @author Lukas
 */
public class JavaTestMiniProj1 {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        boolean encrytMode = true; //whether or not the program is encrypting or decrypting
        String inputAddress = "src/javaTestMiniProj1/testFile.txt";
        String outputAddress;
        String outputFileType = getFileType(encrytMode);

        //Read in the data file
        try {
            //Setup the file and scanner
            File inputFile = new File(inputAddress);
            Scanner scanner = new Scanner(inputFile);

            //set the output adress as the same as the input but with a different file extension
            outputAddress = inputAddress.substring(0, inputAddress.indexOf('.')) + outputFileType;
            //create a new output file
            File outputFile = new File(outputAddress);
            //create a print wrtitter to write to the file
            PrintWriter outputFileWriter = new PrintWriter(outputFile);

            //now either encrypt or decrypt the file
            if (encrytMode) {
                //encypt
                encrypt(scanner, outputFileWriter);
            } else {
                //decrypt
                System.out.println("Lol Can't");
            }

        } catch (FileNotFoundException e) {
            System.out.println("File ERROR: \n" + e);
        }

    }

    /**
     * Encrypt a file. Given a Scanner from an input file and a PrintWritter as
     * an output-stream convert the input to an sudo encrypted file.
     *
     * @param scanner
     * @param outputFileWriter
     */
    private static void encrypt(Scanner scanner, PrintWriter outputFileWriter) {
        String workingLine; //the current line of the input file being worked on
        char workingChar; //the character currently being worked on
        int outChar; //the encryped version fo the workingChar

        //encrypt the file line by line
        //while there are still lines left loop through it
        while (scanner.hasNextLine()) {
            workingLine = scanner.nextLine();

            for (int i = 0; i < workingLine.length(); i++) {
                //get the next character
                workingChar = workingLine.charAt(i);

                //encrypt the character
                outChar = (int) workingChar - 16;

                //check if it's less than 32
                if (outChar < 32) {
                    outChar = (outChar - 32) + 144;
                }

                //write it
                outputFileWriter.print(outChar + " ");
            }
            outputFileWriter.println("");

            //outputFileWriter.println(scanner.nextLine());
        }

        //close the file
        outputFileWriter.close();
    }

    /**
     * Based off of the mode the program is in: Either encryption or decryption.
     * Then determine the extension that should be used for the output file.
     *
     * @param encrytMode
     * @return
     */
    protected static String getFileType(boolean encrytMode) {
        if (encrytMode) {
            return ".crp";
        } else {
            return ".txt";
        }
    }

}
