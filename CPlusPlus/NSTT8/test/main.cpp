#include "gtest/gtest.h"
#include <my_iostream.h>



int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
