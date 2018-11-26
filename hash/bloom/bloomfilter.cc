#include "bloomfilter.h"
#include <iostream>

void BloomFilter::dumpmmap () {
    int fd = open(DUMPFILE, O_RDONLY);
    if (fd >= 0) {
        struct stat st;
        if (0 > fstat(fd, &st)) {
            return;
        }

        int filesize = st.st_size;
        void *fptr = mmap(nullptr, filesize, PROT_READ, MAP_SHARED, fd, 0);
        if (MAP_FAILED == fptr) {
            return;
        }

        close(fd);
        fileptr = fptr;
        size = filesize;
    }
}

BloomFilter::BloomFilter () {
    LoadDumpFile();
}

BloomFilter::~BloomFilter () {
    if (working) {
        munmap(fileptr, size);
    }
}

void BloomFilter::LoadRawFile () {
    if (!hash_funcs.empty()) {
        bitmap.reset(new Bitmap(MAXHASHCODE));
        std::ifstream rawfile(RAWFILE);

        std::string line = "";
        while (!rawfile.eof()) {
            getline(rawfile, line);
            for (auto &func: hash_funcs) {
                unsigned int hashcode = func(line.c_str()) % MAXHASHCODE;;
                bitmap->set(hashcode);
            }
        }

        bitmap->dump(DUMPFILE);
        rawfile.close();
    }
}

void BloomFilter::LoadDumpFile () {
    std::ifstream dumpfile(DUMPFILE, std::ios::in);
    if (dumpfile) {
        dumpmmap();
        if (fileptr != MAP_FAILED) {
            bitmap.reset(new Bitmap(size, (unsigned int *)fileptr));
            working = true;
            return;
        }
    }
}

bool BloomFilter::judge (const char *data) {
    for (auto &func: hash_funcs) {
        int hashcode = func(data) % MAXHASHCODE;
        if (!bitmap->test(hashcode)) {
            return false;
        }
    }

    return true;
}

bool BloomFilter::judge (int data) {
    for (auto &func: hash_funcs) {
        unsigned int hashcode = func(std::to_string(data).c_str()) % MAXHASHCODE;
        if (!bitmap->test(hashcode)) {
            return false;
        }
    }

    return true;
}

bool BloomFilter::operator== (const BloomFilter &other) {
    if (size == other.size) {
        return *bitmap == *other.bitmap;
    }

    return false;
}
