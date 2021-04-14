#pragma once
#include "../misc/constants.hpp"
#include <vector>
#include <iostream>

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
std::vector<S> operator *(std::vector<S>& first, std::vector<S> &second){
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
std::vector<S> operator *(S s, std::vector<S> &v){
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
std::vector<S> operator *(std::vector<S> &v, S s){
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
std::vector<S> operator +(std::vector<S>& first, std::vector<S> &second){
    if(first.size() != second.size()){
        throw std::invalid_argument("Invalid size");
    }
    std::vector<S> temp;
    for(int i = 0; i < first.size(); i++){
        temp.push_back(first[i]+second[i]);
    }
    return temp;
}

template<typename S>
std::vector<S> operator +(S s, std::vector<S> &v){
    std::vector<S> temp;
    for(int i = 0; i < v.size(); i++){
        temp.push_back(s+v[i]);
    }
    return temp;
}

template<typename S>
std::vector<S> operator +(std::vector<S> &v, S s){
    std::vector<S> temp;
    for(int i = 0; i < v.size(); i++){
        temp.push_back(v[i]+s);
    }
    return temp;
}

// ********************** subtract ****************************

template<typename S>
std::vector<S> operator -(std::vector<S>& first, std::vector<S> &second){
    if(first.size() != second.size()){
        throw std::invalid_argument("Invalid size");
    }
    std::vector<S> temp;
    for(int i = 0; i < first.size(); i++){
        temp.push_back(first[i]-second[i]);
    }
    return temp;
}

template<typename S>
std::vector<S> operator -(S s, std::vector<S> &v){
    std::vector<S> temp;
    for(int i = 0; i < v.size(); i++){
        temp.push_back(s-v[i]);
    }
    return temp;
}

template<typename S>
std::vector<S> operator -(std::vector<S> &v, S s){
    std::vector<S> temp;
    for(int i = 0; i < v.size(); i++){
        temp.push_back(v[i]-s);
    }
    return temp;
}

// ********************** divide ****************************

template<typename S>
std::vector<S> operator /(std::vector<S>& first, std::vector<S> &second){
    if(first.size() != second.size()){
        throw std::invalid_argument("Invalid size");
    }
    std::vector<S> temp;
    for(int i = 0; i < first.size(); i++){
        temp.push_back(first[i]/second[i]);
    }
    return temp;
}

template<typename S>
std::vector<S> operator /(S s, std::vector<S> &v){
    std::vector<S> temp;
    for(int i = 0; i < v.size(); i++){
        temp.push_back(s/v[i]);
    }
    return temp;
}

template<typename S>
std::vector<S> operator /(std::vector<S> &v, S s){
    std::vector<S> temp;
    for(int i = 0; i < v.size(); i++){
        temp.push_back(v[i]/s);
    }
    return temp;
}

// ********************** streams ****************************

template<typename S>
std::ostream& operator << (std::ostream& out, std::vector<S> &other){
    for(auto const &i: other){
        out << i;
    }
    return out;
}

// ********************** others ****************************

template<typename S>
std::vector<S> dot(std::vector<S> a, std::vector<S> b){
    if(a.size() != b.size()){
        throw std::invalid_argument("Invalid size");
    }
}

template<typename S>
std::vector<S> cross(std::vector<S> a, std::vector<S> b){
    if(a.size() != b.size()){
        throw std::invalid_argument("Invalid size");
    } 
}