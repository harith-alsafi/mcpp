/**
 * @file matrix.hpp
 * @author Harith Al-Safi (harith.alsafi@gmail.com)
 * @brief Implementation and declaration of matrix class
 * @version 1.0
 * @date 17/07/2022
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#pragma once
#include "../mcpp.hpp"
#include <algorithm>
#include <numeric>
#include <limits>
#include <cmath>
namespace var
{
    /**
     * @brief Class for 2d matrix of objects
     * 
     * @tparam D: can be of any type
     */
    template <typename D> class matrix
    {   
        protected:
            /**
             * @brief Col class for another operator[]
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
                     * @return D& 
                     */
                    D &operator[](int j){
                        return _a.data[_i][j];
                    }
            };
            
            /**
             * @brief 2D vector definition 
             * 
             * @tparam T 
             */
            template<typename T> 
            using table = std::vector<std::vector<T>>;

            /**
             * @brief checks index for columns
             * 
             * @param j column index 
             */
            void check_col(int j){
                if(j < 0 || j >= _col){
                    throw std::out_of_range("var::matrix::check_col -> Col index is out of range");
                }
            }

            /**
             * @brief checks index for rows
             * 
             * @param i row index
             */
            void check_row(int i){
                if(i < 0 || i >= _row){
                    throw std::out_of_range("var::matrix::check_row -> Row index is out of range");
                }
            }

            /**
             * @brief Returns transpose for data
             * 
             * @return ``table<D>`` 
             */
            table<D> TT(){
                // temps
                std::vector<D> temp_col;
                table<D> temp;
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
             * @brief Checks other matrix size for operators 
             * 
             * @param r row  
             * @param c column
             */
            void check_size(int r, int c){
                if(c != _col || r != _row){
                    throw std::invalid_argument("var::matrix::check_size -> Size mismatch");
                }
            }

            /**
             * @brief Protected minor (used in ``DET``)
             * 
             * @param i row index
             * @param j column index
             * @param other ``matrix``
             * @return ``matrix`` 
             */
            matrix MM(int i, int j, matrix &other) {
                matrix b(other.row()-1, other.col()-1);
                int r = 0;
                int c = 0;
                for(int ii = 0; ii < other.row(); ii++){
                    for(int jj = 0; jj < other.col(); jj++){
                        if(ii != i && jj != j){
                            b[r][c] = other[ii][jj];
                            c++;
                        }
                    }
                    c = 0;
                    if(ii != i){
                        r++;
                    }
                }
                return b;
            }

            /**
             * @brief Recursive determinant 
             * 
             * @param a ``matrix`` type
             * @return ``D``  
             */
            D DET(matrix a){
                // 2x2 determinant
                if(a.col() == 2){
                    return (a[0][0]*a[1][1])-(a[1][0]*a[0][1]);
                }
                // n by n
                D sum = D();
                for(int j = 0; j < a.col(); j++){              
                    sum += a[0][j]*std::pow((-1), 0+j)*DET(MM(0, j, a));                  
                }
                return sum;
            }

            /**
             * @brief throws exception if matrix is not a square
             * 
             */
            void square(){
                if(!is_square()){
                    throw std::invalid_argument("var::matrix::square -> Matrix is not a square");
                }
            }

        private:
            table<D> data;
            int _row;
            int _col;
        public:

            /**
             * @brief Struct for PLU decomposition
             * 
             * **Usage**:
             * ```cpp
             * typename var::matrix<D>::LU a;
             * ```
             * 
             */
            struct LU
            {
                /**
                 * @brief Lower triangular
                 * 
                 */
                matrix L;

                /**
                 * @brief Upper triangular
                 * 
                 */
                matrix U;

                /**
                 * @brief Permutation matrix
                 * 
                 */
                matrix P;
            };

            /**
             * @brief Construct a new matrix object
             * 
             * **Usage**:
             * ```cpp
             * var::matrix<int> m(2, 3); // 2 rows, 3 colums
             * ```
             * @param r number of rows
             * @param c number of colums
             */
            matrix(int r, int c){
                resize(r, c);
            }

            /**
             * @brief Default construct a new matrix object
             * 
             * **Usage**:
             * ```cpp
             * var::matrix<int> m;
             * ```
             */
            matrix(): _row(0), _col(0){}

            /**
             * @brief Construct a new matrix object
             * 
             * **Usage**:
             * ```cpp
             *  var::matrix<int> m = {
                    {1, 2, 3},
                    {4, 5, 6},
                    {7, 8, 9}
                };
             * ```
             * 
             * ## Getters
             * 
             * @param a initializer list 
             */
            matrix (std::initializer_list<std::initializer_list<D>> a){ 
                _row = a.size();
                _col = a.begin()->size();
                std::vector<D> vect_row;
                for(auto &i: a){
                    vect_row.clear();
                    for(auto &j: i){
                        vect_row.push_back(j);
                    }
                    data.push_back(vect_row);
                }
            }

            /**
             * @brief Returns the number of rows
             * 
             * **Usage**:
             * ```cpp
             * var::matrix<int> m(2, 3); 
             * int r = m.row();
             * ```
             * 
             * @return ``int`` 
             */
            int row(){
                return _row;
            }

            /**
             * @brief Returns the number of columns
             * 
             * @return ``int`` 
             */
            int col(){
                return _col;
            }
            
            /**
             * @brief Returns total number of elements
             * 
             * @return ``int`` 
             */
            int size(){
                return _col*_row;
            }

            /**
             * @brief Mainly invoked for the ranged for loop
             * 
             * **Usage**: 
             * ```cpp
             * for(auto i: m){
             *    for(j: i){
             *      // do smth 
             *    }
             * }
             * ```
             * 
             * @return ``std::vector<D>``
             */
            auto begin(){
                return data.begin();
            }

            /**
             * @brief Returns end of data
             * 
             * @return ``std::vector<D>``
             */
            auto end(){
                return data.end();
            }

            /**
             * @brief Returns const begin
             * 
             * @return ``std::vector<D>``
             */
            auto begin() const{
                return data.begin();
            }

            /**
             * @brief Returns const end
             * 
             * @return ``std::vector<D>``
             */
            auto end() const{
                return data.end();
            }

            /**
             * @brief Get the element object
             * 
             * * Unlike the ``[]`` operator this does index checking
             * 
             * @param i row index
             * @param j column index
             * @return ``D`` 
             */
            D get_element(int i, int j){
                check_row(i);
                check_col(j);
                return data[i][j];
            }

            /**
             * @brief Returns the row at an index
             * 
             * **Usage**:  
             * ```cpp
             * var::matrix<int> m(3, 3);
             * auto col = m.get_col(1);
             * ```
             * 
             * @param i row index  
             * @return ``std::vector<D>`` 
             */
            std::vector<D> get_row(int i){
                check_row(i);
                return data[i];
            }

            /**
             * @brief Returns the column at an index
             * 
             * @param j column index 
             * @return ``std::vector<D>``
             * 
             * ## Mutable methods   
             * 
             */
            std::vector<D> get_col(int j){
                check_col(j);
                std::vector<D> temp;
                for(int i = 0; i < _row; i++){
                    temp.push_back(data[i][j]);
                }
                return temp;
            }

            /**
             * @brief Resizes the matrix
             * 
             * **Usage**:
             * ```cpp
             * m.resize(3, 3);
             * ``` 
             * 
             * !!! warning "Warning"  
             * <pre>
             *     This resets all elements in the matrix
             * </pre>
             * 
             * @param r number of rows 
             * @param c number of colums
             */
            void resize(int r, int c){
                // checking 
                if(r < 0 || c < 0){
                    throw std::invalid_argument("var::matrix::resize -> Invalid values");
                }
                _row = r;
                _col = c;
                data.clear();
                for(int i = 0; i < _row; i++){
                    data.push_back(std::vector<D>(_col));
                }
            }

            /**
             * @brief Inserts row at the end or the matrix
             * 
             * **Usage**:  
             * ```cpp
             * m.push_row({1, 2, 3});
             * ```
             * 
             * @param a row vector
             */
            void push_row(std::vector<D> a){
                // checking size
                if(a.size() != _col && _row != 0 && _col != 0){
                    throw std::invalid_argument("var::matrix::push_row -> Size doesnt match");
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
             * @brief Inserts column at the end of the matrix
             * 
             * @param a column vector
             */
            void push_col(std::vector<D> a){
                // checking size
                if(a.size() != _row && _row != 0 && _col != 0){
                    throw std::invalid_argument("var::matrix::push_col -> Size doesnt match");
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
             * @brief Inserts row at specefic index 
             * 
             * **Usage**:  
             * ```cpp
             * m.insert_row(1, {1, 2, 3});
             * ```
             * 
             * @param i row index
             * @param a row vector
             */
            void insert_row(int i, std::vector<D> a){
                if(a.size() != _col){
                    throw std::invalid_argument("var::matrix::insert_row -> Size doesnt match");
                }
                check_row(i);
                typename table<D>::iterator it = data.begin();
                std::advance(it, i);
                data.insert(it, a);
                _row = data.size();
            }

            /**
             * @brief Inserts column at specefic index
             * 
             * @param j column index 
             * @param a column vector
             */
            void insert_col(int j, std::vector<D> a){
                if(a.size() != _row){
                    throw std::invalid_argument("var::matrix::insert_col -> Size doesnt match");
                }
                check_col(j);
                typename std::vector<D>::iterator it;
                for(int i = 0; i < _row; i++){
                    it = data[i].begin();
                    std::advance(it, j);
                    data[i].insert(it, a[i]);
                }
                _col = data[0].size(); // since all colums have same size
            }

            /**
             * @brief Removes last row
             * 
             * **Usage**:
             * ```cpp
             * m.pop_row(1);
             * ``` 
             * 
             */
            void pop_row(){
                if(_row == 0){
                    throw std::invalid_argument("var::matrix::pop_row -> No rows to remove");
                }
                data.pop_back();
                _row = data.size();
            }

            /**
             * @brief removes last column
             * 
             */
            void pop_col(){
                if(_col == 0){
                    throw std::invalid_argument("var::matrix::pop_col -> No colums to remove");
                }
                for(int i = 0; i < _row; i++){
                    data[i].pop_back();
                }
                _col = data[0].size();
            }
            
            /**
             * @brief Erase row at index
             * 
             * **Usage**:
             * ```cpp
             * m.erase_row(1);
             * ``` 
             * 
             * @param i row index
             */
            void erase_row(int i){
                check_row(i);
                data.erase(data.begin()+i);
                _row = data.size();
            }

            /**
             * @brief Erases column at index
             * 
             * @param j column index
             * 
             */
            void erase_col(int j){
                check_col(j);
                for(int i = 0; i < _row; i++){
                    data[i].erase(data[i].begin()+j);
                }
                _col = data[0].size();
            }

            /**
             * @brief Swaps row of matrix 
             * 
             * **Usage**:
             * ```cpp
             * m.row_swap(0, 1); // swaps row 0 with row 1
             * ```
             * 
             * @param i1 first row 
             * @param i2 second row 
             */
            void row_swap(int i1, int i2){
                check_row(i1);
                check_row(i2);
                auto temp = data[i1];
                data[i1] = data[i2];
                data[i2] = temp;
            }

            /**
             * @brief Replaces certain row 
             * 
             * @param i row index
             * @param a ``std::vector`` 
             */
            void replace_row(int i, std::vector<D> a){
                if(a.size() != _row){
                    throw std::invalid_argument("var::matrix::replace_row -> Size doesnt match");
                }
                check_row(i);
                data[i] = a;
            }

            /**
             * @brief Replaces certain colum
             * 
             * @param j column index
             * @param a ``std::vector``
             */
            void replace_col(int j, std::vector<D> a){
                if(a.size() != _col){
                    throw std::invalid_argument("var::matrix::replace_col -> Size doesnt match");
                }
                check_col(j);
                for(int i = 0; i < _row; i++){
                    data[i][j] = a[i];
                }
            }

            /**
             * @brief Colum swap 
             * 
             * @param j1 first column 
             * @param j2 second column 
             */
            void col_swap(int j1, int j2){
                check_col(j1);
                check_col(j2);
                D temp = D();
                for(int i = 0; i < _row; i++){
                    temp = data[i][j1];
                    data[i][j1] = data[i][j2];
                    data[i][j2] = temp;
                }
            }

            /**
             * @brief Sorts all rows
             * 
             * **Usage**:
             * ```cpp
             * m.sort_rows();
             * ``` 
             * 
             * @param d details are shown below
             * @param ``d = 1`` is accending order $\rightarrow$ ``sort_rows();`` <br>  
             * @param ``d = 0`` is decending order $\rightarrow$ ``sort_rows(0);``
             */
            void sort_rows(int d = 1){
                for(int i = 0; i < _row; i++){
                    sort_row(i, d);
                }
            }

            /**
             * @brief Sorts all columns 
             * 
             * @param d details are shown below
             * @param ``d = 1`` is accending order $\rightarrow$ ``sort_rows();`` <br>  
             * @param ``d = 0`` is decending order $\rightarrow$ ``sort_rows(0);``
             */
            void sort_cols(int d = 1){
                for(int j = 0; j < _col; j++){
                    sort_col(j, d);
                }
            }

            /**
             * @brief Sorts rows at specefic index 
             * 
             * **Usage**:
             * ```cpp
             * m.sort_row(0, 0);
             * ``` 
             * 
             * @param i row index
             * @param d details are shown below
             * @param ``d = 1`` is accending order $\rightarrow$ ``sort_rows();`` <br>  
             * @param ``d = 0`` is decending order $\rightarrow$ ``sort_rows(0);``
             */
            void sort_row(int i, int d = 1){
                check_row(i);
                auto dec = [](int a, int b)-> bool {return a > b;}; 
                if(d == 1){ // accending 
                    std::sort(data[i].begin(), data[i].end());
                }
                else{ // decending 
                    std::sort(data[i].begin(), data[i].end(), dec);
                }
            }

            /**
             * @brief Sorts column at specefic index
             * 
             * @param j column index  
             * @param d details are shown below
             * @param ``d = 1`` is accending order $\rightarrow$ ``sort_rows();`` <br>  
             * @param ``d = 0`` is decending order $\rightarrow$ ``sort_rows(0);``
             */
            void sort_col(int j, int d = 1){
                check_col(j);
                data = TT(); // transpose
                sort_row(j, d); // sort transposed
                data = TT(); // transpose back
            }

            /**
             * @brief Does operations on specefic rows
             * 
             * **Usage**:
             * ```cpp
             * auto f = [](int A){return A*2+3;};
             * m.row_op(1, f);
             * ```
             * 
             * @tparam LAMBDA: ``std::function`` 
             * @param i column index
             * @param f function to change column elements
             */
            template<typename LAMBDA> 
            void row_op(int i, LAMBDA f){
                check_row(i);
                for(int j = 0; j < _col; j++){
                    data[i][j] = f(data[i][j]);
                }
            }

            /**
             * @brief Does operations on a specefic column
             * 
             * @tparam LAMBDA: ``std::function`` 
             * @param j column index 
             * @param f function to change column elements
             *  
             * !!! warning "Exception"    
             * <pre>
             *     All row and column operations (inserting, removing .. etc) throw an <code>std::invalid_argument</code> if&#58;  
             *         1. There is a size mismatch  
             *         2. Invalid index 
             * </pre>
             *              
             */
            template<typename LAMBDA> 
            void col_op(int j, LAMBDA f){
                check_col(j);
                for(int i = 0; i < _row; i++){
                    data[i][j] = f(data[i][j]);
                }
            }
            
            /**
             * @brief Function operation on all of the matrix
             * 
             * **Usage**:
             * ```cpp
             * auto f = [](int A){return A*2+3;};
             * m.mat_op(f);
             * ```
             * 
             * @tparam LAMBDA: ``std::function`` 
             * @param f Function
             */
            template<typename LAMBDA>
            void mat_op(LAMBDA f){
                for(int i = 0; i < _row; i++){
                    for(int j = 0; j < _col; j++){
                        data[i][j] = f(data[i][j]);
                    }
                }
            }

            /**
             * @brief Combines the rows of another matrix
             * 
             * **Usage**:
             * ```cpp
             * // m2 must have same number of columns as m1
             * m1.join_row(m2);
             * ```
             * 
             * @param other ``matrix``
             */
            void join_row(matrix other){
                if(other.col() != _col){
                    throw std::invalid_argument("var::matrix::join_row -> Size mismatch");
                }
                for(int i = 0; i < other.row(); i++){
                    push_row(other.get_row(i));
                }
            }

            /**
             * @brief Combines the columns of another matrix
             * 
             * * ``other`` must have same number of rows
             * 
             * @param other ``matrix``
             */
            void join_col(matrix other){
                if(other.row() != _row){
                    throw std::invalid_argument("var::matrix::join_col -> Size mismatch");
                }
                for(int j = 0; j < other.col(); j++){
                    push_col(other.get_col(j));
                }
            }

            /**
             * @brief Converts all elements to n
             * 
             * **Usage**:
             * ```cpp
             * m.turn_to(1); 
             * ```
             * 
             * @param n the specifeid variable
             *  
             * ## Immutable methods  
             * 
             */
            void turn_to(D n){
                for(int i = 0; i < _row; i++){
                    for(int j = 0; j<_col; j++){
                        data[i][j] = n;
                    }
                }
            }

            /**
             * @brief Sum of all elements
             * 
             * **Usage**:
             * ```cpp
             * auto sum = m.sum();
             * ``` 
             * 
             * @return ``D``
             */
            D sum(){
                D SUM = D();
                for(int i = 0; i < _row; i++){
                    for(int j = 0; j < _col; j++){
                        SUM += data[i][j];
                    }
                }
                return SUM;
            }

            /**
             * @brief Trace of a matrix
             * 
             * @return ``D``
             */
            D tr(){
                square();
                D sum = D();
                for(int i = 0; i < _row; i++){
                    sum+= data[i][i];
                }
                return sum;
            }

            /**
             * @brief Returns the determinant 
             * 
             * @return ``D`` 
             */
            D det(){
                square();
                return DET(*this);
            }

            /**
             * @brief Transpose of a matrix 
             * 
             * **Usage**:
             * ```cpp
             * var::matrix<int> m(3, 3);
             * auto T = m.T();
             * ``` 
             * 
             * @return ``matrix`` 
             */
            matrix T(){
                matrix temp;
                temp.resize(_col, _row);
                temp.data = TT();
                return temp;
            }

            /**
             * @brief Returns cofactor matrix
             * 
             * @return matrix 
             */
            matrix cofactor(){
                square();
                matrix temp(_row, _col);
                for(int i = 0; i < _row; i++){
                    for(int j = 0; j < _col; j++){
                        auto m = MM(i, j, *this);
                        temp[i][j] = pow((-1), (i+j))*m.det();
                    }
                }
                return temp;
            }

            /**
             * @brief Minor of a matrix
             * 
             * @param i row index
             * @param j column index
             * @return ``matrix`` 
             */
            matrix M(int i, int j) {
                return MM(i, j, *this);
            }

            /**
             * @brief Adjugate of a matrix
             * 
             * @return ``matrix`` 
             */
            matrix adj(){
                square();
                matrix temp = cofactor();
                return temp.T();
            }

            /**
             * @brief Returns inverse of a matrix
             * 
             * @return ``matrix`` 
             */
            matrix inv(){
                square();
                D detm = det();
                if(detm == 0){
                    throw std::runtime_error("var::matrix::inv -> Determinant is 0");
                }
                return adj()/detm;
            }

            /**
             * @brief Reduced row echolon form 
             * 
             * @return ``matrix`` 
             */
            matrix rref(){
                matrix temp = *this;
                auto RREF = [](matrix &A)->void{

                    int lead = 0;

                    for(int r = 0; r < A.row(); r++){
                        if(lead >= A.col()){
                            return;
                        }

                        int i = r;

                        while(A[i][lead] == 0)
                        {
                            i++;
                            if(i >= A.row()){
                                i = r;
                                lead++;
                                if(lead >= A.col()){
                                    return;
                                }
                            }
                        }

                        A.row_swap(i, r);

                        auto divide_row = [&](matrix &B, int i, D v)->void{
                            assert(A[r][lead] != 0);
                            for(int j = 0; j < B.col(); j++){
                                B[i][j] /= v;
                            }
                        };
                        auto add_rows = [](matrix &B, int i, int k, D v)->void{
                            for(int j = 0; j < B.col(); j++){
                                B[i][j] += v*B[k][j];
                            }
                        };

                        divide_row(A, r, A[r][lead]);

                        for(i = 0; i < A.row(); i++){
                            if(i != r){
                                add_rows(A, i, r, -A[i][lead]);
                            }
                        }
                    }
                };
                RREF(temp);
                return temp;
            }

            /**
             * @brief Row echolon form 
             * 
             * @return ``matrix`` 
             */
            matrix ref(){
                matrix temp = *this;
                int nr = _row;
                int nc = _col;
                for(int r = 0; r < nr; r++){
                    bool allZeros = true;
                    for(int c = 0; c < nc; c++){
                        if(temp.data[r][c] != D(0)){
                            allZeros = false;
                            break;
                        }
                    }
                    if(allZeros){
                        nr--;
                        temp.row_swap(r, nr);
                    }
                }

                int p = 0;
                while(p < nr && p < nc)
                {
                    nextPivot:
                        int r = 1;
                        while(temp.data[p][p] == D(0))
                        {
                            if((p+r) <= nr){
                                p++;
                                goto nextPivot;
                            }
                            temp.row_swap(p, (p+r));
                            r++;
                        }
                        for(r = 1; r < (nr-p); r++){
                            if(temp.data[p+r][p] != D(0)){
                                int x = -temp.data[p+r][p]/temp.data[p][p];
                                for(int c = p; c < nc; c++){
                                    temp.data[p+r][c] = temp.data[p][c]*x+temp.data[p+r][c]; 
                                }

                            }
                        }
                        p++;
                }
                return temp;
            }

            /**
             * @brief PLU decomposition 
             * 
             * **Usage**:
             * ```cpp
             * // the output is LU struct 
             * auto LU = m.plu();
             * auto L = LU.L;
             * auto U = LU.U;
             * auto P = LU.p;
             * ```
             * 
             * @return ``LU`` 
             */
            LU plu(){
                LU lu;
                int n = fmax(_col, _row);

                lu.U.resize(n, n);
                lu.L.resize(n, n);
                lu.P.resize(n, n);

                matrix temp = *this;

                auto f = [&](LU &a, matrix b)->void{
                    std::vector<int> perm(n);
                    std::iota(perm.begin(), perm.end(), 0);
                    
                    for(int j = 0; j < n; j++){
                        int max_index = j;
                        D max_value = D(0);
                        for(int i = j; i < n; i++){
                            D value = D(abs(b.data[perm[i]][j]));
                            if(value > max_value){
                                max_index = i;
                                max_value = value;
                            }
                        }
                        if(max_value <= std::numeric_limits<D>::epsilon()){
                            throw std::runtime_error("var::matrix::plu -> Matrix is singular");
                        }
                        if(j != max_index){
                            std::swap(perm[j], perm[max_index]);
                        }
                        int jj = perm[j];
                        for(int i = j+1; i < n; i++){
                            int ii = perm[i];
                            b.data[ii][j] /= b.data[jj][j];
                            for(int k = j+1; k < n; k++){
                                b.data[ii][k] -= b.data[ii][j]*b.data[jj][k];
                            }
                        }
                    }
                    for(int j = 0; j < n; j++){
                        a.L.data[j][j] = 1;
                        for(int i = j+1; i < n; i++){
                            a.L.data[i][j] = b.data[perm[i]][j];
                        }
                        for(int i = 0; i <= j; i++){
                            a.U.data[i][j] = b.data[perm[i]][j];
                        }
                    }
                    for(int i = 0; i < n; i++){
                        a.P.data[i][perm[i]] = 1;
                    }
                    a.P = a.P.inv();
                };
                if(!is_square()){
                    matrix eyed = num::mat::eye<D>(n); 
                    if(n == _row){
                        temp.join_col(eyed(0, _row, 0, fabs(_row-_col)));
                        f(lu, temp);
                        for(int i = 0; i < fabs(_row-_col); i++){
                            lu.U.pop_col();
                            
                            lu.L.pop_col();
                            lu.L.pop_row();

                            lu.P.pop_row();
                            lu.P.pop_col();
                        }
                    }
                    else{
                        temp.join_row(eyed(0, fabs(_row-_col), 0, _col));
                        f(lu, temp);
                        for(int i = 0; i < fabs(_row-_col); i++){
                            lu.U.pop_row();

                            lu.L.pop_col();
                            lu.L.pop_row();

                            lu.P.pop_row();
                            lu.P.pop_col();
                        }
                    }
                }
                else{
                    f(lu, temp);
                }
                return lu;
            }

            /**
             * @brief Checks if matrix is square 
             * 
             * **Usage**:
             * ```cpp
             * bool square = m.is_square();
             * ```
             * 
             * @return true 
             * @return false 
             */
            bool is_square(){
                return _row == _col;
            }

            /**
             * @brief Returns if the matrix is empty or not
             * 
             * @return true 
             * @return false 
             */
            bool is_empty(){
                return data.empty();
            }

            /**
             * @brief Checks if matrix is an identity matrix
             * 
             * @return true 
             * @return false 
             * 
             * ## Operator methods 
             * 
             */
            bool is_identity(){
                if(is_square()){
                    int count_zeros = 0;
                    int count_ones = 0;
                    for(int i = 0; i < _row; i++){
                        for(int j = 0; j < _col; j++){
                            if(i == j && round(data[i][j]) == D(1)){
                                count_ones++;
                            }
                            else if (i != j && round(data[i][j]) == D(0)){
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
             * @brief [][] operator for ``matrix``
             * 
             * **Usage**:
             * ```cpp
             * // m[row][col]
             * m[0][0] = 5;
             * ```
             * 
             * * Does not check the correct row and colum index;
             * 
             * @param i row index
             * @return ``Col`` which then returns &D 
             */
            Col operator[](int i){
                return Col(*this, i);
            }

// ***************************** + operator ************************** //

            /**
             * @brief Matrix addition
             * 
             * **Usage**:
             * ```cpp
             * // m1 and m2 are matrix class
             * auto summed = m1+m2; 
             * ```
             * 
             * @param other 
             * @return ``matrix`` 
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
             * @brief ``matrix+var`` as ``var`` as added to all elements
             * 
             * **Usage**:
             * ```cpp
             * auto m_add_2 = m+2; // or 2+m 
             * ```
             * 
             * @param n variable to add 
             * @return ``matrix`` 
             */
            matrix operator +(D n){
                matrix temp = *this;
                for(int i = 0; i < _row; i++){
                    for(int j = 0; j < _col; j++){
                        temp.data[i][j] = data[i][j]+n;
                    }
                }
                return temp;
            }

            /**
             * @brief ``var+matrix``
             * 
             * @param n variable to add
             * @param other ``matrix``
             * @return ``matrix`` 
             */
            friend matrix operator +(D n, matrix &other){
                return other+n;
            }

            /**
             * @brief Increments current matrix by matrix ``a``
             * 
             * **Usage**:
             * ```cpp
             * m1+=m2; // m1,m2 -> matrix
             * ```
             * 
             * @param a ``matrix``
             */
            void operator +=(matrix a){
                *this = *this+a;
            }

            /**
             * @brief Specific variable increment 
             * 
             * **Usage**:
             * ```cpp
             * m+=2; // increments every element by 2
             * ```
             * 
             * @param a increments each value by a 
             */
            void operator +=(D a){
                matrix temp = *this;
                temp.turn_to(a);
                *this += temp;
            }

            /**
             * @brief Increment operator 
             * 
             * **Usage**:
             * ```cpp
             * m++; all values will be increased by 1
             * ```
             * 
             * @param a 
             */
            void operator ++(int a){
                *this += D(1);
            }

// ***************************** - operator ************************** //

            /**
             * @brief Negative of a matrix
             * 
             * **Usage**:
             * ```cpp
             * auto negated = -m; 
             * ```
             * 
             * @return ``matrix`` 
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
             * @brief Matrix subtraction
             * 
             * **Usage**:
             * ```cpp
             * auto subtracted = m1-m2; 
             * ```
             * 
             * @param other ``matrix``
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
             * @brief ``matrix-var``
             * 
             * **Usage**:
             * ```cpp
             * auto m_take_2 = m-2; // or 2-m 
             * ``` 
             * 
             * @param n variable to add
             * @return ``matrix`` 
             */
            matrix operator -(D n){
                matrix temp = *this;
                for(int i = 0; i < _row; i++){
                    for(int j = 0; j < _col; j++){
                        temp.data[i][j] = data[i][j]-n;
                    }
                }
                return temp;
            }

            /**
             * @brief ``var-matrix``
             * 
             * @param n variable to add
             * @param other ``matrix``
             * @return ``matrix`` 
             */
            friend matrix operator -(D n, matrix &other){
                matrix temp = -other;
                return n+temp;
            }

            /**
             * @brief Decrement current matrix by matrix ``a`` 
             * 
             * **Usage**:
             * ```cpp
             * m1 -= m2;
             * ```
             * 
             * @param a ``matrix``
             */
            void operator -=(matrix a){
                *this = *this-a;
            }

            /**
             * @brief Decrement current matrix by value ``a`` 
             * 
             * **Usage**:
             * ```cpp
             * m -= 2; // subtracts each element by 2
             * ```
             * 
             * @param a Decrements each value by a 
             */
            void operator -=(D a){
                matrix temp = *this;
                temp.turn_to(a);
                *this -= temp;
            }

            /**
             * @brief Decrement operator 
             * 
             * **Usage**:
             * ```cpp
             * m--; // deacreses every value of m by 1 
             * ```
             * 
             * @param a 
             */
            void operator --(int a=1){
                *this -= D(1);
            }

// ***************************** * operator ************************** //

            /**
             * @brief Matrix multiplication 
             * 
             * **Usage**:
             * ```cpp
             * auto matrix_mul = m*m;
             * ```
             * 
             * @param other ``matrix``
             * @return ``matrix`` 
             */
            matrix operator *(matrix const &other){
                // condition 
                if(_row != other._col && _col != other._row){
                    throw std::invalid_argument("var::matrix::operator * -> Size mismatch");
                }
                auto SUM = [this, other](int i, int j)-> D {
                    D summ = D();
                    for(int k = 0; k < _col; k++){
                        summ += data[i][k]*other.data[k][j];
                    }
                    return summ;
                };
                matrix temp(_row, other._col);
                for(int i = 0; i < _row; i++){
                    for(int j = 0; j < other._col; j++){
                        temp.data[i][j] = SUM(i, j);
                    }
                }
                return temp;
            }

            /**
             * @brief ``matrix*var``
             * 
             * **Usage**:
             * ```cpp
             * auto m_by_2 = m*2; // or 2*m
             * ```
             * 
             * @param n variable multiplying with 
             * @return ``matrix`` 
             */
            matrix operator *(D n){
                matrix temp = *this;
                for(int i = 0; i < _row; i++){
                    for(int j = 0; j < _col; j++){
                        temp.data[i][j] = data[i][j]*n;
                    }
                }
                return temp;
            }

            /**
             * @brief Normal multiplicatoin 
             * 
             * **Usage**:
             * ```cpp
             * auto mul_m = m1.mathmul(m2);
             * ``` 
             * 
             * @param other ``matrix``
             * @return ``matrix`` 
             */
            matrix mathmul(matrix const &other){
                // condition 
                check_size(other._row, other._col); 
                matrix temp(_row, _col);
                for(int i = 0; i < _row; i++){
                    for(int j = 0; j < _col; j++){
                        temp.data[i][j] = data[i][j]*other.data[i][j];
                    }
                }
                return temp;
            }

            /**
             * @brief ``var*matrix``
             * 
             * @param n variable multiplying with 
             * @param other ``matrix`` 
             * @return ``matrix`` 
             */
            friend matrix operator *(D n, matrix &other){
                return other*n;
            }

// ***************************** / operator ************************** //

            /**
             * @brief Matrix division using inverse 
             * 
             * @param other ``matrix`` 
             * @return ``matrix`` 
             */
            matrix operator /(matrix &other){
                matrix temp = *this*other.inv(); 
                return temp;
            }

            /**
             * @brief ``matrix/var`` 
             * 
             * **Usage**:
             * ```cpp
             * auto m_over_2 = m/2; // 2/m can work
             * ```
             * 
             * @param n our variable
             * @return ``matrix``
             */
            matrix operator /(D n){
                matrix temp(_row, _col);
                temp.data = data;
                for(int i = 0; i < _row; i++){
                    for(int j = 0; j < _col; j++){
                        temp.data[i][j] = data[i][j]/n;
                    }
                }
                return temp;
            }

            /**
             * @brief Normal math division 
             * 
             * **Usage**:
             * ```cpp
             * auto divided = m1.mathdiv(m2);
             * ```
             * 
             * @param other ``matrix``
             * @return ``matrix`` 
             */
            matrix mathdiv(matrix const &other){
                check_size(other._row, other._col); 
                matrix temp(_row, _col);
                for(int i = 0; i < _row; i++){
                    for(int j = 0; j < _col; j++){
                        temp.data[i][j] = data[i][j]/other.data[i][j];
                    }
                }
                return temp;
            }

            /**
             * @brief ``var/matrix``
             * 
             * @param n our variable
             * @param other ``matrix``
             * @return ``matrix`` 
             */
            friend matrix operator /(D n, matrix &other){
                matrix temp = other;
                for(int i = 0; i < other._row; i++){
                    for(int j = 0; j < other._col; j++){
                        assert(temp.data[i][j] > D(0));
                        temp.data[i][j] = n/temp.data[i][j];
                    }
                }
                return temp;
            }

// ***************************** () operator ************************** //

            /**
             * @brief Returns a sliced matrix
             * 
             * **Usage**:
             * ```cpp
             * // m(inclusive, exclusive)
             * auto sliced = m(1, 3); // row-1 to row-2
             * ```
             * 
             * @param i1 index row 1 (inclusive)
             * @param i2 index row 2 (exclusive)
             * @return ``matrix`` 
             */
            matrix operator()(int i1, int i2){
                check_row(i1);
                check_row(i2-1);
                matrix temp;
                for(int i = i1; i < i2; i++){
                    temp.push_row(get_row(i));
                }
                return temp;
            }

            /**
             * @brief Column per row slicing 
             * 
             * * Condition ``j2 >= j1`` must be true. 
             * 
             * @param i row index
             * @param j1 column index 1 (inclusive)
             * @param j2 column index 2 (exclusive)
             * @return ``std::vector<D>`` 
             */
            std::vector<D> operator()(int i, int j1, int j2){
                check_row(i);
                check_col(j1);
                check_col(j2-1);
                std::vector<D> temp;
                for(int j = j1; j < j2; j++){
                    temp.push_back(data[i][j]);
                }
                return temp;
            }

            /**
             * @brief Row and column slice 
             * 
             * @param i1 row index 1 (inclusive)
             * @param i2 row index 2 (exclusive)
             * @param j1 column index 1 (inclusive)
             * @param j2 column index 2 (exclusive)
             * @return matrix 
             * 
             * !!! warning "Exception"    
             * <pre>
             *     All ``()`` operators will throw an <code>std::invalid_argument</code> if&#58;  
             *         1. Index must be correct
             *         2. ``i2>=i1`` and ``j2>=j1``  
             * </pre>
             * 
             */
            matrix operator()(int i1, int i2, int j1, int j2){
                check_row(i1);
                check_row(i2-1);
                check_col(j1);
                check_col(j2-1);
                matrix temp;
                if(i2 == i1){
                    temp.resize(1, j2-j1);
                }
                else if(j2 == j1){
                    temp.resize(i2-i1, 1);
                }
                else if(i2 == i1 && j2 == j1){
                    temp.resize(1, 1);
                }
                else{
                   temp.resize(i2-i1, j2-j1);
                }
                for(int i = i1; i < i2; i++){
                    for(int j = j1; j < j2; j++){
                        temp.data[i][j] = data[i][j];
                    }
                }
                return temp;
            }

// *********************** conditional operators ******************** //

            /**
             * @brief Equals to operator 
             * 
             * **Usage**:
             * ```cpp
             * bool eq = (m1 == m2);
             * ````
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
             * @brief Less than operator
             * 
             * @param other ``matrix``
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
             * @brief Less than or equal
             * 
             * @param other ``matrix``
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
             * @brief More than
             * 
             * @param other ``matrix``
             * @return true 
             * @return false 
             */
            bool operator>(matrix other){
                return !(*this <= other);
            }

            /**
             * @brief More than or equal 
             * 
             * @param other ``matrix``
             * @return true 
             * @return false 
             */
            bool operator>=(matrix other){
                return !(*this < other);
            }        

            /**
             * @brief Not equal method
             * 
             * @param other ``matrix``
             * @return true 
             * @return false 
             */
            bool operator!=(matrix other){
                return !(*this == other);
            }

// ***************************** % operator ************************** //
            
            /**
             * @brief Moudlus operator 
             * 
             * **Usage**:
             * ```cpp
             * auto m_divisably_2 = m%2;
             * ```
             * 
             * @param n modulus variable
             * @return ``matrix`` 
             */
            matrix operator %(D n){
                matrix temp = *this;
                for(int i = 0; i < _row; i++){
                    for(int j = 0; j < _col; j++){
                        temp.data[i][j] = data[i][j]%n;
                    }
                }
                return temp;
            }

// ************************* stream operator ************************ //

            /**
             * 
             * @brief Output method for matrices
             *
             * **Usage**:
             * 
             * ```cpp
             * std::cout << m;
             * ```
             * 
             * @tparam D 
             * @param out 
             * @param other 
             * @return std::ostream& 
             */
            friend std::ostream& operator << (std::ostream& out, matrix const &other){
                for(int i = 0; i < other._row; i++){
                    for(int j = 0; j < other._col; j++){
                        out << other.data[i][j];
                        if(j < other._col-1){
                            out << ",";
                        }
                    }
                    if(i != other._row-1){
                        out << "\n";
                    }
                }
                return out;
            }

            /**
             * @brief Input method for matrices 
             * 
             * **Usage**:
             * ```cpp
             * std::cin >> m;
             * ```
             * 
             * @param input x
             * @param other 
             * @return std::istream& 
             * 
             * !!! note "Note"  
             * <pre>
             *     The input and output method rely on the following configuration (3 rows amd 4 colums in this case)
             *        ```
             *        1,2,3,4
             *        5,6,7,8
             *        9,2,1,5
             *        ```
             * </pre>
             * 
             */
            friend std::istream &operator >> (std::istream  &input, matrix &other){
                std::vector<D> temp;
                other.resize(0, 0);
                while(input.good())
                {
                    input >> temp;
                    if(input.eof()){
                        break;
                    }    
                    other.push_row(temp);
                    temp.clear();       
                }
                return input;
            }
    };
};