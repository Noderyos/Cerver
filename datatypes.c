#include "datatypes.h"

void writeVarInt(int fd, int value){
    if(0 > value){
        perror("Negative value");
        return;
    }
    while (1) {
        if ((value & ~SEGMENT_BITS) == 0) {
            send(fd,(const char*)&value,1,0);
            return;
        }
        
        char v = ((value & SEGMENT_BITS) | CONTINUE_BIT);
        printf("Sent : %d", value);
        send(fd,(const char*)&v, 1, 0);

        value >>= 7;
    }
}

void writeVarLong(int fd, long value){
    if(0 > value){
        perror("Negative value");
        return;
    }
    while (1) {
        if ((value & ~(long)SEGMENT_BITS) == 0) {
            send(fd,(const char*)&value,1,0);
            return;
        }
        char v = ((value & SEGMENT_BITS) | CONTINUE_BIT);
        send(fd,(const char*)&v, 1, 0);

        value >>= 7;
    }
}

void writeVarLongLong(int fd, long long value){
    if(0 > value){
        perror("Negative value");
        return;
    }
    while (1) {
        if ((value & ~(long long)SEGMENT_BITS) == 0) {
            send(fd,(const char*)&value,1,0);
            return;
        }
        char v = ((value & SEGMENT_BITS) | CONTINUE_BIT);
        send(fd,(const char*)&v, 1, 0);

        value >>= 7;
    }
}

int readVarInt(int fd){
    int value = 0;
    int position = 0;
    char currentByte;

    while (1) {
        recv(fd, (const char*)&currentByte, 1, 0);
        value |= (currentByte & SEGMENT_BITS) << position;

        if ((currentByte & CONTINUE_BIT) == 0) break;

        position += 7;

        if (position >= 32){
            perror("Var int too big");
            return;
        }
            
    }
    return value;
}

long readVarLong(int fd){
    long value = 0;
    int position = 0;
    char currentByte;

    while (1) {
        recv(fd, (const char*)&currentByte, 1, 0);
        value |= (long)(currentByte & SEGMENT_BITS) << position;

        if ((currentByte & CONTINUE_BIT) == 0) break;

        position += 7;

        if (position >= 64){
            perror("Var long too big");
            return;
        }
    }
    return value;
}