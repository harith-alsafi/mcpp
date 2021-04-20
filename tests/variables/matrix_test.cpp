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

TEST(functionality, push_row_col){
    // no size given 
    matrix<int> m1;

    // colum 
    std::vector<int> a = {0, 1, 2, 3};
    m1.push_col(a);
    ASSERT_EQ(a.size(), m1.row());
    ASSERT_EQ(1, m1.col());
    for(int i = 0; i < m1.row(); i++){
        ASSERT_EQ(m1[i][0], a[i]);
    }

    // row
    m1.resize(0, 0); 
    m1.push_row(a);
    ASSERT_EQ(1, m1.row());
    ASSERT_EQ(a.size(), m1.col());
    for(int i = 0; i < m1.col(); i++){
        ASSERT_EQ(m1[0][i], a[i]);
    }

    // size is given
    matrix<float> m2(4, 3);

    // colum 
    m2.push_col({0, 1, 2, 3});
    ASSERT_EQ(4, m2.row());
    ASSERT_EQ(3+1, m2.col());
    for(int i = 0; i < m1.row(); i++){
        ASSERT_EQ(m2[i][m2.col()-1], a[i]);
    }

    // row
    m2.resize(2, 4); 
    m2.push_row({0, 1, 2, 3});
    ASSERT_EQ(2+1, m2.row());
    ASSERT_EQ(4, m2.col());
    for(int i = 0; i < m1.col(); i++){
        ASSERT_EQ(m2[m2.row()-1][i], a[i]);
    }
}

TEST(functionality, insert_row_col)
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
    m2.insert_col(1, c);
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

TEST(functionality, row_col_op)
{
    matrix<int> m = {
        {9, 3, 10},
        {7, 6, 20},
        {10, 5, 19}
    };

    // sort rows
    // accending
    auto m_sorted = m.sort_rows();
    matrix<int> sorted = {
        {3, 9, 10},
        {6, 7, 20},
        {5, 10, 19}
    };
    ASSERT_TRUE(m_sorted == sorted);

    // desending 
    auto m_sorted_2 = m.sort_rows(0);
    matrix<int> sorted_2 = {
        {10, 9, 3},
        {20, 7, 6},
        {19, 10, 5}
    };
    ASSERT_TRUE(m_sorted_2 == sorted_2);

    // sort cols
    // accending 
    auto m_sorted_c = m.sort_cols();
    matrix<int> sorted_c = {
        {7, 3, 10},
        {9, 5, 19},
        {10, 6, 20}
    };
    ASSERT_TRUE(m_sorted_c == sorted_c);


    // decending 
    auto m_sorted_c_2 = m.sort_cols(0);
    matrix<int> sorted_c_2 = {
        {10, 6, 20}, 
        {9, 5,  19}, 
        {7, 3, 10}
    };
    ASSERT_TRUE(sorted_c_2 == m_sorted_c_2);

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

    // transpose 
    matrix<int> m3 = {
        {1, 2, 3},
        {4, 5, 6}
    };

    auto m4 = m3.T();
    ASSERT_EQ(m3.row(), m4.col());
    ASSERT_EQ(m3.col(), m4.row());
    
    table<int> T ={
        {1, 4},
        {2, 5},
        {3, 6}
    };

    for(int i = 0; i < m4.row(); i++){
        for(int j = 0; j < m4.col(); j++){
            ASSERT_EQ(m4[i][j], T[i][j]);
        }
    }

}

TEST(operators, arithematic) 
{
    matrix<int> m1 = {
        {1, 2, 3},
        {3, 4, 5},
        {6, 7, 8}
    };
    matrix<int> m2 = {
        {1, 2, 3},
        {3, 4, 5},
        {6, 7, 8}
    };

    auto m3 = m1+m2;
    auto m4 = m1*2;
    auto m5 = 2*m1;
    ASSERT_TRUE(m1 == m2);
    ASSERT_TRUE(m5 == m4);
    ASSERT_TRUE(m3 == m4);

}

TEST(operators, conditional) 
{
    matrix<int> m1 = {
        {1, 2, 3},
        {3, 4, 5},
        {6, 7, 8}
    };
    matrix<int> m2 = {
        {1, 2, 3},
        {3, 4, 5},
        {6, 7, 8}
    };
    matrix<int> m3 = {
        {0, 2, 3},
        {3, 4, 5},
        {6, 7, 8}
    };
    matrix<int> m4 = {
        {0, 1, 2},
        {2, 3, 4},
        {5, 6, 7}
    };

    // equal 
    ASSERT_TRUE(m1 == m2);

    // not equal
    ASSERT_TRUE(m1 != m3);

    // less than 
    ASSERT_FALSE(m3 < m1);
    ASSERT_TRUE(m4 < m1);

    // more than 
    ASSERT_FALSE(m4 > m1);
    ASSERT_TRUE(m1 > m4);

    // less than or equal 
    ASSERT_TRUE(m3 <= m1);

    // more than or equal 
    ASSERT_TRUE(m1 >= m3);
    
}

int main(int argc, char **argv) 
{
   testing::InitGoogleTest(&argc, argv);
   return RUN_ALL_TESTS();
}