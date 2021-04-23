#pragma once
#include "../misc/constants.hpp"
#include <iostream>
#include <vector>
#include <algorithm>

namespace var
{
    /**
     * @brief Class for 2d matrix of objects
     * 
     * @tparam S can be of any type
     */
    template <typename S> class matrix
    {   
        protected:
            /**
             * @brief checks index for columns
             * 
             * @param j 
             */
            void check_col(int j){
                if(j < 0 || j >= _col){
                    throw std::out_of_range("Col index is out of range");
                }
            }

            /**
             * @brief checks index for rows
             * 
             * @param i 
             */
            void check_row(int i){
                if(i < 0 || i >= _row){
                    throw std::out_of_range("Row index is out of range");
                }
            }

            /**
             * @brief returns transpose for data
             * 
             * @return table<S> 
             */
            table<S> TT(){
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
                return temp;
            }

            /**
             * @brief checks size for operators 
             * 
             * @param r 
             * @param c 
             */
            void check_size(int r, int c){
                if(c != _col || r != _row){
                    throw std::invalid_argument("Size mismatch");
                }
            }
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
            matrix(): _row(0), _col(0){}

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
                    throw std::invalid_argument("Invalid values");
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

            /**
             * @brief returns the number of columns
             * 
             * @return int 
             */
            int col(){
                return _col;
            }

            /**
             * @brief returns total number of elements
             * 
             * @return int 
             */
            int size(){
                return _col*_row;
            }

            /**
             * @brief insterts row at the end 
             * 
             * @param a 
             */
            void push_row(const std::vector<S>& a){
                // checking size
                if(a.size() != _col && _row != 0 && _col != 0){
                    throw std::invalid_argument("Size doesnt match");
                }
                else if(_row == 0 && _col == 0){
                    resize(1, a.size());
                    data[0] = a;
                    return;
                }
                data.push_back(a);
                _row = data.size();
            }

            /**
             * @brief insterts column at the end
             * 
             * @param a 
             */
            void push_col(const std::vector<S>& a){
                // checking size
                if(a.size() != _row && _row != 0 && _col != 0){
                    throw std::invalid_argument("Size doesnt match");
                }
                else if(_row == 0 && _col == 0){
                    resize(a.size(), 1);
                    for(int i = 0; i < _row; i++){
                        data[i][0] = a[i];
                    }
                    return;
                }
                for(int i = 0; i < _row; i++){
                    data[i].push_back(a[i]);
                }
                _col = data[0].size(); // since all colums have same size
            }

            /**
             * @brief inserts row at specefic index 
             * 
             * @param i 
             * @param a 
             */
            void insert_row(int i, std::vector<S> a){
                if(a.size() != _col){
                    throw std::invalid_argument("Size doesnt match");
                }
                check_row(i);
                typename table<S>::iterator it = data.begin();
                std::advance(it, i);
                data.insert(it, a);
                _row = data.size();
            }

            /**
             * @brief inserts column at specefic index
             * 
             * @param j 
             * @param a 
             */
            void insert_col(int j, const std::vector<S>& a){
                if(a.size() != _row){
                    throw std::invalid_argument("Size doesnt match");
                }
                check_col(j);
                typename std::vector<S>::iterator it;
                for(int i = 0; i < _row; i++){
                    it = data[i].begin();
                    std::advance(it, j);
                    data[i].insert(it, a[i]);
                }
                _col = data[0].size(); // since all colums have same size
            }

            /**
             * @brief mutates data to into transpose
             * 
             * @return matrix 
             */
            matrix T(){
                matrix temp;
                temp.resize(_col, _row);
                temp.data = TT();
                return temp;
            }

            /**
             * @brief sorts all rows
             * 
             * @param d 
             * d = 1 is accending order -> sort_rows()
             * d = 0 is decending order -> sort_rows(0)
             */
            matrix sort_rows(int d = 1){
                matrix temp = *this;
                auto dec = [](int a, int b)-> bool {return a > b;}; // lambda function
                for(int i = 0; i < _row; i++){
                    if(d == 1){ // accending 
                        std::sort(temp.data[i].begin(), temp.data[i].end());
                    }
                    else{ // decending 
                        std::sort(temp.data[i].begin(), temp.data[i].end(), dec);
                    }
                }
                return temp;
            }

            /**
             * @brief sorts all columns 
             * 
             * @param d 
             * d = 1 is accending order -> sort_cols()
             * d = 0 is decending order -> sort_cols(0)
             */
            matrix sort_cols(int d = 1){
                matrix temp = *this;
                matrix temp2;

                temp = temp.T();
                temp2 = temp.sort_rows(d);
                temp = temp2.T();

                return temp;
            }

            /**
             * @brief sorts rows at specefic index 
             * 
             * @param i 
             * @param d 
             * d = 1 is accending order -> sort_cols()
             * d = 0 is decending order -> sort_cols(0)
             */
            void sort_row(int i, int d = 1){
                check_row(i);
            }

            /**
             * @brief sorts colum at specefic index
             * 
             * @param j 
             * @param d 
             * d = 1 is accending order -> sort_cols()
             * d = 0 is decending order -> sort_cols(0)
             */
            void sort_col(int j, int d = 1){
                check_col(j);
                data = TT(); // transpose
                sort_rows(j, d); // sort transposed
                data = TT(); // transpose back
            }

            /**
             * @brief does operations on specefic rows
             *  operations are specified by lambda function 
             * @tparam LAMBDA 
             * @param i 
             * @param f 
             */
            template<typename LAMBDA> 
            void row_op(int i, LAMBDA f){
                check_row(i);
            }

            /**
             * @brief does operations on specefic colum
             *  operations are specified by lambda function 
             * @tparam LAMBDA 
             * @param j 
             * @param f 
             */
            template<typename LAMBDA> 
            void col_op(int j, LAMBDA f){
                check_col(j);
            }

            /**
             * @brief converts all elements to n
             * 
             * @param n 
             */
            void turn_to(S n){
                for(int i = 0; i < _row; i++){
                    for(int j = 0; j<_col; j++){
                        data[i][j] = n;
                    }
                }
            }

            /**
             * @brief sum of all elements
             * 
             * @return S 
             */
            S sum(){
                S SUM;
                for(int i = 0; i < _row; i++){
                    for(int j = 0; j < _col; j++){
                        SUM += data[i][j];
                    }
                }
                return SUM;
            }

            /**
             * @brief returns the determinant 
             * 
             * @return S 
             */
            S det(){

            }

            /**
             * @brief returns inverse of a matrix
             * 
             * @return matrix 
             */
            matrix inv(){

            }
            
            /**
             * @brief returns RREF of matrix
             * 
             * @return matrix 
             */
            matrix rref(){

            }

            /**
             * @brief checks if matrix is square 
             * 
             * @return true 
             * @return false 
             */
            bool is_square(){
                return _row == _col;
            }

            /**
             * @brief checks if matrix is an identity matrix
             * 
             * @return true 
             * @return false 
             */
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

// ***************************** [] operator ************************** //

            /**
             * @brief col class for another operator[]
             * 
             */
            class Col
            {
                private:
                    matrix& _a;
                    int _i;
                public:
                    /**
                     * @brief Construct a new Col object
                     * 
                     * @param a 
                     * @param i 
                     */
                    Col(matrix& a, int i): _a(a), _i(i){}

                    /**
                     * @brief [] operator for col
                     * 
                     * @param j 
                     * @return S& 
                     */
                    S &operator[](int j){
                        _a.check_row(_i);
                        _a.check_col(j);
                        return _a.data[_i][j];
                    }
            };

            /**
             * @brief [] operator for rows 
             * calls another [] operator for column
             * 
             * @param i 
             * @return Row 
             */
            Col operator[](int i){
                return Col(*this, i);
            }

// ***************************** + operator ************************** //

            /**
             * @brief matrix addition
             * 
             * @param other 
             * @return matrix 
             */
            matrix operator +(matrix const &other){
                check_size(other._row, other._col); 
                matrix temp(_row, _col);
                temp.data = data;
                for(int i = 0; i < _row; i++){
                    for(int j = 0; j < _col; j++){
                        temp.data[i][j] = data[i][j]+other.data[i][j];
                    }
                }
                return temp;
            }

            /**
             * @brief matrix+var
             * 
             * @param n 
             * @return matrix 
             */
            matrix operator +(S n){
                matrix temp = *this;
                for(int i = 0; i < _row; i++){
                    for(int j = 0; j < _col; j++){
                        temp.data[i][j] = data[i][j]+n;
                    }
                }
                return temp;
            }

            /**
             * @brief var+matrix
             * 
             * @param n 
             * @param other 
             * @return matrix 
             */
            friend matrix operator +(S n, matrix &other){
                return other+n;
            }

// ***************************** - operator ************************** //

            /**
             * @brief -matrix
             * 
             * @return matrix 
             */
            matrix operator -(){
                matrix temp = *this;    
                for(int i = 0; i < _row; i++){
                    for(int j = 0; j < _col; j++){
                        temp.data[i][j] = -data[i][j];
                    }
                }
                return temp;
            }

            /**
             * @brief matrix subtraction
             * 
             * @param other 
             * @return matrix 
             */
            matrix operator -(matrix const &other){
                check_size(other._row, other._col); 
                matrix temp = *this;    
                for(int i = 0; i < _row; i++){
                    for(int j = 0; j < _col; j++){
                        temp.data[i][j] = data[i][j]-other.data[i][j];
                    }
                }
                return temp;
            }



            /**
             * @brief matrix-var
             * 
             * @param n 
             * @return matrix 
             */
            matrix operator -(S n){
                matrix temp = *this;
                for(int i = 0; i < _row; i++){
                    for(int j = 0; j < _col; j++){
                        temp.data[i][j] = data[i][j]-n;
                    }
                }
                return temp;
            }

            /**
             * @brief var-matrix
             * 
             * @param n 
             * @param other 
             * @return matrix 
             */
            friend matrix operator -(S n, matrix &other){
                matrix temp = -other;
                return n+temp;
            }

// ***************************** * operator ************************** //

            matrix operator *(matrix const &other){
                // condition 
                if(!(_row == other._col && _col == other._row)){
                    throw std::invalid_argument("Size mismatch");
                }
                matrix temp(_row, other._col);
                for(int i = 0; i < _row; i++){
                    for(int j = 0; j < other._col; j++){
                        
                    }
                }
            }

            /**
             * @brief matrix*var
             * 
             * @param n 
             * @return matrix 
             */
            matrix operator *(S n){
                matrix temp = *this;
                for(int i = 0; i < _row; i++){
                    for(int j = 0; j < _col; j++){
                        temp.data[i][j] = data[i][j]*n;
                    }
                }
                return temp;
            }

            /**
             * @brief var*matrix
             * 
             * @param n 
             * @param other 
             * @return matrix 
             */
            friend matrix operator *(S n, matrix &other){
                return other*n;
            }

// ***************************** / operator ************************** //

            matrix operator /(matrix const &other){

            }

            matrix operator /(S n){
                matrix temp(_row, _col);
                temp.data = data;
                
                for(int i = 0; i < _row; i++){
                    for(int j = 0; j < _col; j++){
                        temp.data[i][j] = data[i][j]/n;
                    }
                }
                return temp;
            }

            friend matrix operator /(S n, matrix &other){
                matrix temp = other;
                for(int i = 0; i < other._row; i++){
                    for(int j = 0; j < other._col; j++){
                        temp.data[i][j] = n/temp.data[i][j];
                    }
                }
                return temp;
            }

// ***************************** ^ operator ************************** //

// ***************************** % operator ************************** //

// ***************************** ~ operator ************************** //


// *********************** conditional operators ******************** //

            /**
             * @brief equals method for all elements
             * 
             * @param other 
             * @return true 
             * @return false 
             */
            bool operator==(matrix other){
                check_size(other._row, other._col); 

                for(int i = 0; i < _row; i++){
                    for(int j = 0; j < _col; j++){
                        if(other.data[i][j] != data[i][j]){
                            return false;
                        }
                    }
                }
                return true;
            }

            /**
             * @brief less than operator
             * 
             * @param other 
             * @return true 
             * @return false 
             */
            bool operator<(matrix other){
                if(other._col != _col || other._row != _row){
                    return false;
                }
                for(int i = 0; i < _row; i++){
                    for(int j = 0; j < _col; j++){
                        if(data[i][j] >= other.data[i][j]){
                            return false;
                        }
                    }
                }
                return true;
            }
            
            /**
             * @brief more than
             * 
             * @param other 
             * @return true 
             * @return false 
             */
            bool operator>(matrix other){
                return !(*this < other);
            }

            /**
             * @brief less than or equal
             * 
             * @param other 
             * @return true 
             * @return false 
             */
            bool operator<=(matrix other){
                check_size(other._row, other._col); 
                for(int i = 0; i < _row; i++){
                    for(int j = 0; j < _col; j++){
                        if(data[i][j] > other.data[i][j]){
                            return false;
                        }
                    }
                }
                return true;
            }

            /**
             * @brief more than or equal 
             * 
             * @param other 
             * @return true 
             * @return false 
             */
            bool operator>=(matrix other){
                return !(*this <= other);
            }        

            /**
             * @brief not equal method
             * 
             * @param other 
             * @return true 
             * @return false 
             */
            bool operator!=(matrix other){
                return !(*this == other);
            }

// ************************* stream operator ************************ //

            /**
             * @brief print method for the class 
             * var::matrix<int> m; cout << m;
             * @tparam S 
             * @param out 
             * @param other 
             * @return std::ostream& 
             */
            friend std::ostream& operator << (std::ostream& out, matrix const &other){
                for(int i = 0; i < other._row; i++){
                    for(int j = 0; j < other._col; j++){
                        out << other.data[i][j] << ",";
                    }
                    out << "\n";
                }
                return out;
            }
    
    
    };
    
};