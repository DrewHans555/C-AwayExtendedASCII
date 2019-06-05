#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "CAwayExtendedASCII.h"

int CAwayExtendedASCII(const char *filename)
{
    FILE *filePtr;
    char *charsByteStream;
    char *packedByteStream;
    unsigned long int fileLengthInBytes = 0;
    unsigned long int packedLength = 0;
    const int OLDBITS = 8;
    const int NEWBITS = 7;

    filePtr = fopen(filename, "rb");
    if (filePtr == NULL)
    {
        fprintf(stderr, "Error opening %s\n", filename);
        return 1;
    }

    fseek(filePtr, 0, SEEK_END);
    fileLengthInBytes = ftell(filePtr);
    rewind(filePtr);

    // malloc enough memory for file + \0
    charsByteStream = (char *)malloc((fileLengthInBytes + 1) * sizeof(char));
    if (charsByteStream == NULL)
    {
        fprintf(stderr, "Error: malloc failed for charsByteStream");
        fclose(filePtr);
        return 1;
    }

    fread(charsByteStream, fileLengthInBytes, 1, filePtr);
    fclose(filePtr);

    // calculate the size of our compressed file
    unsigned long int tempSize = 0;
    tempSize = (fileLengthInBytes / OLDBITS) * NEWBITS;
    packedLength = tempSize + (tempSize % 8);

    // malloc enough memory for new file + \0
    packedByteStream = (char *)malloc((packedLength + 1) * sizeof(char));
    if (packedByteStream == NULL)
    {
        fprintf(stderr, "Error: malloc failed for packedByteStream");
        free(charsByteStream);
        return 1;
    }

    unsigned long int pbsIndex = 0;
    packedByteStream[pbsIndex] = 0;
    int pbsBitsFilled = 0;

    // visit each byte in charsByteStream
    for (unsigned long int byteIndex = 0; byteIndex < fileLengthInBytes; byteIndex++)
    {
        for (int i = 6; i > -1; i--)
        {
            char byte = charsByteStream[byteIndex];
            byte = ((byte >> i) & 0x01) << i;
            packedByteStream[pbsIndex] = packedByteStream[pbsIndex] | byte;
            pbsBitsFilled++;

            if (pbsBitsFilled == 8)
            {
                // move to next byte in packedByteStream
                pbsIndex++;
                packedByteStream[pbsIndex] = 0;
                pbsBitsFilled = 0;
            }
        }
    }

    free(charsByteStream);

    char *compressedFileName = malloc(strlen(filename) + 11 + 1);
    if (compressedFileName == NULL)
    {
        fprintf(stderr, "Error: malloc failed for compressedFileName");
        return 1;
    }
    strcpy(compressedFileName, filename);
    strcat(compressedFileName, ".compressed");

    FILE *compressedFilePtr = fopen(compressedFileName, "w");
    free(compressedFileName);

    int fputsResult = fputs(packedByteStream, compressedFilePtr);

    free(packedByteStream);
    fclose(compressedFilePtr);

    if (fputsResult == EOF)
    {
        fprintf(stderr, "Failed to write packedByteStream to file.\n");
        return 1;
    }

    return 0;
}
