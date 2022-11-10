#ifndef DATATYPES_H_
#define DATATYPES_H_

#define SEGMENT_BITS 0x7F
#define CONTINUE_BIT 0x80

void writeVarInt(int fd, int value);
void writeVarLong(int fd, long value);
void writeVarLongLong(int fd, long long value);


int readVarInt(int fd);
long readVarLong(int fd);


#endif // DATATYPES_H_
