#include <gtest/gtest.h>
#include "../src/treap.cpp" 

template <typename T>
bool isBST(TreapNode<T>* node, T min_value, T max_value) {
    if (node == nullptr) return true;
    if (node->key < min_value || node->key > max_value) return false;
    return isBST(node->left, min_value, node->key) && isBST(node->right, node->key, max_value);
}

template <typename T>
class TreapTest : public ::testing::Test {
protected:
    Treap<T> treap;

};

// Define types to run the same tests over different types
typedef ::testing::Types<int> Implementations;
TYPED_TEST_SUITE(TreapTest, Implementations);

// Test initialization of Treap
TYPED_TEST(TreapTest, InitializesCorrectly) {
    EXPECT_EQ(this->treap.getRoot(), nullptr);
}

// Test insertion functionality
TYPED_TEST(TreapTest, InsertsElementsCorrectly) {
    this->treap.insert(5);
    auto root = this->treap.getRoot();
    ASSERT_NE(root, nullptr);
    EXPECT_EQ(root->key, 5);
    EXPECT_TRUE(isBST(root, std::numeric_limits<TypeParam>::min(), std::numeric_limits<TypeParam>::max()));
}

// Test clear functionality
TYPED_TEST(TreapTest, ClearsCorrectly) {
    this->treap.insert(5);
    this->treap.insert(3);
    this->treap.insert(7);
    this->treap.clear();
    EXPECT_EQ(this->treap.getRoot(), nullptr);
}

// Test erase functionality
TYPED_TEST(TreapTest, ErasesElementsCorrectly) {
    this->treap.insert(5);
    this->treap.insert(3);
    this->treap.insert(7);
    this->treap.erase(3);
    auto root = this->treap.getRoot();
    EXPECT_TRUE(isBST(root, std::numeric_limits<TypeParam>::min(), std::numeric_limits<TypeParam>::max()));
}

TYPED_TEST(TreapTest, CopyConstructorCreatesIndependentCopy) {
    Treap<TypeParam> copyConstructed = this->treap;

    copyConstructed.insert(40);

    ASSERT_FALSE(this->treap.contains(40));
}

TYPED_TEST(TreapTest, CopyConstructorCreatesEquivalentData) {
    // Use the copy constructor
    Treap<int> copyConstructed(this->treap);

    copyConstructed.insert(40);
    ASSERT_FALSE(this->treap == copyConstructed);
}



int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}