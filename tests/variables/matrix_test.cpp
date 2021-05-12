#include "../../lib/googletest/googletest/include/gtest/gtest.h"
#include "../../includes/mcpp.hpp"
#include <fstream>
using var::matrix;
template<typename T> 
using table = std::vector<std::vector<T>>;
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
    m2.insert_row(1, {1, 2, 3});
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
    m.sort_rows();
    matrix<int> sorted = {
        {3, 9, 10},
        {6, 7, 20},
        {5, 10, 19}
    };
    ASSERT_TRUE(m == sorted);

    // desending 
    m = {
        {9, 3, 10},
        {7, 6, 20},
        {10, 5, 19}
    };
    m.sort_rows(0);
    matrix<int> sorted_2 = {
        {10, 9, 3},
        {20, 7, 6},
        {19, 10, 5}
    };
    ASSERT_TRUE(m == sorted_2);

    // sort cols
    // accending 
    m = {
        {9, 3, 10},
        {7, 6, 20},
        {10, 5, 19}
    };
    m.sort_cols();
    matrix<int> sorted_c = {
        {7, 3, 10},
        {9, 5, 19},
        {10, 6, 20}
    };
    ASSERT_TRUE(m == sorted_c);


    // decending 
    m = {
        {9, 3, 10},
        {7, 6, 20},
        {10, 5, 19}
    };
    m.sort_cols(0);
    matrix<int> sorted_c_2 = {
        {10, 6, 20}, 
        {9, 5,  19}, 
        {7, 3, 10}
    };
    ASSERT_TRUE(m == sorted_c_2 );

}

TEST(functionality, get_row_col)
{
    matrix<int> m = {
        {9, 3, 10},
        {7, 6, 20},
        {10, 5, 19}
    };  
    auto row = m.get_row(1);
    ASSERT_EQ(row.size(), m.col());
    ASSERT_EQ(row[0], m[1][0]);
    ASSERT_EQ(row[1], m[1][1]);
    ASSERT_EQ(row[2], m[1][2]);

    auto col = m.get_col(1);
    ASSERT_EQ(col.size(), m.row());
    ASSERT_EQ(col[0], m[0][1]);
    ASSERT_EQ(col[1], m[1][1]);
    ASSERT_EQ(col[2], m[2][1]);

}

TEST(functionality, row_col_op_2)
{
    matrix<int> m = {
        {9, 3, 10},
        {7, 6, 20},
        {10, 5, 19}
    };  

    auto fun = [](int A){
        return A*2+3;
    };
    m.row_op(1, fun);
    ASSERT_EQ(m[1][0], 7*2+3);
    ASSERT_EQ(m[1][1], 6*2+3);
    ASSERT_EQ(m[1][2], 20*2+3);

    m = {
        {9, 3, 10},
        {7, 6, 20},
        {10, 5, 19}
    };
    m.col_op(1, fun);
    ASSERT_EQ(m[0][1], 3*2+3);
    ASSERT_EQ(m[1][1], 6*2+3);
    ASSERT_EQ(m[2][1], 5*2+3);

    m = {
        {9, 3, 10},
        {7, 6, 20},
        {10, 5, 19}
    };
    auto f = [](int A){
        return (0*A+1);
    };
    m.mat_op(f);
    ASSERT_EQ(m.sum(), m.size());

}

TEST(functionality, remove_row_col)
{
    matrix<int> m1 = {
        {1, 0},
        {0, 1}
    };
    m1.pop_row();
    ASSERT_EQ(m1.row(), 1);
    ASSERT_EQ(m1[0][0], 1);
    ASSERT_EQ(m1[0][1], 0);

    matrix<int> m2 = {
        {1, 2, 3},
        {4, 5, 6}
    };
    m2.pop_col();
    ASSERT_EQ(m2.col(), 2);
    ASSERT_EQ(m2[0][0], 1);
    ASSERT_EQ(m2[0][1], 2);
    ASSERT_EQ(m2[1][0], 4);
    ASSERT_EQ(m2[1][1], 5);
}

