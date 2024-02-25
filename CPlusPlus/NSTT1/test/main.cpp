#include <gtest/gtest.h>
#include "../src/treap.cpp" // Assuming the Treap class is part of this file

// Helper function to check if the Treap is a valid binary search tree
template <typename T>
bool isBST(TreapNode<T>* node, T min_value, T max_value) {
    if (node == nullptr) return true;
    if (node->key < min_value || node->key > max_value) return false;
    return isBST(node->left, min_value, node->key) && isBST(node->right, node->key, max_value);
}

// Test fixture for Treap
template <typename T>
class TreapTest : public ::testing::Test {
protected:
    Treap<T> treap;

    // You can define helper methods here if needed
};

// Define types to run the same tests over different types
typedef ::testing::Types<int, char> Implementations;
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
    // More checks can be added to validate the structure after the erase operation
}

// More tests can be added here...

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}