// #include "../../includes/variables/matrix.hpp"
// #include <algorithm>
// #include <cmath>
// #include <iostream>
// #include <complex>
// #include "../../includes/misc/constants.hpp"

// using var::matrix;

// template<typename S>
// void matrix<S>::check_col(int j){
//     if(j < 0 || j >= _col){
//         throw std::out_of_range("Col index is out of range");
//     }
// }

// template<typename S>
// void matrix<S>::check_row(int i){
//     if(i < 0 || i >= _row){
//         throw std::out_of_range("Row index is out of range");
//     }
// }

// template<typename S>
// table<S> matrix<S>::TT(){
//     // temps
//     std::vector<S> temp_col;
//     table<S> temp;
//     // reversing rows with colums
//     for(int i = 0; i < _col; i++){
//         temp_col.clear();
//         for(int j = 0; j < _row; j++){
//             temp_col.push_back(data[j][i]);
//         }
//         temp.push_back(temp_col);
//     }
//     // applying to data variable
//     return temp;
// }

// template<typename S>
// void matrix<S>::check_size(int r, int c){
//     if(c != _col || r != _row){
//         throw std::invalid_argument("Size mismatch");
//     }
// }

// template<typename S>
// matrix<S>::matrix(int r, int c){
//     resize(r, c);
// }

// template<typename S>
// matrix<S>::matrix(): _row(0), _col(0){}

// template<typename S>
// matrix<S>::matrix (std::initializer_list<std::initializer_list<S>> a){ 
//     _row = a.size();
//     _col = a.begin()->size();
//     std::vector<S> vect_row;
//     for(auto &i: a){
//         vect_row.clear();
//         for(auto &j: i){
//             vect_row.push_back(j);
//         }
//         data.push_back(vect_row);
//     }
// }

// template<typename S>
// void matrix<S>::resize(int r, int c){
//     // checking 
//     if(r < 0 || c < 0){
//         throw std::invalid_argument("Invalid values");
//     }
//     _row = r;
//     _col = c;
//     data.clear();
//     for(int i = 0; i < _row; i++){
//         data.push_back(std::vector<S>(_col));
//     }
// }

// template<typename S>
// int matrix<S>::row(){
//     return _row;
// }

// template<typename S>
// int matrix<S>::col(){
//     return _col;
// }

// template<typename S>
// int matrix<S>::size(){
//     return _col*_row;
// }

// template<typename S>
// void matrix<S>::push_row(const std::vector<S>& a){
//     // checking size
//     if(a.size() != _col && _row != 0 && _col != 0){
//         throw std::invalid_argument("Size doesnt match");
//     }
//     else if(_row == 0 && _col == 0){
//         resize(1, a.size());
//         data[0] = a;
//         return;
//     }
//     data.push_back(a);
//     _row = data.size();
// }

// template<typename S>
// void matrix<S>::push_col(const std::vector<S>& a){
//     // checking size
//     if(a.size() != _row && _row != 0 && _col != 0){
//         throw std::invalid_argument("Size doesnt match");
//     }
//     else if(_row == 0 && _col == 0){
//         resize(a.size(), 1);
//         for(int i = 0; i < _row; i++){
//             data[i][0] = a[i];
//         }
//         return;
//     }
//     for(int i = 0; i < _row; i++){
//         data[i].push_back(a[i]);
//     }
//     _col = data[0].size(); // since all colums have same size
// }

// template<typename S>
// void matrix<S>::insert_row(int i, std::vector<S> a){
//     if(a.size() != _col){
//         throw std::invalid_argument("Size doesnt match");
//     }
//     check_row(i);
//     typename table<S>::iterator it = data.begin();
//     std::advance(it, i);
//     data.insert(it, a);
//     _row = data.size();
// }

// template<typename S>
// void matrix<S>::insert_col(int j, const std::vector<S>& a){
//     if(a.size() != _row){
//         throw std::invalid_argument("Size doesnt match");
//     }
//     check_col(j);
//     typename std::vector<S>::iterator it;
//     for(int i = 0; i < _row; i++){
//         it = data[i].begin();
//         std::advance(it, j);
//         data[i].insert(it, a[i]);
//     }
//     _col = data[0].size(); // since all colums have same size
// }

// template<typename S>
// matrix<S> matrix<S>::T(){
//     matrix temp;
//     temp.resize(_col, _row);
//     temp.data = TT();
//     return temp;
// }

// template<typename S>
// matrix<S> matrix<S>::sort_rows(int d){
//     matrix temp = *this;
//     auto dec = [](int a, int b)-> bool {return a > b;}; // lambda function
//     for(int i = 0; i < _row; i++){
//         if(d == 1){ // accending 
//             std::sort(temp.data[i].begin(), temp.data[i].end());
//         }
//         else{ // decending 
//             std::sort(temp.data[i].begin(), temp.data[i].end(), dec);
//         }
//     }
//     return temp;
// }

// template<typename S>
// matrix<S> matrix<S>::sort_cols(int d){
//     matrix temp = *this;
//     matrix temp2;

