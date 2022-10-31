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

        //Read in the data file
        try {
            //Setup the file and scanner
            File inputFile = new File(inputAddress);
            Scanner scanner = new Scanner(inputFile);

            //set the output adress as the same as the input but with a different file extension
            outputAddress = inputAddress.substring(0, inputAddress.indexOf('.')) + ".crp";
            //create a new output file
            File outputFile = new File(outputAddress);
            //create a print wrtitter to write to the file
            PrintWriter outputFileWriter = new PrintWriter(outputFile);

            //write to the file
            while (scanner.hasNextLine()) {
                outputFileWriter.println(scanner.nextLine());
            }
            
            //close the file
            outputFileWriter.close();

        } catch (FileNotFoundException e) {
            System.out.println("File ERROR: \n" + e);
        }

    }

}
