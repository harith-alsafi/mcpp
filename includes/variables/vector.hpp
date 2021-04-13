#pragma once
#include "../misc/constants.hpp"
#include <vector>
#include <iostream>

template<typename S>
std::vector<S> operator *(std::vector<S>& first, std::vector<S> &second);

template<typename S>
std::vector<S> operator +(std::vector<S>& first, std::vector<S> &second);

template<typename S>
std::vector<S> operator -(std::vector<S>& first, std::vector<S> &second);

template<typename S>
std::vector<S> operator /(std::vector<S>& first, std::vector<S> &second);

template<typename S>
std::ostream& operator << (std::ostream& out, std::vector<S> &other);