//     temp = temp.T();
//     temp2 = temp.sort_rows(d);
//     temp = temp2.T();

//     return temp;
// }

// template<typename S>
// void matrix<S>::sort_row(int i, int d){
//     check_row(i);
// }

// template<typename S>
// void matrix<S>::sort_col(int j, int d){
//     check_col(j);
//     data = TT(); // transpose
//     sort_row(j, d); // sort transposed
//     data = TT(); // transpose back
// }

// template<typename S>
// template<typename LAMBDA> 
// void matrix<S>::row_op(int i, LAMBDA f){
//     check_row(i);
// }

// template<typename S>
// template<typename LAMBDA> 
// void matrix<S>::col_op(int j, LAMBDA f){
//     check_col(j);
// }

// template<typename S>
// void matrix<S>::turn_to(S n){
//     for(int i = 0; i < _row; i++){
//         for(int j = 0; j<_col; j++){
//             data[i][j] = n;
//         }
//     }
// }

// template<typename S>
// S matrix<S>::sum(){
//     S SUM = S();
//     for(int i = 0; i < _row; i++){
//         for(int j = 0; j < _col; j++){
//             SUM += data[i][j];
//         }
//     }
//     return SUM;
// }

// template<typename S>
// S matrix<S>::det(){
//     // condition 
//     if(!is_square()){
//         throw std::invalid_argument("Matrix is not a square");
//     }
//     // 2x2 determinant
//     auto D = [](int a, int b, int c, int d)-> S{
//         return a*d+c*d;
//     };
//     // 3 by 3 minor
//     auto M = [](int i, int j, matrix &other)-> matrix {
//         matrix a(other.row()-1, other.col()-1);
//     };
//     // cofactor 
//     // auto C = [](int i, int j)->S{
        
//     // };
// }


// template<typename S>
// matrix<S> matrix<S>::inv(){

// }

// template<typename S>
// matrix<S> matrix<S>::rref(){

// }

// template<typename S>
// bool matrix<S>::is_square(){
//     return _row == _col;
// }

// template<typename S>
// bool matrix<S>::is_identity(){
//     if(is_square()){
//         int count_zeros = 0;
//         int count_ones = 0;
//         for(int i = 0; i < _row; i++){
//             for(int j = 0; j < _col; j++){
//                 if(i == j && data[i][j] == 1){
//                     count_ones++;
//                 }
//                 else if (i != j && data[i][j] == 0){
//                     count_zeros++;
//                 }
//             }
//         }
//         if(count_ones+count_zeros == _row*_col && count_ones == _row){
//             return true;
//         }
//     }
//     return false;
// }

// // ***************************** [] operator ************************** //

// template<typename S>
// matrix<S>::Col::Col(matrix& a, int i): _a(a), _i(i){}

// template<typename S>
// S& matrix<S>::Col::operator[](int j){
//     _a.check_row(_i);
//     _a.check_col(j);
//     return _a.data[_i][j];
// }

// template<typename S>
// typename matrix<S>::Col matrix<S>::operator[](int i){
//     return Col(*this, i);
// }

// // ***************************** + operator ************************** //

// template<typename S>
// matrix<S> matrix<S>::operator +(matrix const &other){
//     check_size(other._row, other._col); 
//     matrix temp(_row, _col);
//     temp.data = data;
//     for(int i = 0; i < _row; i++){
//         for(int j = 0; j < _col; j++){
//             temp.data[i][j] = data[i][j]+other.data[i][j];
//         }
//     }
//     return temp;
// }

// template<typename S>
// matrix<S> matrix<S>::operator +(S n){
//     matrix temp = *this;
//     for(int i = 0; i < _row; i++){
//         for(int j = 0; j < _col; j++){
//             temp.data[i][j] = data[i][j]+n;
//         }
//     }
//     return temp;
// }

// template<typename S>
// matrix<S> var::operator+ (S n, matrix<S> &other){
//     return other+n;
// }

// // ***************************** - operator ************************** //

// template<typename S>
// matrix<S> matrix<S>::operator -(){
//     matrix temp = *this;    
//     for(int i = 0; i < _row; i++){
//         for(int j = 0; j < _col; j++){
//             temp.data[i][j] = -data[i][j];
//         }
//     }
//     return temp;
// }

// template<typename S>
// matrix<S> matrix<S>::operator -(matrix const &other){
//     check_size(other._row, other._col); 
//     matrix temp = *this;    
//     for(int i = 0; i < _row; i++){
//         for(int j = 0; j < _col; j++){
//             temp.data[i][j] = data[i][j]-other.data[i][j];
//         }
//     }
//     return temp;
// }

// template<typename S>
// matrix<S> matrix<S>::operator -(S n){
//     matrix temp = *this;
//     for(int i = 0; i < _row; i++){
//         for(int j = 0; j < _col; j++){
//             temp.data[i][j] = data[i][j]-n;
//         }
//     }
//     return temp;
// }

// template<typename S>
// matrix<S> var::operator -(S n, matrix<S> &other){
//     matrix<S> temp = -other;
//     return n+temp;
// }

