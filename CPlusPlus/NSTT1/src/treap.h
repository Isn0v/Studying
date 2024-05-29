#include <vector>

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <random>
#include <stack>
#include <utility>

template <typename T> class Treap {

private:
  struct Node {
    T key;
    int priority;
    Node *left, *right, *parent;

    Node(T key, Node *parent)
        : key(key), left(nullptr), right(nullptr), parent(parent) {
      std::random_device rd;
      std::mt19937_64 gen(rd());
      std::uniform_int_distribution<int> dis;

      priority = dis(gen);
    }

    Treap<T>::Node *leftMost() {
      if (!left)
        return this;
      return left->leftMost();
    }

    Treap<T>::Node *rightMost() {
      if (!right)
        return this;
      return right->rightMost();
    }

    bool operator==(const Node &other) const {
      return key == other.key && priority == other.priority;
    }

    bool operator!=(const Node &other) const { return !(*this == other); }
  };

  Node *root;

  Node *copyNodes(Node *node, Node *parent) {
    if (!node)
      return nullptr;
    Node *newNode = new Node(node->key, parent);
    newNode->left = copyNodes(node->left, newNode);
    newNode->right = copyNodes(node->right, newNode);
    return newNode;
  }

  bool containsRecursive(Node *node, T value) {
    if (node == nullptr) {
      return false;
    }
    if (node->key == value) {
      return true;
    }
    return containsRecursive(node->left, value) ||
           containsRecursive(node->right, value);
  }

  void clear(Node *t) {
    if (t != nullptr) {
      clear(t->left);
      clear(t->right);
      delete t;
    }
  }

  void insert(Node *&t, Node *it) {
    if (!t)
      t = it;
    else if (it->priority > t->priority)
      split(t, it->key, it->left, it->right), t = it;
    else
      insert(t->key <= it->key ? t->right : t->left, it);
  }

  void erase(Node *&t, int key) {
    if (t->key == key) {
      Node* th = t;
      merge(t, t->left, t->right);
      delete th;
    } else
      erase(key < t->key ? t->left : t->right, key);
  }

  void split(Node *t, T key, Node *&l, Node *&r) {
    if (!t) {
      l = nullptr;
      r = nullptr;
      return;
    }
    if (t->key < key) {
      split(t->right, key, t->right, r);
      l = t;
    } else {
      split(t->left, key, l, t->left);
      r = t;
    }
  }

  void merge(Node* &t, Node* l, Node* r) {
    if (!l || !r)
      t = l ? l : r;
    else if (l->priority > r->priority)
      merge(l->right, l->right, r), t = l;
    else
      merge(r->left, l, r->left), t = r;
  }

public:
  class TreapIterator {
  private:
    typename Treap<T>::Node *current;
    bool reverse;

    typename Treap<T>::Node *advanceToNext(typename Treap<T>::Node *node,
                                           bool reverse) {
      if (node == nullptr) {
        return nullptr;
      }
      if (reverse) {
        if (node->left != nullptr) {
          return node->left->rightMost();
        }
        while (node->parent != nullptr && node == node->parent->left) {
          node = node->parent;
        }
        return node->parent;
      } else {
        if (node->right != nullptr) {
          return node->right->leftMost();
        }
        while (node->parent != nullptr && node == node->parent->right) {
          node = node->parent;
        }
        return node->parent;
      }
    }

    void advanceToNext() { current = advanceToNext(current, reverse); }

  public:
    TreapIterator(typename Treap<T>::Node *root, bool reverse = false)
        : current(root), reverse(reverse) {}

    bool hasNext() const { return current != nullptr; }

    bool operator!=(const TreapIterator &other) const {
      return current != other.current;
    }

    TreapIterator &operator++() {
      current = advanceToNext(current, reverse);
      return *this;
    }

    T operator*() const {
      if (!hasNext()) {
        throw std::out_of_range("No next element");
      }
      return current->key;
    }

    typename Treap<T>::Node *operator->() const { return current; }

    T next() {
      if (!hasNext()) {
        throw std::out_of_range("No next element");
      }

      T result = current->key;

      current = advanceToNext(current, reverse);
      return result;
    }
  };

  Treap() : root(nullptr) {}

  Treap(const Treap &other) : root(copyNodes(other.root, nullptr)) {}

  Treap(Treap &&other) : root(other.root) { other.root = nullptr; }

  ~Treap() { clear(root); }

  Treap &operator=(const Treap &other) {
    if (this != &other) {
      clear(root);
      root = copyNodes(other.root, nullptr);
    }
    return *this;
  }

  Treap &operator=(Treap &&other) {
    if (this != &other) {
      delete this->root;
      this->root = other.root;
      other.root = nullptr;
    }

    return *this;
  }

  Treap(const std::vector<T> &vec) {
    for (auto &elem : vec) {
      insert(elem);
    }
  }

  void insert(T value) { insert(root, new Node(value, nullptr)); }

  void erase(int value) { erase(root, value); }

  void clear() {
    clear(root);
    root = nullptr;
  }

  bool contains(T value) { return this->containsRecursive(this->root, value); }

  bool empty() { return root == nullptr; }

  void getAllElements(Node *node, std::vector<T> &vec) const {
    if (node == nullptr) {
      return;
    }
    getAllElements(node->left, vec);
    vec.push_back(node->key);
    getAllElements(node->right, vec);
  }

  TreapIterator iterator() { return TreapIterator(root); }

  bool operator==(const Treap<T> &other) const {
    std::vector<T> thisTreapVec, otherTreapVec;
    getAllElements(this->root, thisTreapVec);
    getAllElements(other.root, otherTreapVec);
    return thisTreapVec == otherTreapVec;
  }

  TreapIterator begin() { return TreapIterator(root->leftMost()); }

  TreapIterator end() { return TreapIterator(nullptr); }

  Treap<T> copy() { return Treap<T>(*this); }
};