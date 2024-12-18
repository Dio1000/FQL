package me.dariansandru.io;

import me.dariansandru.io.exception.OutputException;

import java.io.*;
import java.util.List;
import java.io.FileWriter;
import java.io.IOException;

/**
 * Using this object allows the user to write to
 * standard input or to files.
 */
public class OutputDevice {

    /**
     * Writes a line to standard output.
     * @param line Line that is written.
     */
    public void write(String line){
        System.out.print(line);
    }

    /**
     * Writes an integer to standard output.
     * @param value Integer that is written.
     */
    public void write(Integer value){
        System.out.print(value);
    }

    /**
     * Writes a float to standard output.
     * @param value Float that is written.
     */
    public void write(Float value){
        System.out.println(value);
    }

    /**
     * Writes an empty line to standard output.
     */
    public void writeLine() { System.out.println(); }

    /**
     * Writes a string and an empty line to standard output.
     * @param line Line that is written.
     */
    public void writeLine(String line){
        System.out.println(line);
    }

    /**
     * Writes an integer and an empty line to standard output.
     * @param value Integer that is written.
     */
    public void writeLine(Integer value){
        System.out.println(value);
    }

    /**
     * Writes an float and an empty line to standard output.
     * @param value Float that is written.
     */
    public void writeLine(Float value){
        System.out.println(value);
    }

    /**
     * Writes a list of strings to a file.
     * @param list List of strings that is written.
     * @param fileName Name of the file the list is written to.
     * @throws OutputException Thrown when output validation fails.
     */
    public void writeToFile(List<String> list, String fileName) throws OutputException {
        try (BufferedWriter writer = new BufferedWriter(new FileWriter(fileName))) {
            for (String line : list) {
                writer.write(line);
                writer.newLine();
            }
        } catch (IOException e) {
            throw new OutputException("Could not write to file.");
        }
    }

    /**
     * Appends a list of strings to a file.
     * @param list List of strings that is appended.
     * @param fileName Name of the file the list is appended to.
     * @throws OutputException Thrown when output validation fails.
     */
    public void appendToFile(List<String> list, String fileName) throws OutputException {
        try (BufferedWriter writer = new BufferedWriter(new FileWriter(fileName, true))) {
            for (String line : list) {
                writer.write(line);
                writer.newLine();
            }
        } catch (IOException e) {
            throw new OutputException("Could not write to file.");
        }
    }

    /**
     * Writes a String to a file.
     * @param line Line that is written to the file.
     * @param fileName Name of the file the line is written to.
     * @throws OutputException Thrown when output validation fails.
     */
    public void writeToFile(String line, String fileName) throws OutputException {
        try (BufferedWriter writer = new BufferedWriter(new FileWriter(fileName))) {
            writer.write(line);
            writer.newLine();
        } catch (IOException e) {
            throw new OutputException("Could not write to file.");
        }
    }

    /**
     * Appends a String to a file.
     * @param line Line that is appended to the file.
     * @param fileName Name of the file the line is appended to.
     * @throws OutputException Thrown when output validation fails.
     */
    public void appendToFile(String line, String fileName) throws OutputException {
        try (BufferedWriter writer = new BufferedWriter(new FileWriter(fileName, true))) {
            writer.write(line);
            writer.newLine();
        } catch (IOException e) {
            throw new OutputException("Could not write to file.");
        }
    }

    /**
     * Checks for an empty file. If the file is empty, it creates a new one with the specified name.
     * @param fileName Name of the file that is checked or created.
     * @throws OutputException Thrown when output validation fails.
     */
    public void emptyFile(String fileName) throws OutputException {
        try{
            File file = new File(fileName);
            if (file.exists()){
                if (!file.delete()){
                    throw new IOException("Could not delete " + fileName);
                }
            }

            File parent = file.getParentFile();
            if (!parent.exists()){
                if (!parent.mkdirs()){
                    throw new IOException("Could not create directory for " + fileName);
                }
            }

            if (!file.createNewFile()) throw new IOException("Could not create empty file.");
        }catch(IOException e){
            throw new OutputException("Could not erase from file.");
        }
    }
}
