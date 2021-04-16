#include "../../lib/googletest/googletest/include/gtest/gtest.h"
#include "../../includes/mcpp.hpp"

using var::matrix;

// tes_case_name    test_name
TEST(initails, declaration){
    // declaration -1
    matrix<int> m1(2, 5);
    ASSERT_EQ(2, m1.row());
    ASSERT_EQ(5, m1.col());
    ASSERT_EQ(5*2, m1.row()*m1.col());

    // declaration -2
    matrix<int> m2 = {{2, 3}, {3, 4}};
    ASSERT_EQ(2, m2[0][0]);
    ASSERT_EQ(3, m2[0][1]);
    ASSERT_EQ(4, m2[1][1]);

    // declaration -3
    matrix<int> m3;
    ASSERT_EQ(0, m3.row());
    ASSERT_EQ(0, m3.col());
}

TEST(functionality, insert_row_col){
    // no size given 
    matrix<int> m1;

    // colum 
    std::vector<int> a = {0, 1, 2, 3};
    m1.insert_col(a);
    ASSERT_EQ(a.size(), m1.row());
    ASSERT_EQ(1, m1.col());
    for(int i = 0; i < m1.row(); i++){
        ASSERT_EQ(m1[i][0], a[i]);
    }

    // row
    m1.resize(0, 0); 
    m1.insert_row(a);
    ASSERT_EQ(1, m1.row());
    ASSERT_EQ(a.size(), m1.col());
    for(int i = 0; i < m1.col(); i++){
        ASSERT_EQ(m1[0][i], a[i]);
    }

    // size is given
    matrix<float> m2(4, 3);

    // colum 
    m2.insert_col({0, 1, 2, 3});
    ASSERT_EQ(4, m2.row());
    ASSERT_EQ(3+1, m2.col());
    for(int i = 0; i < m1.row(); i++){
        ASSERT_EQ(m2[i][m2.col()-1], a[i]);
    }

    // row
    m2.resize(2, 4); 
    m2.insert_row({0, 1, 2, 3});
    ASSERT_EQ(2+1, m2.row());
    ASSERT_EQ(4, m2.col());
    for(int i = 0; i < m1.col(); i++){
        ASSERT_EQ(m2[m2.row()-1][i], a[i]);
    }
}

TEST(functionality, insert_row_col_at)
{
    std::vector<int> a = {1, 2, 3};
    // 0 col and 0 row
    matrix<int> m3;
    try{
        m3.insert_row(0, a);
    }
    catch(...){
        
    }

    // 3 rows, 3 colums
    matrix<int> m2(3, 3);

    // row
    m2.insert_row(1, a);
    ASSERT_EQ(3+1, m2.row());
    ASSERT_EQ(3, m2.col());
    for(int j = 0; j < m2.col(); j++){
        ASSERT_EQ(m2[1][j], a[j]);
    }

    // colum 
    m2.resize(3, 3);
    m2.insert_col(1, a);
    ASSERT_EQ(3+1, m2.col());
    ASSERT_EQ(3, m2.row());
    for(int j = 0; j < m2.row(); j++){
        ASSERT_EQ(m2[j][1], a[j]);
    }

    // column and row 
    m2.resize(3, 4);
    std::vector<int> b = {1, 2, 3, 4};
    std::vector<int> c = {1, 2, 3, 4};
    m2.insert_row(1, b);
    m3.insert_col(1, c);
    ASSERT_EQ(3+1, m2.row());
    ASSERT_EQ(4+1, m2.col());
    table<int> tab = {
        {0, 1, 0, 0, 0},
        {1, 2, 2, 3, 4},
        {0, 3, 0, 0, 0},
        {0, 4, 0, 0, 0}
    };
    
    for(int i = 0; i < m2.row(); i++){
        for(int j = 0; j < m2.col(); j++){
            ASSERT_EQ(m2[i][j], tab[i][j]);
        }
    }

}

TEST(functionality, matrix_functions){
    matrix<double> m1(2, 2);
    ASSERT_TRUE(m1.is_square());

    m1 = {
        {1, 0},
        {0, 1}
        };

    ASSERT_TRUE(m1.is_identity());

    m1.resize(3, 3);
    m1.turn_to(10);
    for(int i = 0; i < m1.row(); i++){
        for(int j = 0; j < m1.col(); j++){
            ASSERT_EQ(m1[0][0], 10);
        }
    }

    ASSERT_EQ(m1.sum(), 10*m1.size());
}

TEST(operators, arithematic)
{
    
}

int main(int argc, char **argv)
{
   testing::InitGoogleTest(&argc, argv);
   return RUN_ALL_TESTS();
}