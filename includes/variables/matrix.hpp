#pragma once
#include "../misc/constants.hpp"
#include <algorithm>
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
            matrix(int r, int c){
                resize(r, c);
            }

            /**
             * @brief Default construct a new matrix object
             * 
             */
            matrix(): matrix(0, 0){}

            matrix (std::initializer_list<std::initializer_list<S>> a){ 
                _row = a.size();
                _col = a.begin()->size();
                std::vector<S> vect_row;
                for(auto &i: a){
                    vect_row.clear();
                    for(auto &j: i){
                        vect_row.push_back(j);
                    }
                    data.push_back(vect_row);
                }
            }

            /**
             * @brief resizes the matrix
             * 
             * @param r number of rows 
             * @param c number of colums
             */
            void resize(int r, int c){
                // checking 
                if(r < 0 || c < 0){
                    throw std::invalid_argument("Invalid inputs");
                }
                _row = r;
                _col = c;
                data.clear();
                for(int i = 0; i < _row; i++){
                    data.push_back(std::vector<S>(_col));
                }
            }

            /**
             * @brief returns the number of rows
             * 
             * @return int 
             */
            int row(){
                return _row;
            }

            int col(){
                return _col;
            }

            int size(){
                return _col*_row;
            }

            void insert_row(const std::vector<S>& a){
                // if rows are empty
                if(_row == 0 && _col == 0){
                    _col = a.size();
                }
                // checking size
                if(a.size() != _col){
                    throw std::invalid_argument("Size doesnt match");
                }
                resize(_row+1, _col);
                data.push_back(a);
            }

            void insert_col(const std::vector<S>& a){
                // if rows are empty
                if(_row == 0 && _col == 0){
                    _row = a.size();
                }
                // checking size
                if(a.size() != _row){
                    throw std::invalid_argument("Size doesnt match");
                }
                resize(_row, _col+1);
                for(int i = 0; i < _row; i++){
                    data[i].push_back(a[i]);
                }
            }
            
            void insert_row_at(int i, const std::vector<S>& a){
                if(a.size() != _col){
                    throw std::invalid_argument("Size doesnt match");
                }
                data.insert(i, a);
                _row = data.size();

            }

            void insert_col_at(int j, const std::vector<S>& a){
                // checking size
                if(a.size() != _row){
                    throw std::invalid_argument("Size doesnt match");
                }
                for(int i = 0; i < _row; i++){
                    data[i].insert(j, a[i]);
                }
                _col = data[0].size(); // since all colums have same size
            }

            /**
             * @brief mutates data to ints transpose
             */
            void T(){
                // temps
                std::vector<S> temp_col;
                table<S> temp;
                // reversing rows with colums
                for(int i = 0; i < _col; i++){
                    temp_col.clear();
                    for(int j = 0; j < _row; j++){
                        temp_col.push_back(data[j][i]);
                    }
                    temp.push_back(temp_col);
                }
                // applying to data variable
                resize(_col, _row);
                data = temp;
            }

            /**
             * @brief sorts the rows
             * 
             * @param d 
             * d = 1 is accending order -> sort_rows()
             * d = 0 is decending order -> sort_rows(0)
             */
            void sort_rows(int d = 1){
                auto dec = [](int a, int b)-> bool {return a > b;}; // lambda function
                for(int i = 0; i < _row; i++){
                    if(d == 1){ // accending 
                    std::sort(data[i].begin(), data[i].end());
                    }
                    else{ // decending 
                        std::sort(data[i].begin(), data[i].end(), dec);
                    }
                }
            }

            /**
             * @brief sorts the columns 
             * 
             * @param d 
             * d = 1 is accending order -> sort_cols()
             * d = 0 is decending order -> sort_cols(0)
             */
            void sort_cols(int d = 1){
                T(); // transpose
                sort_rows(d); // sort transposed
                T(); // transpose bacl
            }


            void sort_row_at(int i, int d = 1){

            }

            void sort_col_at(int j, int d = 1){

            }

            template<typename LAMBDA> void row_op(int i, LAMBDA f){

            }

            template<typename LAMBDA> void col_op(int j, LAMBDA f){
                
            }

            void turn_to(S n){
                for(int i = 0; i < _row; i++){
                    for(int j = 0; j<_col; j++){
                        data[i][j] = n;
                    }
                }
            }

            S sum(){
                S SUM;
                for(int i = 0; i < _row; i++){
                    for(int j = 0; j < _col; j++){
                        SUM += data[i][j];
                    }
                }
                return SUM;
            }

            // print method
            friend std::ostream& operator << (std::ostream& out, matrix const &other){
                out << "row: " << other._row << "\t" << "col: " << other._col << "\n";
                for(int i = 0; i < other._row; i++){
                    for(int j = 0; j < other._col; j++){
                        out << other.data[i][j] << " ";
                    }
                    out << "\n";
                }
                return out;
            }

            class Row
            {
                private:
                    matrix& _a;
                    int _i;
                public:
                    Row(matrix& a, int i): _a(a), _i(i){}
                    S &operator[](int j){
                        return _a.data[_i][j];
                    }
            };
            Row operator[](int i){
                return Row(*this, i);
            }
            
            matrix operator +(matrix const &other){
                if(other._col != _col || other._row != _row){
                    throw std::invalid_argument("Size mismatch");
                }
                matrix temp(_row, _col);
                temp.data = data;
                for(int i = 0; i < _row; i++){
                    for(int j = 0; j < _col; j++){
                        temp.data[i][j] += other.data[i][j];
                    }
                }
                return temp;
            }

            matrix operator -(matrix const &other){
                if(other._col != _col || other._row != _row){
                    throw std::invalid_argument("Size mismatch");
                }

            }

            matrix operator *(matrix const &other){

            }

            matrix operator /(matrix const &other){

            }

            S det(){

            }

            S inv(){

            }
            
            bool is_square(){
                return _row == _col;
            }

            bool is_identity(){
                if(is_square()){
                    int count_zeros = 0;
                    int count_ones = 0;
                    for(int i = 0; i < _row; i++){
                        for(int j = 0; j < _col; j++){
                            if(i == j && data[i][j] == 1){
                                count_ones++;
                            }
                            else if (i != j && data[i][j] == 0){
                                count_zeros++;
                            }
                        }
                    }
                    if(count_ones+count_zeros == _row*_col && count_ones == _row){
                        return true;
                    }
                }
                return false;
            }

    };
}