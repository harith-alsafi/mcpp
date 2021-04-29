#pragma once
#include "../vectors/vector.hpp"
#include <algorithm>
#include <cmath>

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
            // 2d vector
            template<typename T> 
            using table = std::vector<std::vector<T>>;
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
            
            /**
             * @brief minor of a matrix
             * 
             * @param i 
             * @param j 
             * @param other 
             * @return matrix 
             */
            matrix M(int i, int j, matrix &other) {
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
             * @brief recursive determinant 
             * 
             * @param a 
             * @return S 
             */
            S DET(matrix a){
                // 2x2 determinant
                if(a.col() == 2){
                    return (a[0][0]*a[1][1])-(a[1][0]*a[0][1]);
                }
                // n by n
                S sum = S();
                for(int j = 0; j < a.col(); j++){              
                    sum += a[0][j]*std::pow((-1), 0+j)*DET(M(0, j, a));                  
                }
                return sum;
            }

            /**
             * @brief throws exception if matrix is not a square
             * 
             */
            void square(){
                if(!is_square()){
                    throw std::invalid_argument("Matrix is not a square");
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
             * @brief returns the row at an index
             * 
             * @param i 
             * @return std::vector<S> 
             */
            std::vector<S> get_row(int i){
                check_row(i);
                return data[i];
            }

            /**
             * @brief returns the colum at an index
             * 
             * @param j 
             * @return std::vector<S> 
             */
            std::vector<S> get_col(int j){
                check_col(j);
                std::vector<S> temp;
                for(int i = 0; i < _row; i++){
                    temp.push_back(data[i][j]);
                }
                return temp;
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
             * @brief removes last row
             * 
             */
            void pop_row(){
                if(_row == 0){
                    throw std::invalid_argument("No rows to remove");
                }
                data.pop_back();
                _row = data.size();
            }

            /**
             * @brief removes last colum
             * 
             */
            void pop_col(){
                if(_col == 0){
                    throw std::invalid_argument("No colums to remove");
                }
                for(int i = 0; i < _row; i++){
                    data[i].pop_back();
                }
                _col = data[0].size();
            }
            
            /**
             * @brief erase row at index
             * 
             * @param i 
             */
            void erase_row(int i){
                check_row(i);
                data.erase(data.begin()+i);
                _row = data.size();
            }

            /**
             * @brief erase column at index
             * 
             * @param j 
             */
            void erase_col(int j){
                check_col(j);
                for(int i = 0; i < _row; i++){
                    data[i].erase(data[i].begin()+j);
                }
                _col = data[0].size();
            }

            /**
             * @brief sorts all rows
             * 
             * @param d 
             * d = 1 is accending order -> sort_rows()
             * d = 0 is decending order -> sort_rows(0)
             */
            void sort_rows(int d = 1){
                for(int i = 0; i < _row; i++){
                    sort_row(i, d);
                }
            }

            /**
             * @brief sorts all columns 
             * 
             * @param d 
             * d = 1 is accending order -> sort_cols()
             * d = 0 is decending order -> sort_cols(0)
             */
            void sort_cols(int d = 1){
                for(int j = 0; j < _col; j++){
                    sort_col(j, d);
                }
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
                auto dec = [](int a, int b)-> bool {return a > b;}; 
                if(d == 1){ // accending 
                    std::sort(data[i].begin(), data[i].end());
                }
                else{ // decending 
                    std::sort(data[i].begin(), data[i].end(), dec);
                }
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
                sort_row(j, d); // sort transposed
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
                for(int j = 0; j < _col; j++){
                    data[i][j] = f(data[i][j]);
                }
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
                for(int i = 0; i < _row; i++){
                    data[i][j] = f(data[i][j]);
                }
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
                S SUM = S();
                for(int i = 0; i < _row; i++){
                    for(int j = 0; j < _col; j++){
                        SUM += data[i][j];
                    }
                }
                return SUM;
            }

            /**
             * @brief trace of a matrix
             * 
             * @return S 
             */
            S tr(){
                square();
                S sum = S();
                for(int i = 0; i < _row; i++){
                    sum+= data[i][i];
                }
                return sum;
            }

            /**
             * @brief returns transpose 
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
             * @brief returns the determinant 
             * 
             * @return S 
             */
            S det(){
                square();
                return DET(*this);
            }

            /**
             * @brief returns cofactor matrix
             * 
             * @return matrix 
             */
            matrix cofactor(){
                square();
                matrix temp(_row, _col);
                for(int i = 0; i < _row; i++){
                    for(int j = 0; j < _col; j++){
                        auto m = M(i, j, *this);
                        temp[i][j] = pow((-1), (i+j))*m.det();
                    }
                }
                return temp;
            }

            /**
             * @brief adjugate of a matrix
             * 
             * @return matrix 
             */
            matrix adj(){
                square();
                matrix temp = cofactor();
                return temp.T();
            }

            /**
             * @brief returns inverse of a matrix
             * 
             * @return matrix 
             */
            matrix inv(){
                square();
                return adj()/det();
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

            /**
             * @brief matrix multiplication 
             * 
             * @param other 
             * @return matrix 
             */
            matrix operator *(matrix const &other){
                // condition 
                if(!(_row == other._col && _col == other._row)){
                    throw std::invalid_argument("Size mismatch");
                }
                auto SUM = [this, other](int i, int j)-> S {
                    S summ = S();
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

            matrix operator /(matrix &other){
                return *this*other.inv();
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

// ***************************** % operator ************************** //
            matrix operator %(S n){
                matrix temp = *this;
                for(int i = 0; i < _row; i++){
                    for(int j = 0; j < _col; j++){
                        temp.data[i][j] = data[i][j]%n;
                    }
                }
                return temp;
            }

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
             * @brief input operator 
             * 
             * @param input 
             * @param other 
             * @return std::istream& 
             */
            friend std::istream &operator >> (std::istream  &input, matrix &other){
                std::vector<S> temp;
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
    // TODO add matrix power
    // TODO add normal multiplication
    // TODO add row and col swap
};