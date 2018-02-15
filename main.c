/*******************************************************************************************
 * Filename: main.c
 * Author: Drew Hans (github.com/drewhans555)
 * Description: This program takes in an ANSI text document with 8-bit ASCII characters,
 *              removes the leftmost bit (used for extended ASCII characters), and outputs a
 *              new compressed file.
 *******************************************************************************************
 */

#include <stdio.h>
#include <stdlib.h>

const char PROGRAMNAME[] = "C-AwayWithExtendedASCII";

/* main method - the program starts here */
int main(void) {
    printf("Starting %s...\n", PROGRAMNAME);
    const char FILENAME[] = "./Alice's Adventures in Wonderland by Lewis Carroll.txt";
    FILE* filePtr; // the pointer to our file
    char* charsByteStream; // the byte stream containing the characters in our file
    char* packedByteStream; // the byte stream containing the packed characters from charsByteStream
    unsigned long int filelength = 0; // the size of our file
    unsigned long int packedLength = 0; // the size of our compressed file
    const int OLDBITS = 8; // the number of bits originally used for each character
    const int NEWBITS = 7; // the number of bits we want to use for each character

    // get our fileSize
    filePtr = fopen(FILENAME, "rb"); // open the file in binary mode
    fseek(filePtr, 0, SEEK_END); // jump to the end of the file
    filelength = ftell(filePtr); // get the current byte offset in the file
    rewind(filePtr); // jump back to the beginning of the file

    // dynamically allocate a chunk of memory to store our character byte stream
    charsByteStream = (char *) malloc((filelength + 1) * sizeof (char)); //enough memory for file + \0

    // read in the entire file in charsByteStream
    fread(charsByteStream, filelength, 1, filePtr);

    // close the file once we're done with it
    fclose(filePtr);

    //printf("%hhx\n", charsByteStream[0]); // gives you the first byte in the file
    //printf("%hhx\n", charsByteStream[1]); // gives you the second byte in the file
    // ..... 
    //printf("%hhx\n", charsByteStream[filelength - 2]); //gives you the second to last byte in the file
    //printf("%hhx\n", charsByteStream[filelength - 1]); //gives you the last byte in the file
    //printf("%hhx\n", charsByteStream[filelength]); //gives you garbage

    // calculate the size of our compressed file
    unsigned long int tempSize = 0;
    tempSize = (filelength / OLDBITS) * NEWBITS; // get the number of chars, times 7 bits per char
    packedLength = tempSize + (tempSize % 8); // account for the last byte that needs to be filled in packedByteStream

    // dynamically allocate a chunk of memory to store our packed byte stream
    packedByteStream = (char *) malloc((packedLength + 1) * sizeof (char)); //enough memory for file + \0

    unsigned long int cbsIndex = 0; // charByteStream index
    unsigned long int pbsIndex = 0; // packedByteStream index
    int pbsBitIndex = 0; // the next bit that needs to be filled in packedByteStream[pbsIndex]

    // visit each char in charByteStream
    while (cbsIndex < filelength) {
        // visit each bit in the char
        for (int i = 6; i > -1; i--) {
            // shove each bit into packedByteStream[pbsIndex] except for leftmost bit
            packedByteStream[pbsIndex] = (packedByteStream[pbsIndex]) | ((charsByteStream[cbsIndex] >> i) & 0x01);
            pbsBitIndex++; // indicates next bit to be filled

            // if out of byte bounds in packedByteStream[pbsIndex]
            if (pbsBitIndex == 8) {
                pbsIndex++; // move to next byte in packedByteStream
                pbsBitIndex = 0; // reset to zero
            }
        }
        cbsIndex++; // move to next char in charByteStream
    }

    // open a file for writing (use "w+" for appending)
    FILE* compressedFilePtr = fopen("compressed.hans", "w");

    // put the packedByteStream into the file
    int fputsResult = fputs(packedByteStream, compressedFilePtr);

    // check for errors
    if (fputsResult == EOF) {
        printf("Failed to write packedByteStream to file.");
    }

    // close the compressedFilePtr when we're finished with it
    fclose(compressedFilePtr);

    printf("%s will now end. ", PROGRAMNAME);
    free(charsByteStream);
    free(packedByteStream);
}//end main method
