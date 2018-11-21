#include "trie.h"
#include <random>
#include <assert.h>

void test () {
    std::array<char, 56> chars;
    int idx = 0;
    for (char start = 48; start < 58; ++start) {
        chars[idx++] = start;
    }
    for (char start = 65; start < 92; ++start) {
        chars[idx++] = start;
    }
    for (char start = 97; start < 114; ++start) {
        chars[idx++] = start;
    }

    std::unordered_set<std::string> A, B;
    Trie trie;
    for (int i = 0; i < 100; i++) {
        std::random_device rd;
        std::string hash = "";
        for (auto i: chars) {
            hash += chars[rd() % chars.size()];
        }
        trie.Insert(hash);
        A.insert(hash);
        assert(trie.Search(hash));
    }

    trie.getAll(B);
    assert(A == B);
}

int main () {
    test();
    return 0;
}
