#include <iostream>
#include <fstream> // Get the pw file
#include "openssl/rc4.h"
#include "fz3539.h"
#include <unistd.h>
#include <string.h>

using namespace std;

bool fz3539RC4(int fd) {

    // Get the password from the file
    ifstream pwFile;
    pwFile.open("~/Desktop/pw.txt"); // open password file from the desktop
    string temp;
    getline(pwFile, temp);
    int myKeyLength = sizeof(temp)-1;
    unsigned char* myKey = (unsigned char*)temp.c_str(); // Need to convert string to unsigned char for RC4

    // Determine inputBufferSize for future buffer size
    off_t inputBufferSize = lseek(fd, 0, SEEK_END);

	if (inputBufferSize < 0)
		return false; // Something wrong with file. File size cannot be less than 0.

	lseek(fd, 0, SEEK_SET); // Go back to start of the fd content to read into buffer in next step

    // Create the input and output buffers. Must be of type unsigned char according to rc4.h
    unsigned char input_buffer[inputBufferSize];
    unsigned char *output_buffer = (unsigned char*)malloc(inputBufferSize+1); // allocate memory for the buffer

    // Try to read the file
    if (pread(fd, &input_buffer, inputBufferSize, 0) == -1)
		return false; // Cannot read the file

    // RC4 functions
    RC4_KEY theRC4key;
    RC4_set_key(&theRC4key, myKeyLength, (const unsigned char *)myKey);
	RC4(&theRC4key, inputBufferSize, input_buffer, output_buffer);

    // Try to write the file
	if (pwrite(fd, output_buffer, inputBufferSize, 0) == -1)
		return false; // Can't write to the output

    free(output_buffer);

    return true; // successful
}
