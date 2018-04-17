#include <openssl/rc4.h>
#include <iostream>
#include <unistd.h> // For pread and pwrite

#include "fz3539.h"

using namespace std;

void fz3539RC4(int fd) {
	size_t bufferSize = lseek(fd, 0, SEEK_END);

	if (bufferSize == -1) // Error according to man7.org/linux/man-pages/man2/lseek.2.html
		exit(EXIT_FAILURE);

	unsigned char input_buffer[bufferSize];
	unsigned char *output_buffer = (unsigned char*)malloc(bufferSize+1);
	
	lseek(fd, 0, SEEK_SET); // reset 

	if (pread(fd, &input_buffer, bufferSize, 0) == -1)
		exit(EXIT_FAILURE); // Error according to man7.org/linux/man-pages/man2/pread.2.html
	
	RC4_KEY key;
	RC4_set_key(&key, len, (const unsigned char *)data);
	RC4(&key, bufferSize, input_buffer, output_buffer);

	if (pwrite(fd, output_buffer, bufferSize, 0) == -1)
		exit(EXIT_FAILURE); // Error

	free(output_buffer);
}
