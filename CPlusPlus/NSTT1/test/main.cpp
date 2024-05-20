#include <gtest/gtest.h>
// #include "../src/treap.cpp"
#include <treap.cpp>
#include <instance_limiter.h>

template <typename T>
class TreapTest : public ::testing::Test
{
protected:
    Treap<T> treap;
};

typedef ::testing::Types<int> Implementations;
TYPED_TEST_SUITE(TreapTest, Implementations);

TYPED_TEST(TreapTest, InitializesCorrectly)
{
    EXPECT_TRUE(this->treap.empty());
}

TYPED_TEST(TreapTest, InsertsElementsCorrectly)
{

    this->treap.insert(5);
    EXPECT_FALSE(this->treap.empty());
    EXPECT_TRUE(this->treap.contains(5));
}

TYPED_TEST(TreapTest, ClearsCorrectly)
{
    this->treap.insert(5);
    this->treap.insert(3);
    this->treap.insert(7);
    this->treap.clear();
    EXPECT_TRUE(this->treap.empty());
}

TYPED_TEST(TreapTest, ErasesElementsCorrectly)
{

    this->treap.insert(5);
    this->treap.insert(3);
    this->treap.insert(7);
    this->treap.erase(3);
}

TYPED_TEST(TreapTest, CopyConstructorCreatesIndependentCopy)
{
    Treap<TypeParam> copyConstructed = this->treap;

    copyConstructed.insert(40);

    ASSERT_FALSE(this->treap.contains(40));
}

TYPED_TEST(TreapTest, CopyConstructorCreatesEquivalentData)
{
    Treap<int> copyConstructed(this->treap);

    copyConstructed.insert(40);
    ASSERT_FALSE(this->treap == copyConstructed);
}

template <typename U>
Treap<U> createMoveTreapWithValue(int val)
{
    Treap<U> newTreap;
    newTreap.insert(val);

    return newTreap;
}

TYPED_TEST(TreapTest, MoveConstructorAndAssignmentOperatorCheck)
{
    Treap<TypeParam> newTreap = std::move(createMoveTreapWithValue<TypeParam>(4));
    EXPECT_TRUE(newTreap.contains(4));
    newTreap.clear();

    newTreap = std::move(createMoveTreapWithValue<TypeParam>(5));
    EXPECT_TRUE(newTreap.contains(5));
}

TYPED_TEST(TreapTest, IteratorBegin)
{
    this->treap.insert(10);
    this->treap.insert(5);
    this->treap.insert(15);

    TreapIterator<int> it = this->treap.iterator();
    EXPECT_TRUE(it.hasNext());
    EXPECT_EQ(it.next(), 5);
}

TYPED_TEST(TreapTest, IteratorTraversal)
{
    this->treap.insert(10);
    this->treap.insert(5);
    this->treap.insert(15);

    TreapIterator<int> it = this->treap.iterator();
    std::vector<int> elements;
    while (it.hasNext())
    {
        elements.push_back(it.next());
    }
    EXPECT_EQ(elements, (std::vector<int>{5, 10, 15}));
}

TYPED_TEST(TreapTest, IteratorNoElements)
{
    Treap<int> emptyTreap;
    TreapIterator<int> it = emptyTreap.iterator();
    EXPECT_FALSE(it.hasNext());
}

TYPED_TEST(TreapTest, IteratorThrowException)
{
    Treap<int> emptyTreap;
    TreapIterator<int> it = emptyTreap.iterator();
    EXPECT_THROW(it.next(), std::out_of_range);
}

TYPED_TEST(TreapTest, RangeBasedForEmpty){
    Treap<int> emptyTreap;
    int sum = 0;
    for (const auto& element : emptyTreap) {
        sum += element;
    }
    EXPECT_EQ(sum, 0);
}

TYPED_TEST(TreapTest, RangeBasedForWithElements){
    Treap<int> treap;
    treap.insert(5);
    treap.insert(10);
    treap.insert(15);
    int sum = 0;
    for (const auto& element : treap) {
        sum += element;
    }
    EXPECT_EQ(sum, 30);
}

// ---------------------------------------------------------------------

class MyClass : public InstanceLimiter<MyClass, 2>
{
public:
    MyClass() : InstanceLimiter()
    {
        // ...
    }

    ~MyClass()
    {
        // ...
    }
};

TEST(InstanceLimiterTest, ThrowExceptionWhenLimitReached)
{
    // EXPECT_NO_THROW(MyClass a{});
    MyClass a{};
    MyClass b{};
    // EXPECT_NO_THROW(MyClass b{});
    EXPECT_THROW(MyClass c{}, std::runtime_error);
}

TEST(InstanceLimiterTest, GetInstanceCountCorrect)
{
    MyClass a{};
    EXPECT_EQ(MyClass::getInstanceCount(), 1);
    // EXPECT_EQ(InstanceLimiter<MyClass, 2>::getInstanceCount(), 1);

    MyClass b{};
    EXPECT_EQ(MyClass::getInstanceCount(), 2);
}

TEST(InstanceLimiterTest, DestructorDecrementInstanceCount)
{
    MyClass a{};
    EXPECT_EQ(MyClass::getInstanceCount(), 1);

    {
        MyClass b{};
        EXPECT_EQ(MyClass::getInstanceCount(), 2);
    }

    EXPECT_EQ(MyClass::getInstanceCount(), 1);

    {
        MyClass c{};
        EXPECT_THROW(MyClass d{}, std::runtime_error);
    }

    EXPECT_EQ(MyClass::getInstanceCount(), 1);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}