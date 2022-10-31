/*
 * Lukas Krampitz
 * October 31, 2022
 * The Main class that is able to use a very basic type of "encrytion" to modify files
 */
package javatestminiproj1;

import java.io.File;
import java.io.FileNotFoundException;
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

        //Read in the data file
        try {
            //Setup the file and scanner
            File file = new File("src/javaTestMiniProj1/testFile.txt");
            Scanner scanner = new Scanner(file);
            
            //print out the data file to the output
            while (scanner.hasNextLine()) {
                System.out.println(scanner.nextLine());
            }

        } catch (FileNotFoundException e) {
            System.out.println("File ERROR: \n" + e);
        }

    }

}
