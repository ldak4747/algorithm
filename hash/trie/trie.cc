#include "trie.h"

void Trie::Clear (Node *r) {
    if (r) {
        for (auto &it: r->children) {
            if (it) {
                Clear(it);
                delete it;
                it = nullptr;
            }
        }
    }
}

Trie::~Trie () {
    Clear(root);
    delete root;
}

void Trie::Insert (const std::string &str) {
    Node *start = root;

    for (auto &ch: str) {
        size_t idx = static_cast<size_t>(ch);

        if (!start->children[idx]) {
            start->children[idx] = new Node(ch);
        }
        start = start->children[idx];
    }

    if (false == start->IsLeaf) {
        ++size;
        start->IsLeaf = true;
    }
}

bool Trie::Search (const std::string &str) const {
    Node *start = root;
    for (auto &ch: str) {
        size_t idx = static_cast<size_t>(ch);

        if (nullptr == start->children[idx]) {
            return false;
        }

        start = start->children[idx];
    }

    if (false == start->IsLeaf) {
        return false;
    }

    return true;
}

void Trie::getall (Node *r, std::string cur, std::unordered_set<std::string> &strs) const {
    if (!r) {
        return;
    } else if (r->IsLeaf) {
        strs.insert(cur);
        return;
    }

    for (auto &it: r->children) {
        if (it) {
            cur += it->val;
            getall(it, cur, strs);
            cur.pop_back();
        }
    }
}

void Trie::getAll (std::unordered_set<std::string> &strs) const {
    getall(root, "", strs);
}

