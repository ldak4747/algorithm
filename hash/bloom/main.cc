#include "bitmap.h"
#include "bloomfilter.h"
#include <unordered_set>
#include <fstream>
#include "gtest/gtest.h"

#include <random>
#include <iostream>


unsigned int FNV1_32_HASH (const char *key) {
    int p = 16777619;
    unsigned int hash = (int)2166136261L;
    for (int i = 0; i < strlen(key); i++) {
        hash = (hash ^ key[i]) * p;
    }

    hash += hash << 13;
    hash ^= hash >> 7;
    hash += hash << 3;
    hash ^= hash >> 17;
    hash += hash << 5;
    if (hash < 0) {
        hash = (0 - hash);
    }

    return hash;
}

unsigned int murMurHash2 (const char *key) {
    int len = strlen(key);
    const unsigned int m = 0x5bd1e995;
    const int r = 24;
    const int seed = 97;
    unsigned int h = seed ^ len;

    // Mix 4 bytes at a time into the hash
    const unsigned char *data = (const unsigned char *)key;
    while(len >= 4) {
        unsigned int k = *(unsigned int *)data;
        k *= m;
        k ^= k >> r;
        k *= m;
        h *= m;
        h ^= k;
        data += 4;
        len -= 4;
    }

    // Handle the last few bytes of the input array
    switch(len) {
        case 3: h ^= data[2] << 16;
        case 2: h ^= data[1] << 8;
        case 1: h ^= data[0];
        h *= m;
    }

    return h;
}
    
int main (int argc, char *argv[]) {
    BloomFilter blf1;
    blf1.AddHashFunc(std::bind(FNV1_32_HASH, std::placeholders::_1));
    blf1.AddHashFunc(std::bind(murMurHash2, std::placeholders::_1));

    if (-1 == access(DUMPFILE, F_OK)) {
        blf1.LoadRawFile();
    } else {
        //test
        std::ifstream ifs("raw.file");
        while (!ifs.eof()) {
            std::string line;
            getline(ifs, line);
            bool err = blf1.judge(line.c_str());
            if (!err) {
                std::cout << line;
            }
        }
    }
    //blf1.LoadRawFile();

    //std::cout << (blf1 == blf2) << std::endl;
    return 0;




    

    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
