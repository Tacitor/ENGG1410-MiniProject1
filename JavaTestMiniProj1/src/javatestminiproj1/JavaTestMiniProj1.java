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
            } else {
                //decrypt
            }

            //close the file
            outputFileWriter.close();

        } catch (FileNotFoundException e) {
            System.out.println("File ERROR: \n" + e);
        }

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
