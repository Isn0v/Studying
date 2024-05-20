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
        Node *left, *right;

        Node(T key) : key(key), left(nullptr), right(nullptr)
        {
            std::random_device rd;
            std::mt19937_64 gen(rd());
            std::uniform_int_distribution<int> dis;

            priority = dis(gen);
        }
    };

    Treap() : root(nullptr) {}

    Treap(const Treap &other) : root(copyNodes(other.root)) {}

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
            root = copyNodes(other.root);
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
        root = merge(merge(l, new Node(key)), r);
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

    Node *copyNodes(Node *node)
    {
        if (!node)
            return nullptr;
        Node *newNode = new Node(node->key);
        newNode->priority = node->priority;
        newNode->left = copyNodes(node->left);
        newNode->right = copyNodes(node->right);
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
            return {l, t};
        }
        else
        {
            auto [l, r] = split(t->right, key);
            t->right = l;
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
            return l;
        }
        else
        {
            r->left = merge(l, r->left);
            return r;
        }
    }
};

template <typename T>
class TreapIterator
{
private:
    std::stack<typename Treap<T>::Node *> stack;
    typename Treap<T>::Node *current;

    void pushLeft(typename Treap<T>::Node *node)
    {
        while (node != nullptr)
        {
            stack.push(node);
            node = node->left;
        }
    }

public:
    TreapIterator(typename Treap<T>::Node *root) : current(root)
    {
        pushLeft(root);
    }

    ~TreapIterator()
    {
        stack = std::stack<typename Treap<T>::Node *>();
        // current = nullptr;
    }

    bool hasNext() const
    {
        return !stack.empty();
    }

    bool operator!=(const TreapIterator &other) const
    {
        return stack != other.stack;
    }

    TreapIterator &operator++()
    {
        if (stack.empty())
        {
            throw std::out_of_range("No more elements in the Treap");
        }
        current = stack.top();
        stack.pop();
        current = current->right;
        pushLeft(current);
        return *this;
    }

    T operator*() const
    {
        // if (current == nullptr){
        //     throw std::out_of_range("No more elements in the Treap");
        // }
        return current->key;
    }

    typename Treap<T>::Node *operator->() const
    {
        return current;
    }

    T next()
    {
        if (stack.empty())
        {
            throw std::out_of_range("No more elements in the Treap");
        }
        current = stack.top();
        stack.pop();
        T key = current->key;
        current = current->right;
        pushLeft(current);
        return key;
    }
};
