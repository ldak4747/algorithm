#pragma once
#include <memory>
#include <vector>
#include <functional>
#include <fstream>
#include "bitmap.h"

#define DUMPFILE "./test.dump"
#define RAWFILE "./raw.file"

class BloomFilter {
    std::unique_ptr<Bitmap> bitmap;
    std::vector<std::function<unsigned int (const char *)>> hash_funcs;
    bool working = false;

    void *fileptr = nullptr;
    int size = 0;
    void dumpmmap();

public:
    BloomFilter();
    ~BloomFilter();

    void AddHashFunc(std::function<unsigned int (const char *)> &&function) { hash_funcs.push_back(function); }
    void LoadRawFile();
    void LoadDumpFile();
    bool judge(int data);
    bool judge(const char *data);

    bool operator== (const BloomFilter &other);
    void traverse() { bitmap->traverse(); }
};
