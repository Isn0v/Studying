#include <vector>

#include <cstdlib>
#include <random>
#include <utility>
#include <ctime>
#include <iostream>
#include <stack>

template <typename T>
class TreapIterator;

template <typename T>
class Treap
{

public:
    struct Node
    {
        T key;
        int priority;
        Node *left, *right, *parent;

        Node(T key, Node *parent) : key(key), left(nullptr), right(nullptr), parent(parent)
        {
            std::random_device rd;
            std::mt19937_64 gen(rd());
            std::uniform_int_distribution<int> dis;

            priority = dis(gen);
        }
    };

    Treap() : root(nullptr) {}

    Treap(const Treap &other) : root(copyNodes(other.root, nullptr)) {}

    Treap(Treap &&other) : root(other.root)
    {
        other.root = nullptr;
    }

    ~Treap()
    {
        clear(root);
    }

    Treap &operator=(const Treap &other)
    {
        if (this != &other)
        {
            clear(root);
            root = copyNodes(other.root, nullptr);
        }
        return *this;
    }

    Treap &operator=(Treap &&other)
    {
        if (this != &other)
        {
            delete this->root;
            this->root = other.root;
            other.root = nullptr;
        }

        return *this;
    }

    Treap(const std::vector<T> &vec)
    {
        for (auto &elem : vec)
        {
            insert(elem);
        }
    }

    void clear()
    {
        clear(root);
        root = nullptr;
    }

    void insert(int key)
    {
        auto [l, r] = split(root, key);
        root = merge(merge(l, new Node(key, nullptr)), r);
    }

    void erase(int key)
    {
        auto [l, r] = split(root, key);
        auto [l1, r1] = split(l, key - 1);
        root = merge(l1, r);
        delete r1;
    }

    bool contains(T value)
    {
        return this->containsRecursive(this->root, value);
    }

    bool empty()
    {
        return root == nullptr;
    }

    void getAllElements(Node *node, std::vector<T> &vec) const
    {
        if (node == nullptr)
        {
            return;
        }
        getAllElements(node->left, vec);
        vec.push_back(node->key);
        getAllElements(node->right, vec);
    }

    TreapIterator<T> iterator()
    {
        return TreapIterator<T>(root);
    }

    bool operator==(const Treap<T> &other) const
    {
        std::vector<T> thisTreapVec, otherTreapVec;
        getAllElements(this->root, thisTreapVec);
        getAllElements(other.root, otherTreapVec);
        return thisTreapVec == otherTreapVec;
    }

    TreapIterator<T> begin()
    {
        return TreapIterator<T>(root);
    }

    TreapIterator<T> end()
    {
        return TreapIterator<T>(nullptr);
    }

    Treap<T> copy()
    {
        return Treap<T>(*this);
    }

private:
    Node *root;

    Node *copyNodes(Node *node, Node *parent)
    {
        if (!node)
            return nullptr;
        Node *newNode = new Node(node->key, parent);
        newNode->left = copyNodes(node->left, newNode);
        newNode->right = copyNodes(node->right, newNode);
        return newNode;
    }

    bool containsRecursive(Node *node, T value)
    {
        if (node == nullptr)
        {
            return false;
        }
        if (node->key == value)
        {
            return true;
        }
        return containsRecursive(node->left, value) || containsRecursive(node->right, value);
    }

    void clear(Node *t)
    {
        if (t != nullptr)
        {
            clear(t->left);
            clear(t->right);
            delete t;
        }
    }

    std::pair<Node *, Node *> split(Node *t, int key)
    {
        if (!t)
            return {nullptr, nullptr};
        if (key < t->key)
        {
            auto [l, r] = split(t->left, key);
            t->left = r;
            if (r)
                r->parent = t;
            return {l, t};
        }
        else
        {
            auto [l, r] = split(t->right, key);
            t->right = l;
            if (l)
                l->parent = t;
            return {t, r};
        }
    }

    Node *merge(Node *l, Node *r)
    {
        if (!l || !r)
            return l ? l : r;
        if (l->priority > r->priority)
        {
            l->right = merge(l->right, r);
            l->right->parent = l;
            return l;
        }
        else
        {
            r->left = merge(l, r->left);
            r->left->parent = r;
            return r;
        }
    }
};
// =================================================================================
// do
template <typename T>
class TreapIterator
{
private:
    typename Treap<T>::Node *current;
    bool reverse;

    typename Treap<T>::Node *advanceToNext(typename Treap<T>::Node *node, bool reverse)
    {
        if (node == nullptr)
        {
            return nullptr;
        }
        if (reverse)
        {
            if (node->left != nullptr)
            {
                return advanceToNext(node->left, reverse);
            }
            else
            {
                return (node->parent == nullptr || node == node->parent->left) ? node->parent : advanceToNext(node->parent, reverse);
            }
        }
        else
        {
            if (node->right != nullptr)
            {
                return advanceToNext(node->right, reverse);
            }
            else
            {
                return (node->parent == nullptr || node == node->parent->right) ? node->parent : advanceToNext(node->parent, reverse);
            }
        }
    }

    void advanceToNext()
    {
        current = advanceToNext(current, reverse);
    }

public:
    TreapIterator(typename Treap<T>::Node *root, bool reverse = false) : current(root), reverse(reverse) {}

    bool hasNext() const
    {
        return current != nullptr;
    }

    bool operator!=(const TreapIterator &other) const
    {
        return current != other.current;
    }

    TreapIterator &operator++()
    {
        if (!reverse)
        {
            advanceToNext();
            return *this;
        }
        else
        {

            throw std::runtime_error("Reverse iterator can't be incremented");
        }
    }

    T operator*() const
    {
        return current->key;
    }

    typename Treap<T>::Node *operator->() const
    {
        return current;
    }

    T next()
    {
        T result = current->key;
        advanceToNext();
        return result;
    }

    TreapIterator operator--(int)
    {
        if (reverse)
        {

            advanceToNext();
            return *this;
        }
        else
        {
            throw std::runtime_error("Forward iterator can't be decremented");
        }
    }
};
