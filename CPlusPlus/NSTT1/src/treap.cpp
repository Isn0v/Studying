#include <vector>

#include <cstdlib>
#include <utility>
#include <ctime>
#include <iostream>

template <typename T>
class TreapNode
{
public:
    T key;
    int priority;
    TreapNode *left, *right;

    TreapNode(T key) : key(key), priority(rand()), left(nullptr), right(nullptr) {}
};

template <typename T>
class Treap
{
private:
    TreapNode<T> *root;

    TreapNode<T> *copyNodes(TreapNode<T> *node)
    {
        if (!node)
            return nullptr;
        TreapNode<T> *newNode = new TreapNode<T>(node->key);
        newNode->priority = node->priority;
        newNode->left = copyNodes(node->left);
        newNode->right = copyNodes(node->right);
        return newNode;
    }
    
    bool containsRecursive(TreapNode<T> *node, T value){
        if (node == nullptr){
            return false;
        }
        if (node->key == value){
            return true;
        }
        return containsRecursive(node->left, value) || containsRecursive(node->right, value);
    }
    


    void clear(TreapNode<T> *t)
    {
        if (t != nullptr)
        {
            clear(t->left);
            clear(t->right);
            delete t;
        }
    }

    std::pair<TreapNode<T> *, TreapNode<T> *> split(TreapNode<T> *t, int key)
    {
        if (!t)
            return {nullptr, nullptr};
        if (key < t->key)
        {
            auto [l, r] = split(t->left, key);
            t->left = r;
            return {l, t};
        }
        else
        {
            auto [l, r] = split(t->right, key);
            t->right = l;
            return {t, r};
        }
    }

    TreapNode<T> *merge(TreapNode<T> *l, TreapNode<T> *r)
    {
        if (!l || !r)
            return l ? l : r;
        if (l->priority > r->priority)
        {
            l->right = merge(l->right, r);
            return l;
        }
        else
        {
            r->left = merge(l, r->left);
            return r;
        }
    }

public:
    Treap() : root(nullptr) {}

    Treap(const Treap &other)
    {
        root = copyNodes(other.root);
    }

    ~Treap()
    {
        clear(root);
    }

    void clear()
    {
        clear(root);
        root = nullptr;
    }

    TreapNode<T> *getRoot() const
    {
        return root;
    }

    void insert(int key)
    {
        auto [l, r] = split(root, key);
        root = merge(merge(l, new TreapNode<T>(key)), r);
    }

    void erase(int key)
    {
        auto [l, r] = split(root, key);
        auto [l1, r1] = split(l, key - 1);
        root = merge(l1, r);
        delete r1;
    }

    bool contains(T value){
        return this->containsRecursive(this->root, value);
    }

    void asVector(TreapNode<T>* node, std::vector<T> &vec) const{
        if (node == nullptr){
            return;
        }
        asVector(node->left, vec);
        vec.push_back(node->key);
        asVector(node->right, vec);
    }

    Treap &operator=(const Treap &other)
    {
        if (this != &other)
        {
            clear(root);
            root = copyNodes(other.root);
        }
        return *this;
    }

    bool operator==(const Treap<T> &other) const{
        std::vector<T> thisTreapVec, otherTreapVec;
        asVector(this->root, thisTreapVec);
        asVector(other.root, otherTreapVec);
        return thisTreapVec == otherTreapVec;
    }

};
