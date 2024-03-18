#include <gtest/gtest.h>
#include "../src/treap.cpp" 


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
    EXPECT_TRUE(this->treap.empty());
}

// Test insertion functionality
TYPED_TEST(TreapTest, InsertsElementsCorrectly) {

    this->treap.insert(5);
    EXPECT_FALSE(this->treap.empty());
    EXPECT_TRUE(this->treap.contains(5));
}

// Test clear functionality
TYPED_TEST(TreapTest, ClearsCorrectly) {
    this->treap.insert(5);
    this->treap.insert(3);
    this->treap.insert(7);
    this->treap.clear();
    EXPECT_TRUE(this->treap.empty());
}

// Test erase functionality
TYPED_TEST(TreapTest, ErasesElementsCorrectly) {

    this->treap.insert(5);
    this->treap.insert(3);
    this->treap.insert(7);
    this->treap.erase(3);
}

TYPED_TEST(TreapTest, CopyConstructorCreatesIndependentCopy) {
    Treap<TypeParam> copyConstructed = this->treap;

    copyConstructed.insert(40);

    ASSERT_FALSE(this->treap.contains(40));
}

TYPED_TEST(TreapTest, CopyConstructorCreatesEquivalentData) {
    Treap<int> copyConstructed(this->treap);

    copyConstructed.insert(40);
    ASSERT_FALSE(this->treap == copyConstructed);
}

template <typename U>
Treap<U> createMoveTreapWithValue(int val){
    Treap<U> newTreap;
    newTreap.insert(val);

    return newTreap;
}


TYPED_TEST(TreapTest, MoveConstructorAndAssignmentOperatorCheck){
    Treap<TypeParam> newTreap = std::move(createMoveTreapWithValue<TypeParam>(4));
    EXPECT_TRUE(newTreap.contains(4));
    newTreap.clear();

    newTreap = std::move(createMoveTreapWithValue<TypeParam>(5));
    EXPECT_TRUE(newTreap.contains(5));
}

int main(int argc, char **argv) {
    // ::testing::InitGoogleTest(&argc, argv);
    // return RUN_ALL_TESTS();
    int* a = new int[10];
    a[5] = 0;
    if (a[argc])
        printf("xx\n");
    return 0;

}