TEST(functionality, remove_row_col_at)
{
    matrix<int> m1 = {
        {1, 9},
        {2, 10},
        {3, 4}
    };
    m1.erase_row(1);
    ASSERT_EQ(m1.row(), 2);
    ASSERT_EQ(m1[0][0], 1);
    ASSERT_EQ(m1[0][1], 9);
    ASSERT_EQ(m1[1][0], 3);
    ASSERT_EQ(m1[1][1], 4);


    matrix<int> m2 = {
        {1, 9, 11},
        {2, 10, 12},
        {3, 4, 16}
    };
    m2.erase_col(1);
    ASSERT_EQ(m2.col(), 2);
    ASSERT_EQ(m2[0][0], 1);
    ASSERT_EQ(m2[1][0], 2);
    ASSERT_EQ(m2[2][0], 3);
    ASSERT_EQ(m2[0][1], 11);
    ASSERT_EQ(m2[1][1], 12);
    ASSERT_EQ(m2[2][1], 16);

}

TEST(functionality, join_row_col)
{
    matrix<int> m = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9},
        {2, 3, 4}
    };

    auto eyed = num::mat::eye<int>(m.col());

    m.join_row(eyed);

    matrix<int> Eyed = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9},
        {2, 3, 4},
        {1, 0, 0},
        {0, 1, 0},
        {0, 0, 1}
    };

    ASSERT_TRUE(m == Eyed);
    
    matrix<int> m2 = {
        {1, 2, 3, 0, 0},
        {4, 5, 6, 0, 0},
        {7, 8, 9, 0, 0},
        {2, 3, 4, 0, 0},
        {1, 0, 0, 0, 0},
        {0, 1, 0, 0, 0},
        {0, 0, 1, 0, 0}
    };

    matrix<int> eyed2(m2.row(), 2);

    m.join_col(eyed2);

    ASSERT_TRUE(m == m2);

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
    // det 
    matrix<int> m5 = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {8, 10, 11, 12},
        {13, 14, 15, 20}
    };
    ASSERT_EQ(m5.det(), 16);

    // cofactor 
    matrix<double> m6 = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 12}
    };
    matrix<double> m7 = {
        {12, -6, -3},
        {0, -9, 6},
        {-3, 6, -3}
    };
    ASSERT_TRUE(m7 == m6.cofactor());

    // adjugate 
    matrix<double> m8 = {
        {12, 0, -3},
        {-6, -9, 6},
        {-3, 6, -3}
    };
    ASSERT_TRUE(m6.adj() == m8);
    // inverse 
    matrix<double> m9 = {
        {-4.0/3.0, 0, 1.0/3.0},
        {2.0/3, 1.0, -2.0/3.0},
        {1.0/3.0, -2.0/3.0, 1.0/3.0}
    };
    ASSERT_TRUE(m9 == m6.inv());

    // trace 
    ASSERT_FLOAT_EQ(m6.tr(), 1.0+5.0+12.0);

}

TEST(operators, slicing)
{
    matrix<int> m = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };

    auto sliced = m(1, 3);
    matrix<int> Sliced = {
        {4, 5, 6},
        {7, 8, 9}
    };

    ASSERT_TRUE(sliced == Sliced);

    auto sliced2 = m(1, 0, 2);
    std::vector<int> Sliced2 = {4, 5};
    ASSERT_TRUE(sliced2 == Sliced2);

    auto sliced3 = m(0, 2, 0, 2);
    matrix<int> Sliced3 = {
        {1, 2},
        {4, 5}
    };
    ASSERT_TRUE(Sliced3 == sliced3);
}

TEST(functionality, rref) 
{
    matrix<int> m = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };

    matrix<int> RREF = {
        {1, 0, -1},
        {0, 1, 2},
        {0, 0, 0}
    };

    auto rref = m.rref();
    ASSERT_TRUE(rref == RREF);

    matrix<int> m2 = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9},
        {10, 11, 12}
    };

    matrix<int> RREF2 = {
        {1, 0, -1},
        {0, 1, 2},
        {0, 0, 0},
        {0, 0, 0}
    };

    auto rref2 = m2.rref();
    ASSERT_TRUE(rref2 == RREF2);
}

TEST(functionality, ref)
{
    matrix<double> m = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9},
        {10, 11, 12}
    };

    matrix<double> ref = {
        {1, 2, 3},
        {0, -3, -6},
        {0, 0, 0},
        {0, 0, 0}
    };
    ASSERT_TRUE(ref == m.ref());
} 

