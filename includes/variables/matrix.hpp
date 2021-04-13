#pragma once
#include "../misc/constants.hpp"
#include <iostream>
#include <vector>

namespace var
{
    /**
     * @brief Class for 2d matrix of objects with matrix properties 
     * 
     * @tparam S can be of any type
     */
    template <typename S> class matrix
    {
        private:
            table<S> data;
            int _row;
            int _col;

        public:

            /**
             * @brief Construct a new matrix object
             * 
             * @param r number of rows
             * @param c number of colums
             */
            matrix(int r, int c);

            /**
             * @brief Default construct a new matrix object
             * 
             */
            matrix();

            matrix (std::initializer_list<std::initializer_list<S>> a);

            /**
             * @brief resizes the matrix
             * 
             * @param r number of rows 
             * @param c number of colums
             */
            void resize(int r, int c);

            /**
             * @brief returns the number of rows
             * 
             * @return int 
             */
            int row();
            /**
             * @brief returns the number of columns
             * 
             * @return int 
             */
            int col();

            int size();

            void insert_row(const std::vector<S>& a);

            void insert_col(const std::vector<S>& a);
            
            void insert_row(int i, const std::vector<S>& a);

            void insert_col(int j, const std::vector<S>& a);

            /**
             * @brief mutates data to ints transpose
             */
            void T();

            /**
             * @brief sorts the rows
             * 
             * @param d 
             * d = 1 is accending order -> sort_rows()
             * d = 0 is decending order -> sort_rows(0)
             */
            void sort_rows(int d = 1);

            /**
             * @brief sorts the columns 
             * 
             * @param d 
             * d = 1 is accending order -> sort_cols()
             * d = 0 is decending order -> sort_cols(0)
             */
            void sort_cols(int d = 1);


            void sort_row_at(int i, int d = 1);

            void sort_col_at(int j, int d = 1);

            template<typename LAMBDA> 
            void row_op(int i, LAMBDA f);

            template<typename LAMBDA> 
            void col_op(int j, LAMBDA f);

            void turn_to(S n);

            S sum();



            class Row
            {
                private:
                    matrix& _a;
                    int _i;
                public:
                    Row(matrix& a, int i);
                    S &operator[](int j);
            };

            Row operator[](int i);
            
            matrix operator +(matrix const &other);

            matrix operator -(matrix const &other);

            matrix operator *(matrix const &other);

            matrix operator /(matrix const &other);

            S det();

            S inv();
            
            bool is_square();

            bool is_identity();

    };

    /**
     * @brief print method for the class 
     * var::matrix<int> m; cout << m;
     * @tparam S 
     * @param out 
     * @param other 
     * @return std::ostream& 
     */
    template<typename S>
    std::ostream& operator << (std::ostream& out, matrix<S> &other);
};

#include "../../src/variables/matrix.cpp"