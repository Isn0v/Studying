#include <scoped_pointer.h>
#include <gtest/gtest.h>

// Mock class to test deep copy
class MockClass {
public:
    MockClass(int value) : value_(value) {}
    int GetValue() const { return value_; }

private:
    int value_;
};

// Test fixture for ScopedPointerDeep
class ScopedPointerDeepTest : public ::testing::Test {
protected:
    ScopedPointerDeep<MockClass> pointer_;
};

TEST_F(ScopedPointerDeepTest, HandlesConstruction) {
    MockClass* raw_pointer = new MockClass(42);
    ScopedPointerDeep<MockClass> deep_pointer(raw_pointer);
    ASSERT_EQ(deep_pointer->GetValue(), 42);
}

TEST_F(ScopedPointerDeepTest, HandlesCopyConstruction) {
    ScopedPointerDeep<MockClass> original(new MockClass(42));
    ScopedPointerDeep<MockClass> copy = original;
    ASSERT_EQ(original->GetValue(), copy->GetValue());
}

TEST_F(ScopedPointerDeepTest, HandlesCopyAssignment) {
    ScopedPointerDeep<MockClass> original(new MockClass(42));
    ScopedPointerDeep<MockClass> copy(new MockClass(0));
    copy = original;
    ASSERT_EQ(original->GetValue(), copy->GetValue());
}

// Test fixture for ScopedPointerTransfered
class ScopedPointerTransferedTest : public ::testing::Test {
protected:
    ScopedPointerTransfered<MockClass> pointer_;
};

TEST_F(ScopedPointerTransferedTest, HandlesConstruction) {
    MockClass* raw_pointer = new MockClass(42);
    ScopedPointerTransfered<MockClass> transfered_pointer(raw_pointer);
    ASSERT_EQ(transfered_pointer->GetValue(), 42);
}

TEST_F(ScopedPointerTransferedTest, HandlesMoveConstruction) {
    ScopedPointerTransfered<MockClass> original(new MockClass(42));
    ScopedPointerTransfered<MockClass> moved = std::move(original);
    ASSERT_EQ(moved->GetValue(), 42);
    ASSERT_EQ(original.operator->(), nullptr); // original should have been set to nullptr
}

TEST_F(ScopedPointerTransferedTest, HandlesMoveAssignment) {
    ScopedPointerTransfered<MockClass> original(new MockClass(42));
    ScopedPointerTransfered<MockClass> moved(new MockClass(0));
    moved = std::move(original);
    ASSERT_EQ(moved->GetValue(), 42);
    ASSERT_EQ(original.operator->(), nullptr); // original should have been set to nullptr
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}