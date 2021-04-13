#pragma once
#include "../misc/constants.hpp"
#include <vector>
#include <iostream>

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
std::ostream& operator << (std::ostream& out, std::vector<S> &other){
    for(auto const &i: other){
        out << i;
    }
    return out;
}