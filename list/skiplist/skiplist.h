#ifndef __SKIPLIST_H__
#define __SKIPLIST_H__
#include <vector>
#include <random>
#include <iostream>

template<class Key, class Value> struct SkNode {
    Key key;
    Value value;
    std::vector<SkNode<Key, Value> *> forwardlist;
    SkNode(int level): forwardlist(level + 1, static_cast<SkNode<Key, Value> *>(nullptr)) {}
    SkNode(int level, const Key &key_, const Value &value_): SkNode(level) {
        key = key_;
        value = value_;
    }
    SkNode &operator= (const SkNode &other) {
        if (this != &other) {
            forwardlist = other.forwardlist;
            key = other.key;
            value = other.value;
        }
        return *this;
    }
};

template<class Key, class Value> class SkipList {
    SkNode<Key, Value> *header = new SkNode<Key, Value>(0);
    int GetInsertLevel();

public:
    SkipList() = default;
    ~SkipList();
    void Insert(const Key &key, const Value &value, int level = -1);
    void Remove(const Key &key);
    bool Search(const Key &key, Value &value);
    std::vector<std::pair<Key, Value>> RangeGet(const Key &k1_, const Key &k2_);
    int GetLevel () const { return header->forwardlist.size(); }

    void Debug () {
        int curlevel = header->forwardlist.size();
        std::cout << "curlevel: " << curlevel << std::endl;
        for (int i = curlevel - 1; i >= 0; i--) {
            std::cout << "level " << i << ":" << std::endl;
            SkNode<Key, Value> *start = header;
            while (start->forwardlist[i]) {
                std::cout << start->forwardlist[i]->key << " ";
                start = start->forwardlist[i];
            }
            std::cout << std::endl;
        }
        std::cout << "#######################################################" << std::endl;
    }
};

template<class Key, class Value> int SkipList<Key, Value>::GetInsertLevel() {
    int result = 0;
    std::random_device rd;
    while (rd() % 2) {
        ++result;
    }
    
    return result;
}

template<class Key, class Value> SkipList<Key, Value>::~SkipList () {
    SkNode<Key, Value> *start = header->forwardlist[0];
    while (start) {
        SkNode<Key, Value> *next = start->forwardlist[0];
        delete start;
        start = next;
    }
    delete header;
}

template<class Key, class Value> void SkipList<Key, Value>::Insert (const Key &key, const Value &value, int level) {
    int curlevel = header->forwardlist.size();
    std::vector<SkNode<Key, Value> *> prevs(curlevel, static_cast<SkNode<Key, Value> *>(nullptr));

    SkNode<Key, Value> *start = header;
    for (int i = curlevel - 1; i >= 0; i--) {
        while (start->forwardlist[i] && start->forwardlist[i]->key < key) {
            start = start->forwardlist[i];
        }

        prevs[i] = start;
    }
    if (start->forwardlist[0] && start->forwardlist[0]->key == key) {
        return;
    }

    if (level == -1) {
        level = GetInsertLevel();
    }
    if (level >= curlevel) {
        header->forwardlist.push_back(static_cast<SkNode<Key, Value> *>(nullptr));
        level = curlevel;
    }
    SkNode<Key, Value> *newnode = new SkNode<Key, Value>(level, key, value);
    
    for (int i = level; i >= 0; i--) {
        if (i == prevs.size()) {
            newnode->forwardlist[i] = header->forwardlist[i];
            header->forwardlist[i] = newnode;
        } else {
            newnode->forwardlist[i] = prevs[i]->forwardlist[i];
            prevs[i]->forwardlist[i] = newnode;
        }
    }
}

template<class Key, class Value> void SkipList<Key, Value>::Remove (const Key &key) {
    int curlevel = header->forwardlist.size();
    std::vector<SkNode<Key, Value> *> prevs(curlevel, static_cast<SkNode<Key, Value> *>(nullptr));
    SkNode<Key, Value> *start = header;
    for (int i = curlevel - 1; i >= 0; i--) {
        while (start->forwardlist[i] && start->forwardlist[i]->key < key) {
            start = start->forwardlist[i];
        }

        prevs[i] = start;
    }

    SkNode<Key, Value> *delnode = start->forwardlist[0];
    if (delnode && delnode->key == key) {
        for (int i = curlevel - 1; i >= 0; i--) {
            if (prevs[i]->forwardlist[i] && prevs[i]->forwardlist[i]->key == key) {
                prevs[i]->forwardlist[i] = delnode->forwardlist[i];
                if (prevs[i] == header && !prevs[i]->forwardlist[i]) {
                    header->forwardlist.pop_back();;
                }
            }
        }

        delete delnode;
    }
}

template<class Key, class Value> bool SkipList<Key, Value>::Search (const Key &key, Value &value) {
    int curlevel = header->forwardlist.size();
    SkNode<Key, Value> *start = header;
    for (int i = curlevel - 1; i >= 0; i--) {
        while (start->forwardlist[i] && start->forwardlist[i]->key < key) {
            start = start->forwardlist[i];
        }
    }
    
    SkNode<Key, Value> *next = start->forwardlist[0];
    if (next && next->key == key) {
        value = next->value;
        return true;
    }
    
    return false;
}

template<class Key, class Value> std::vector<std::pair<Key, Value>> SkipList<Key, Value>::RangeGet (const Key &k1_, const Key &k2_) {
    Key k1(std::min(k1_, k2_)), k2(std::max(k1_, k2_));
    SkNode<Key, Value> *start = header, *st;
    int curlevel = header->forwardlist.size();
    
    for (int i = curlevel - 1; i >= 0; i--) {
        while (start->forwardlist[i] && start->forwardlist[i]->key < k1) {
            start = start->forwardlist[i];
        }
    }

    st = start->forwardlist[0];
    std::vector<std::pair<Key, Value>> res;
    if (st) {
        while (st && st->key <= k2) {
            res.emplace_back(st->key, st->value);
            st = st->forwardlist[0];
        }
    }

    return res;
}
#endif
