#include <gtest/gtest.h>
#include "../src/Line/Line.h"

TEST(PointLine, findIntersectionCheck)
{
    Line l1({2, 2}, {5, 5});
    Line l2({1, 5}, {5, 1});
    EXPECT_TRUE(l1.hasIntersection(l2));

    auto pointOrNothing = l1.findIntersection(l2);
    EXPECT_NE(pointOrNothing, std::nullopt);
}

TEST(PointLine, findIntersectionCheckFalse){
    Line l1({2, 2}, {5, 5});
    Line l2({0, 0}, {1, 1});

    auto pointOrNothing = l1.findIntersection(l2);
    EXPECT_EQ(pointOrNothing, std::nullopt);
}

TEST(PointLine, IntersectionCheck) {
    Line l1({1, 5}, {5, 1});
    Line l2({5, 1}, {1, 5});
    EXPECT_FALSE(l1.hasIntersection(l2));
}

TEST(PointLine, orthogonalCheck) {
    Line l1({1, 1}, {7, 2});
    Line l2 = l1.findPerpendicular({3, 3});
    Line l3({1, 2}, {7, 3});
    EXPECT_TRUE(l3.isOrthogonal(l2));
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}