// // ***************************** * operator ************************** //

// template<typename S>
// matrix<S> matrix<S>::operator *(matrix const &other){
//     // condition 
//     if(!(_row == other._col && _col == other._row)){
//         throw std::invalid_argument("Size mismatch");
//     }
//     auto SUM = [this, other](int i, int j)-> S {
//         S summ = S();
//         for(int k = 0; k < _col; k++){
//             summ += data[i][k]*other.data[k][j];
//         }
//         return summ;
//     };
//     matrix temp(_row, other._col);
//     for(int i = 0; i < _row; i++){
//         for(int j = 0; j < other._col; j++){
//             temp.data[i][j] = SUM(i, j);
//         }
//     }
//     return temp;
// }

// template<typename S>
// matrix<S> matrix<S>::operator *(S n){
//     matrix temp = *this;
//     for(int i = 0; i < _row; i++){
//         for(int j = 0; j < _col; j++){
//             temp.data[i][j] = data[i][j]*n;
//         }
//     }
//     return temp;
// }

// template<typename S>
// matrix<S> var::operator *(S n, matrix<S> &other){
//     return other*n;
// }

// // ***************************** / operator ************************** //
// template<typename S>
// matrix<S> matrix<S>::operator /(matrix &other){
//     return *this*other.inv();
// }

// template<typename S>
// matrix<S> matrix<S>::operator /(S n){
//     matrix temp(_row, _col);
//     temp.data = data;
    
//     for(int i = 0; i < _row; i++){
//         for(int j = 0; j < _col; j++){
//             temp.data[i][j] = data[i][j]/n;
//         }
//     }
//     return temp;
// }

// template <typename S> 
// matrix<S> var::operator /(S n, matrix<S> &other){
//     matrix<S> temp = other;
//     for(int i = 0; i < other._row; i++){
//         for(int j = 0; j < other._col; j++){
//             temp.data[i][j] = n/temp.data[i][j];
//         }
//     }
//     return temp;
// }

// // ***************************** ^ operator ************************** //

// // ***************************** % operator ************************** //

// // ***************************** ~ operator ************************** //


// // *********************** conditional operators ******************** //
// template<typename S>
// bool  matrix<S>::operator==(matrix other){
//     check_size(other._row, other._col); 

//     for(int i = 0; i < _row; i++){
//         for(int j = 0; j < _col; j++){
//             if(other.data[i][j] != data[i][j]){
//                 return false;
//             }
//         }
//     }
//     return true;
// }

// template<typename S>
// bool  matrix<S>::operator<(matrix other){
//     if(other._col != _col || other._row != _row){
//         return false;
//     }
//     for(int i = 0; i < _row; i++){
//         for(int j = 0; j < _col; j++){
//             if(data[i][j] >= other.data[i][j]){
//                 return false;
//             }
//         }
//     }
//     return true;
// }

// template<typename S>
// bool  matrix<S>::operator>(matrix other){
//     return !(*this < other);
// }

// template<typename S>
// bool  matrix<S>::operator<=(matrix other){
//     check_size(other._row, other._col); 
//     for(int i = 0; i < _row; i++){
//         for(int j = 0; j < _col; j++){
//             if(data[i][j] > other.data[i][j]){
//                 return false;
//             }
//         }
//     }
//     return true;
// }

// template<typename S>
// bool  matrix<S>::operator>=(matrix other){
//     return !(*this <= other);
// }        

// template<typename S>
// bool  matrix<S>::operator!=(matrix other){
//     return !(*this == other);
// }

// // ************************* stream operator ************************ //

// template<typename S>
// std::ostream& var::operator << (std::ostream& out, matrix<S> const &other){
//     for(int i = 0; i < other._row; i++){
//         for(int j = 0; j < other._col; j++){
//             out << other.data[i][j] << ",";
//         }
//         out << "\n";
//     }
//     return out;
// }

// template class matrix<int>;
// template matrix<int> var::operator+ (int n, matrix<int> &other);
// template matrix<int> var::operator* (int n, matrix<int> &other);
// template matrix<int> var::operator/ (int n, matrix<int> &other);
// template matrix<int> var::operator- (int n, matrix<int> &other);
// // std::ostream& var::operator<< <int>(int n, matrix<int> &other);

// template class matrix<double>;
// template matrix<double> var::operator+ (double n, matrix<double> &other);
// template matrix<double> var::operator* (double n, matrix<double> &other);
// template matrix<double> var::operator/ (double n, matrix<double> &other);
// template matrix<double> var::operator- (double n, matrix<double> &other);
// // template std::ostream& var::operator<< (double n, matrix<double> &other);

// template class matrix<float>;
// template matrix<float> var::operator+ (float n, matrix<float> &other);
// template matrix<float> var::operator* (float n, matrix<float> &other);
// template matrix<float> var::operator/ (float n, matrix<float> &other);
// template matrix<float> var::operator- (float n, matrix<float> &other);
// // template std::ostream& var::operator<< (float n, matrix<float> &other);