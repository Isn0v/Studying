#include <cstdlib>
#include <utility>
#include <ctime>
#include <iostream>
#include <gtest/gtest.h>


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

    std::string inOrderNodes(TreapNode<T>* node)
    {
        if (node)
        {
            return inOrderNodes(node->left) + std::string(" ") + std::to_string(node->key) + std::string(" ") + inOrderNodes(node->right);
        }
        return "";
    }

public:
    Treap() : root(nullptr) {}

    ~Treap()
    {
        clear(root);
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

    std::string inOrder()
    {
        return inOrderNodes(root);
    }

    // overload <<
    friend std::ostream &operator<<(std::ostream &os, Treap &t)
    {
        os << t.inOrder();
        return os;
    }

};

// int main()
// {
//     srand(time(nullptr));

//     Treap<int>* treap = new Treap<int>();
//     for (int i = 0; i < 10; i++)
//     {
//         treap->insert(i);
//     }

//     treap->erase(4);
//     treap->erase(5);

//     std::cout << *treap << std::endl;

//     // delete treap;

//     return 0;
// }