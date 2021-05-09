#pragma once
#include "../vectors/vector.hpp"
#include <algorithm>
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
                        _a.check_row(_i);
                        _a.check_col(j);
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
             * @param j colum index 
             */
            void check_col(int j){
                if(j < 0 || j >= _col){
                    throw std::out_of_range("Col index is out of range");
                }
            }

            /**
             * @brief checks index for rows
             * 
             * @param i row index
             */
            void check_row(int i){
                if(i < 0 || i >= _row){
                    throw std::out_of_range("Row index is out of range");
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
             * @param c colum
             */
            void check_size(int r, int c){
                if(c != _col || r != _row){
                    throw std::invalid_argument("Size mismatch");
                }
            }
            
            /**
             * @brief minor of a matrix
             * 
             * @param i row
             * @param j colum
             * @param other ``matrix`` type
             * @return ``matrix`` 
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
            table<D> data;
            int _row;
            int _col;
        public:
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
             * @brief Resizes the matrix
             * 
             * ### Usage:
             * ```cpp
             * m.resize(5, 6);
             * ``` 
             * 
             * !!! warning "Warning"  
             * <pre>
             *     This resets all elements in the matrix
             * </pre>
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
                    data.push_back(std::vector<D>(_col));
                }
            }

            /**
             * @brief Returns the number of rows
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
             * @brief Returns the row at an index
             * 
             * @param i row index  
             * @return ``std::vector<D>`` 
             */
            std::vector<D> get_row(int i){
                check_row(i);
                return data[i];
            }

            /**
             * @brief Returns the colum at an index
             * 
             * Usage:  
             * ```cpp
             * var::matrix<int> m(3, 3);
             * auto col = m.get_col(1);
             * ```
             * 
             * @param j colum index 
             * @return ``std::vector<D>``
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
             * @brief Inserts row at the end or the matrix
             * 
             * **Usage**:  
             * ```cpp
             * var::matrix<int> m(3, 3);
             * m.push_row(1, {1, 2, 3});
             * ```
             * 
             * @param a row vector
             */
            void push_row(const std::vector<D>& a){
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
             * @brief Inserts column at the end of the matrix
             * 
             * @param a colum vector
             */
            void push_col(const std::vector<D>& a){
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
             * @brief Inserts row at specefic index 
             * 
             * **Usage**:  
             * ```cpp
             * var::matrix<int> m(3, 3);
             * m.insert_row(1, {1, 2, 3});
             * ```
             * 
             * @param i row index
             * @param a row vector
             */
            void insert_row(int i, std::vector<D> a){
                if(a.size() != _col){
                    throw std::invalid_argument("Size doesnt match");
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
             * **Usage**:  
             * ```cpp
             * var::matrix<int> m(3, 3);
             * m.insert_col(1, {1, 2, 3});
             * ```
             * 
             * @param j column index 
             * @param a colum vector
             */
            void insert_col(int j, const std::vector<D>& a){
                if(a.size() != _row){
                    throw std::invalid_argument("Size doesnt match");
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
             * @brief Erase row at index
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
             * **Usage**:
             * ```cpp
             * var::matrix<int> m(3, 3);
             * m.erase_col(1);
             * ```
             * 
             * @param j colum index
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
             * @brief Sorts all rows
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
             * @brief Sorts colum at specefic index
             * 
             * @param j colum index  
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
             * @tparam LAMBDA: ``std::function`` 
             * @param i colum index
             * @param f function to change colum elements
             */
            template<typename LAMBDA> 
            void row_op(int i, LAMBDA f){
                check_row(i);
                for(int j = 0; j < _col; j++){
                    data[i][j] = f(data[i][j]);
                }
            }

            /**
             * @brief Does operations on a specefic colum
             * 
             * @tparam LAMBDA: ``std::function`` 
             * @param j colum index 
             * @param f function to change colum elements
             *  
             * !!! warning "Exception"    
             * <pre>
             *     All row and colum operations (inserting, removing .. etc) throw an <code>std::invalid_argument</code> if&#58;  
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
             * @brief Converts all elements to n
             * 
             * @param n the specifeid variable
             * 
             * !!! note "Note"    
             * <pre>
             *     All the functions listed abover **mutate** the original matrix  
             * </pre>
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
             * @return D 
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
             * @brief trace of a matrix
             * 
             * @return D 
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
             * @return D 
             */
            D det(){
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
             * @brief var+matrix
             * 
             * @param n 
             * @param other 
             * @return matrix 
             */
            friend matrix operator +(D n, matrix &other){
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
             * @brief var-matrix
             * 
             * @param n 
             * @param other 
             * @return matrix 
             */
            friend matrix operator -(D n, matrix &other){
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
             * @brief matrix*var
             * 
             * @param n 
             * @return matrix 
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
             * @brief var*matrix
             * 
             * @param n 
             * @param other 
             * @return matrix 
             */
            friend matrix operator *(D n, matrix &other){
                return other*n;
            }

// ***************************** / operator ************************** //

            matrix operator /(matrix &other){
                return *this*other.inv();
            }

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

            friend matrix operator /(D n, matrix &other){
                matrix temp = other;
                for(int i = 0; i < other._row; i++){
                    for(int j = 0; j < other._col; j++){
                        temp.data[i][j] = n/temp.data[i][j];
                    }
                }
                return temp;
            }

// ***************************** % operator ************************** //
            matrix operator %(D n){
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
             * @brief input operator 
             * 
             * @param input x
             * @param other 
             * @return std::istream& 
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
    // TODO add normal multiplication
    // TODO add row and col swap
    // TODO rref 
    // TODO test division 
    // TODO test exceptions
    // TODO add mat_op 
    // TODO add replace row and colum 
};