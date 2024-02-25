#include <gtest/gtest.h>
#include "../src/Line/Line.h" 

TEST(PointLine, PointLine) {
    Line l1({2,2},{5,5});
    Line l2({1,5},{5,1});
    EXPECT_TRUE(l1.hasIntersection(l2));
    Point p = l1.findIntersection(l2);
    EXPECT_EQ(p.x, 3);
    EXPECT_EQ(p.y, 3);
    Line l3({5,1},{1,5});
    EXPECT_FALSE(l2.hasIntersection(l3));
    Line l4({1,1},{7,2});
    Line l5=l4.findPerpendicular({3,3});
    Line l6({1,2},{7,3});
    EXPECT_TRUE(l6.isOrthogonal(l5));
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}