#include "../src/diff.h"
#include "gtest/gtest.h"

class ExponentDiffTest : public ::testing::Test {
protected:
  void SetUp() override {
    // Setup any common objects or variables needed for the tests
  }

  void TearDown() override {
    // Clean up any resources
  }
};

TEST_F(ExponentDiffTest, ConstantExponent) {
  Expression *base = new Val(2);
  Expression *exponent = new Val(3);
  Exponent *exponentObj = new Exponent(base, exponent);

  Expression *result = exponentObj->diff("x");
}

TEST_F(ExponentDiffTest, VariableExponent) {

  Expression *base = new Var("x");
  Expression *exponent = new Val(3);
  Exponent *exponentObj = new Exponent(base, exponent);
}

TEST_F(ExponentDiffTest, AddDiffMethod) {
  Expression *left = new Val(2);
  Expression *right = new Val(3);
  Add *addObj = new Add(left, right);

  Expression *result = addObj->diff("x");
}

// Add more test cases as needed to cover all scenarios

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}