TEST(functionality, lu)
{
    matrix<double> m = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9},
        {10, 11, 12}
    };

    matrix<double> u = {
        {1, 2, 3},
        {0, -3, -6},
        {0, 0, 0},
        {0, 0, 0}
    };

    matrix<double> l = {
        {1, 0, 0, 0},
        {4, 1, 0, 0},
        {7, 2, 1, 0},
        {10, 3, 0, 1}
    };

    auto LU = m.lu_decomposition();

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

    // addition 
    matrix<int> m3 = {
        {2, 4, 6},
        {6, 8, 10},
        {12, 14, 16}
    };
    auto m4 = m1+m2;
    ASSERT_TRUE(m3 == (m1+m2));

    matrix<int> m5 = {
        {1+2, 2+2, 3+2},
        {3+2, 4+2, 5+2},
        {6+2, 7+2, 8+2}
    };

    auto m6 = 2+m1;
    auto m7 = m1+2;

    ASSERT_TRUE(m6 == m7);
    ASSERT_TRUE(m6 == m5);

    // subtraction 
    matrix<int> m8 = {
        {-1, -2, -3},
        {-3, -4, -5},
        {-6, -7, -8}
    };
    ASSERT_TRUE(m8 == -m1);
    ASSERT_TRUE((m4-m1) == m1);
    ASSERT_TRUE(m1 == (m6-2));
    ASSERT_TRUE(m8 == (2-m6));
}

TEST(operators, cin_cout)
{
   std::ifstream infile("mat.txt");
   matrix<int> a;
   infile >> a;
   testing::internal::CaptureStdout();
   std::cout << a;
   std::string output = testing::internal::GetCapturedStdout();
   EXPECT_TRUE(output == "1,2,3,4,5\n6,7,8,9,10");

}


TEST(operators, mult_div)
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
        {1, 2, 3},
        {4, 5, 6}
    };
    matrix<int> m4 = {
        {7, 8},
        {9, 10},
        {11, 12}
    };
    matrix<int> m5 = {
        {58, 64},
        {139, 154}
    };
    // multiply 
    ASSERT_TRUE(2*m2 == m2*2);
    ASSERT_TRUE(2*m2 == m1+m2);
    ASSERT_TRUE(m3*m4 == m5);

    // multiply 
    ASSERT_TRUE(2*m2 == m2*2);
    ASSERT_TRUE(2*m2 == m1+m2);

    // divide 
    ASSERT_TRUE(m2/2 != 2/m2);

    // modulus 
    auto m6 = m5%2;
    int count = 0;
    for(const auto &i: m6){
        for(const auto &j: i){
            if(j == 0){
                count++;
            }
        }
    }
    ASSERT_EQ(count, 3);

    // mathmul
    auto m7 = m1.mathmul(m2);
    ASSERT_EQ(m7[0][0], 1*1);
    ASSERT_EQ(m7[1][1], 4*4);

    // mathdiv 
    auto m8 = m1.mathdiv(m2);
    ASSERT_EQ(m8[0][0], 1);
    ASSERT_EQ(m8[1][1], 1);


} 

TEST(functionality, row_col_swap)
{
    matrix<int> m = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };

    std::vector<int> row0 = m.get_row(0);
    std::vector<int> row1 = m.get_row(1);

    m.row_swap(0, 1);

    ASSERT_TRUE(m.get_row(0) == row1);
    ASSERT_TRUE(m.get_row(1) == row0);

    std::vector<int> col0 = m.get_col(0);
    std::vector<int> col1 = m.get_col(1);

    m.col_swap(0, 1);

    ASSERT_TRUE(col0 == m.get_col(1));
    ASSERT_TRUE(col1 == m.get_col(0));

}

TEST(functionality, row_col_replace)
{
    matrix<int> m = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };

    std::vector<int> row0 = {5, 5, 5};
    
    m.replace_row(0, row0);
    ASSERT_TRUE(row0 == m.get_row(0));

    std::vector<int> col0 = {-1, -2, -5};
    m.replace_col(0, col0);
    ASSERT_TRUE(col0 == m.get_col(0));
    

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