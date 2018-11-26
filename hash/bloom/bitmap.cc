#include "bitmap.h"
#include <iostream>

Bitmap::Bitmap (int size, unsigned int *srcdata): bitdata(srcdata), fromextern(true) {
    if (!srcdata) {
        len = size/32 + 1;
        bitdata = new unsigned int[len];
        memset(bitdata, 0, (size/32 + 1) * sizeof(int));
        fromextern = false;
    } else {
        len = size/4;
    }
}

Bitmap::~Bitmap () {
    if (!fromextern) {
        delete []bitdata;
    }
}

void Bitmap::set (unsigned int d) {
    int idx1 = d/32, idx2 = d % 32;
    if (idx1 < len) {
        bitdata[idx1] |= (1 << idx2);
    }
}

bool Bitmap::test (unsigned int d) const {
    int idx1 = d/32, idx2 = d % 32;
    if (idx1 < len) {
        return bitdata[idx1] & (1 << idx2);
    }
}

void Bitmap::dump (const char *dumpfile) {
    int fd = open(dumpfile, O_CREAT | O_RDWR | O_TRUNC);
    if (fd < 0) {
        return;
    }

    lseek(fd, len * sizeof(int), SEEK_SET);
    write(fd, "\0", 1);

    void *fileptr = mmap(nullptr, len * sizeof(int), PROT_WRITE, MAP_SHARED, fd, 0);
    if (MAP_FAILED == fileptr) {
        close(fd);
        return;
    }
    memcpy(fileptr, bitdata, len * sizeof(int));
    munmap(fileptr, len * sizeof(int));
    close(fd);
}

bool Bitmap::operator== (const Bitmap &other) {
    if (len == other.len) {
        return memcmp(bitdata, other.bitdata, len);
    }

    return false;
}

void Bitmap::traverse () {
    for (unsigned int i = 0; i < MAXHASHCODE/32 + 1; i++) {
        for (int j = 0; j < 32; j++) {
            if (bitdata[i] & (1 << j)) {
                unsigned int data = i * 32 + j;
                std::cout << data << std::endl;
            }
        }
    }
}
