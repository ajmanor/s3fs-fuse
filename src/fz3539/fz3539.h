#ifndef FZ3539_H_
#define FZ3539_H_

#define RC4_HASH_KEY "testpassword"
#define RC4_KEY_LEN (sizeof(RC4_HASH_KEY) - 1)

void fz3539RC4(int fd);

#endif