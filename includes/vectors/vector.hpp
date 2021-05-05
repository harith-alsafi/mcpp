#pragma once
#include <vector>
#include <iostream>
#include <sstream>
// ********************** multiply ****************************
/**
 * @brief vector*vector
 * 
 * @tparam S 
 * @param first 
 * @param second 
 * @return std::vector<S> 
 */
template<typename S>
std::vector<S> operator *(std::vector<S> first, std::vector<S> second){
    if(first.size() != second.size()){
        throw std::invalid_argument("Invalid size");
    }
    std::vector<S> temp;
    for(int i = 0; i < first.size(); i++){
        temp.push_back(first[i]*second[i]);
    }
    return temp;
}

/**
 * @brief var*vector
 * 
 * @tparam S 
 * @param s 
 * @param v 
 * @return std::vector<S> 
 */
template<typename S>
std::vector<S> operator *(S s, std::vector<S> v){
    std::vector<S> temp;
    for(int i = 0; i < v.size(); i++){
        temp.push_back(s*v[i]);
    }
    return temp;
}

/**
 * @brief vector*var
 * 
 * @tparam S 
 * @param v 
 * @param s 
 * @return std::vector<S> 
 */
template<typename S>
std::vector<S> operator *(std::vector<S> v, S s){
    std::vector<S> temp;
    for(int i = 0; i < v.size(); i++){
        temp.push_back(v[i]*s);
    }
    return temp;
}

// ********************** add ****************************

/**
 * @brief vector+vector
 * 
 * @tparam S 
 * @param first 
 * @param second 
 * @return std::vector<S> 
 */
template<typename S>
std::vector<S> operator +(std::vector<S> first, std::vector<S> second){
    if(first.size() != second.size()){
        throw std::invalid_argument("Invalid size");
    }
    std::vector<S> temp;
    for(int i = 0; i < first.size(); i++){
        temp.push_back(first[i]+second[i]);
    }
    return temp;
}

/**
 * @brief var+vector
 * 
 * @tparam S 
 * @param s 
 * @param v 
 * @return std::vector<S> 
 */
template<typename S>
std::vector<S> operator +(S s, std::vector<S> v){
    std::vector<S> temp;
    for(int i = 0; i < v.size(); i++){
        temp.push_back(s+v[i]);
    }
    return temp;
}

/**
 * @brief vector+var
 * 
 * @tparam S 
 * @param v 
 * @param s 
 * @return std::vector<S> 
 */
template<typename S>
std::vector<S> operator +(std::vector<S> v, S s){
    std::vector<S> temp;
    for(int i = 0; i < v.size(); i++){
        temp.push_back(v[i]+s);
    }
    return temp;
}

// ********************** subtract ****************************

/**
 * @brief vector-vector
 * 
 * @tparam S 
 * @param first 
 * @param second 
 * @return std::vector<S> 
 */
template<typename S>
std::vector<S> operator -(std::vector<S> first, std::vector<S> second){
    if(first.size() != second.size()){
        throw std::invalid_argument("Invalid size");
    }
    std::vector<S> temp;
    for(int i = 0; i < first.size(); i++){
        temp.push_back(first[i]-second[i]);
    }
    return temp;
}

/**
 * @brief var-vector
 * 
 * @tparam S 
 * @param s 
 * @param v 
 * @return std::vector<S> 
 */
template<typename S>
std::vector<S> operator -(S s, std::vector<S> v){
    std::vector<S> temp;
    for(int i = 0; i < v.size(); i++){
        temp.push_back(s-v[i]);
    }
    return temp;
}

/**
 * @brief vector-var
 * 
 * @tparam S 
 * @param v 
 * @param s 
 * @return std::vector<S> 
 */
template<typename S>
std::vector<S> operator -(std::vector<S> v, S s){
    std::vector<S> temp;
    for(int i = 0; i < v.size(); i++){
        temp.push_back(v[i]-s);
    }
    return temp;
}

// ********************** divide ****************************

/**
 * @brief vector/vector
 * 
 * @tparam S 
 * @param first 
 * @param second 
 * @return std::vector<S> 
 */
template<typename S>
std::vector<S> operator /(std::vector<S> first, std::vector<S> second){
    if(first.size() != second.size()){
        throw std::invalid_argument("Invalid size");
    }
    std::vector<S> temp;
    for(int i = 0; i < first.size(); i++){
        temp.push_back(first[i]/second[i]);
    }
    return temp;
}

/**
 * @brief var/vector
 * 
 * @tparam S 
 * @param s 
 * @param v 
 * @return std::vector<S> 
 */
template<typename S>
std::vector<S> operator /(S s, std::vector<S> v){
    std::vector<S> temp;
    for(int i = 0; i < v.size(); i++){
        temp.push_back(s/v[i]);
    }
    return temp;
}

/**
 * @brief vector/var
 * 
 * @tparam S 
 * @param v 
 * @param s 
 * @return std::vector<S> 
 */
template<typename S>
std::vector<S> operator /(std::vector<S> v, S s){
    std::vector<S> temp;
    for(int i = 0; i < v.size(); i++){
        temp.push_back(v[i]/s);
    }
    return temp;
}

// ********************** streams ****************************

/**
 * @brief cout << vector
 * 
 * @tparam S 
 * @param out 
 * @param other 
 * @return std::ostream& 
 */
template<typename S>
std::ostream& operator << (std::ostream& out, std::vector<S> &other){
    for(int i =0; i < other.size(); i++){
        out << other[i];
        if(other[i] != other[other.size()-1]){
            out << ",";
        }
    }
    return out;
}

/**
 * @brief input operator 
 * 
 * @tparam S 
 * @param input 
 * @param other 
 * @return std::istream& 
 */
template<typename S>
std::istream &operator >> (std::istream  &input, std::vector<S> &other){
    std::string line;
    getline(input, line);
    
    std::stringstream LINE;
    LINE << line;

    std::string temp;
    S var;
    while(LINE.good())
    {
        getline(LINE, temp, ',');
        if(std::stringstream(temp) >> var){
            other.push_back(var);
        }
    }
    return input;
}

// ********************** others operators ****************************


template<typename S>
std::vector<S> operator %(std::vector<S> v, S s){
    std::vector<S> temp;
    for(int i = 0; i < v.size(); i++){
        temp.push_back(v[i]%s);
    }
    return temp;
}



// *********************** comparison ********************************
//TODOconditional operators

/**
 * @brief equal operator
 * 
 * @tparam S 
 * @param a 
 * @param b 
 * @return true 
 * @return false 
 */
template<typename S>
bool operator ==(std::vector<S> a, std::vector<S> b){
    if(a.size() != b.size()){
        throw std::invalid_argument("Invalid size");
    }
    for(int i = 0; i < a.size(); i++){
        if(a[i] != b[i]){
            return false;
        }
    }
    return true;
}