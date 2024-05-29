#include <vector>

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <random>
#include <stack>
#include <utility>

std::random_device rd;
// auto seed = rd();
auto seed = 3718554003;

std::mt19937_64 gen(seed);
std::uniform_int_distribution<int> dis;

template <typename T> class Treap {

private:
  struct Node {
    T key;
    int priority;
    Node *left, *right, *parent;

    Node(T key, Node *parent)
        : key(key), left(nullptr), right(nullptr), parent(parent) {

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

    std::pair<Treap<T>::Node *, Treap<T>::Node *> split(T value) {
      if (key < value) {
        if (!right)
          return [ this, nullptr ];
        auto [leftNode, rightNode] = right->split(value);
        return [ this, rightNode ];
      } else {
        if (!left)
          return [ nullptr, this ];
        auto [leftNode, rightNode] = left->split(value);
        return [ leftNode, this ];
      }
    }

    Treap<T>::Node *merge(Treap<T>::Node *other) {
      if (!other)
        return this;
      if (key < other->key) {
        if (!right)
          return [ this, other ];
        return right->merge(other);
      } else {
        if (!left)
          return [ other, this ];
        return left->merge(other);
      }
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

  Treap() : root(nullptr) {
    std::cout << "Treap created with seed: " << seed << std::endl;
  }

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

  TreapIterator iterator(bool reverse = false) {
    if (!reverse) {
      return TreapIterator(root->leftMost(), false);
    } else {
      return TreapIterator(root->rightMost(), true);
    }
  }

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