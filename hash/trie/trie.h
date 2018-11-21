#pragma
#include <linux/types.h>
#include <unordered_set>

const int ALPHABIG = 65, ALPHASMALL = 97, NUMBER = 48;

struct Node {
    char val;
    bool IsLeaf = false;
    std::array<Node *, 256> children{nullptr};
    Node (char v): val(v) {}
};

class Trie {
    Node *root = new Node(-1);
    int size = 0;
 
    void Clear(Node *r);
    void getall(Node *r, std::string cur, std::unordered_set<std::string> &strs) const;
   
public:
    Trie() = default;
    ~Trie();

    void Insert(const std::string &str);
    bool Search(const std::string &str) const;
    int getNum() const { return size; }
    void getAll(std::unordered_set<std::string> &strs) const;
};
