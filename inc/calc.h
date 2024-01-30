#ifndef CRYPT_H
#define CRYPT_H

#define MAX_BUFF 1024
#define STDIN 0
#define STDOUT 1
#define STDERR  2

void client(int readfd /*read head of channel */, int writefd /*write head of channel */); 
void server(int readfd /*read head of channel */, int writefd /*write head of channel */);
double calculate(char *buf);

#endif
