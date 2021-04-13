#include "../../includes/mcpp.hpp"
#include <algorithm>

template<typename S>
std::ostream& var::operator << (std::ostream& out, var::matrix<S> &other){
    out << "row: " << other.row() << "\t" << "col: " << other.col() << "\n";
    for(int i = 0; i < other.row(); i++){
        for(int j = 0; j < other.col(); j++){
            out << other[i][j] << " ";
        }
        out << "\n";
    }
    return out;
}

template<typename S>
var::matrix<S>::matrix(int r, int c){
    resize(r, c);
}

template<typename S>
var::matrix<S>::matrix(): _row(0), _col(0){}

template<typename S>
var::matrix<S>::matrix (std::initializer_list<std::initializer_list<S>> a){ 
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

template<typename S>
void var::matrix<S>::resize(int r, int c){
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

template<typename S>
int var::matrix<S>::row(){
    return _row;
}

template<typename S>
int var::matrix<S>::col(){
    return _col;
}

template<typename S>
int var::matrix<S>::size(){
    return _col*_row;
}

template<typename S>
void var::matrix<S>::insert_row(const std::vector<S>& a){
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

template<typename S>
void var::matrix<S>::insert_col(const std::vector<S>& a){
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

template<typename S>
void var::matrix<S>::insert_row(int i, const std::vector<S>& a){
    if(a.size() != _col){
        throw std::invalid_argument("Size doesnt match");
    }
    data.insert(i, a);
    _row = data.size();

}

template<typename S>
void var::matrix<S>::insert_col(int j, const std::vector<S>& a){
    // checking size
    if(a.size() != _row){
        throw std::invalid_argument("Size doesnt match");
    }
    for(int i = 0; i < _row; i++){
        data[i].insert(j, a[i]);
    }
    _col = data[0].size(); // since all colums have same size
}

template<typename S>
void var::matrix<S>::T(){
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

template<typename S>
void var::matrix<S>::sort_rows(int d){
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

template<typename S>
void var::matrix<S>::sort_cols(int d){
    T(); // transpose
    sort_rows(d); // sort transposed
    T(); // transpose bacl
}

template<typename S>
void var::matrix<S>::sort_row_at(int i, int d){

}

template<typename S>
void var::matrix<S>::sort_col_at(int j, int d){

}

template<typename S>
template<typename LAMBDA> 
void var::matrix<S>::row_op(int i, LAMBDA f){

}

template<typename S>
template<typename LAMBDA> 
void var::matrix<S>::col_op(int j, LAMBDA f){
    
}

template<typename S>
void var::matrix<S>::turn_to(S n){
    for(int i = 0; i < _row; i++){
        for(int j = 0; j<_col; j++){
            data[i][j] = n;
        }
    }
}

template<typename S>
S var::matrix<S>::sum(){
    S SUM;
    for(int i = 0; i < _row; i++){
        for(int j = 0; j < _col; j++){
            SUM += data[i][j];
        }
    }
    return SUM;
}


template<typename S>
var::matrix<S>::Row::Row(var::matrix<S>& a, int i): _a(a), _i(i){}

template<typename S>
S& var::matrix<S>::Row::operator[](int j){
    return _a.data[_i][j];
}


template<typename S>
typename var::matrix<S>::Row var::matrix<S>::operator [](int i){
    return var::matrix<S>::Row(*this, i);
}

template<typename S>
var::matrix<S> var::matrix<S>::operator +(var::matrix<S> const &other){
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

template<typename S>
var::matrix<S> var::matrix<S>::operator -(var::matrix<S> const &other){
    if(other._col != _col || other._row != _row){
        throw std::invalid_argument("Size mismatch");
    }

}

template<typename S>
var::matrix<S> var::matrix<S>::operator *(var::matrix<S> const &other){

}

template<typename S>
var::matrix<S> var::matrix<S>::operator /(var::matrix<S> const &other){

}

template<typename S>
S var::matrix<S>::det(){

}

template<typename S>
S var::matrix<S>::inv(){

}

template<typename S>
bool var::matrix<S>::is_square(){
    return _row == _col;
}

template<typename S>
bool var::matrix<S>::is_identity(){
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