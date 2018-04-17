#include <openssl/rc4.h>
#include <iostream>
#include <unistd.h>

#include "fz3539.h"

using namespace std;

void fz3539RC4(int fd) {
	size_t bufferSize = lseek(fd, 0, SEEK_END);

	if (bufferSize < 0)
		exit(EXIT_FAILURE);

	lseek(fd, 0, SEEK_SET); // reset 

	unsigned char input_buffer[bufferSize];
	unsigned char *output_buffer = (unsigned char*)malloc(bufferSize+1);

	if (pread(fd, &input_buffer, bufferSize, 0) == -1)
		exit(EXIT_FAILURE);
	
	RC4_KEY key;
	RC4_set_key(&key, len, (const unsigned char *)data);
	RC4(&key, bufferSize, input_buffer, output_buffer);

	if (pwrite(fd, output_buffer, bufferSize, 0) == -1)
		exit(EXIT_FAILURE);

	free(output_buffer);
}
