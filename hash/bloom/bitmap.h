#pragma once
#include <sys/mman.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

const unsigned int MAXHASHCODE = 1000 * 1000 * 100;

class Bitmap {
    unsigned int *bitdata = nullptr;
    int len = 0;
    bool fromextern = false;

public:

    Bitmap() = default;
    Bitmap(int size, unsigned int *srcdata = nullptr);
    ~Bitmap();

    void dump(const char *dumpfile);
    void set(unsigned int d);
    bool test(unsigned int d) const;

    bool operator== (const Bitmap &other);
    void traverse();
};
