#include "../../lib/googletest/googletest/include/gtest/gtest.h"
#include "../../includes/mcpp.hpp"

using var::matrix;

// tes_case_name    test_name
TEST(initails, declaration){
    // declaration -1
    matrix<int> m1(2, 5);
    ASSERT_EQ(2, m1.row());
    ASSERT_EQ(5, m1.col());

    // declaration -2
    matrix<int> m2 = {{2, 3}, {3, 4}};
    ASSERT_EQ(2, m2[0][0]);
    ASSERT_EQ(3, m2[0][1]);

    // declaration -3
    matrix<int> m3;
    ASSERT_EQ(0, m3.row());
    ASSERT_EQ(0, m3.col());
}

TEST(functionality, insert_row_col){
    // no size given 
    matrix<int> m1;

    // colum 
    m1.insert_col({0, 1, 2, 3});
    ASSERT_EQ(4, m1.row());
    ASSERT_EQ(1, m1.col());

    // // row
    // m1.resize(0, 0); 
    // m1.insert_row({0, 1, 2, 3});
    // ASSERT_EQ(1, m1.row());
    // ASSERT_EQ(4, m1.col());

    // // size is given
    // matrix<float> m2(4, 3);

    // // colum 
    // m2.insert_col({0, 1, 2, 3});
    // ASSERT_EQ(4, m2.row());
    // ASSERT_EQ(3+1, m2.col());
    // std::cout << m2;

    // // row
    // m2.resize(2, 4); 
    // m2.insert_row({0, 1, 2, 3});
    // ASSERT_EQ(2+1, m2.row());
    // ASSERT_EQ(4, m2.col());

}

int main(int argc, char **argv)
{
   testing::InitGoogleTest(&argc, argv);
   return RUN_ALL_TESTS();
}