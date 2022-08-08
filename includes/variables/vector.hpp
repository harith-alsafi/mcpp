/**
 * @file vector.hpp
 * @author Harith Al-Safi (harith.alsafi@gmail.com)
 * @brief Extends upon std::vector
 * @version 1.0
 * @date 17/07/2022
 *
 * @copyright Copyright (c) 2022
 *
 */
#pragma once
#include <iostream>
#include <sstream>
#include <vector>

// ********************** multiply ****************************
/**
 * @brief vector*vector
 *
 * @tparam D
 * @param first
 * @param second
 * @return std::vector<D>
 */
template <typename D>
std::vector<D> operator*(std::vector<D> first, std::vector<D> second)
{
	if(first.size() != second.size()) {
		throw std::invalid_argument("std::vector::operator * -> Invalid size");
	}
	std::vector<D> temp;
	for(int i = 0; i < first.size(); i++) {
		temp.push_back(first[i] * second[i]);
	}
	return temp;
}

/**
 * @brief var*vector
 *
 * @tparam D
 * @param s
 * @param v
 * @return std::vector<D>
 */
template <typename D>
std::vector<D> operator*(D s, std::vector<D> v)
{
	std::vector<D> temp;
	for(int i = 0; i < v.size(); i++) {
		temp.push_back(s * v[i]);
	}
	return temp;
}

/**
 * @brief vector*var
 *
 * @tparam D
 * @param v
 * @param s
 * @return std::vector<D>
 */
template <typename D>
std::vector<D> operator*(std::vector<D> v, D s)
{
	std::vector<D> temp;
	for(int i = 0; i < v.size(); i++) {
		temp.push_back(v[i] * s);
	}
	return temp;
}

// ********************** add ****************************

/**
 * @brief vector+vector
 *
 * @tparam D
 * @param first
 * @param second
 * @return std::vector<D>
 */
template <typename D>
std::vector<D> operator+(std::vector<D> first, std::vector<D> second)
{
	if(first.size() != second.size()) {
		throw std::invalid_argument("std::vector::operator + -> Invalid size");
	}
	std::vector<D> temp;
	for(int i = 0; i < first.size(); i++) {
		temp.push_back(first[i] + second[i]);
	}
	return temp;
}

/**
 * @brief var+vector
 *
 * @tparam D
 * @param s
 * @param v
 * @return std::vector<D>
 */
template <typename D>
std::vector<D> operator+(D s, std::vector<D> v)
{
	std::vector<D> temp;
	for(int i = 0; i < v.size(); i++) {
		temp.push_back(s + v[i]);
	}
	return temp;
}

/**
 * @brief vector+var
 *
 * @tparam D
 * @param v
 * @param s
 * @return std::vector<D>
 */
template <typename D>
std::vector<D> operator+(std::vector<D> v, D s)
{
	std::vector<D> temp;
	for(int i = 0; i < v.size(); i++) {
		temp.push_back(v[i] + s);
	}
	return temp;
}

// ********************** subtract ****************************

/**
 * @brief vector-vector
 *
 * @tparam D
 * @param first
 * @param second
 * @return std::vector<D>
 */
template <typename D>
std::vector<D> operator-(std::vector<D> first, std::vector<D> second)
{
	if(first.size() != second.size()) {
		throw std::invalid_argument("std::vector::operator - -> Invalid size");
	}
	std::vector<D> temp;
	for(int i = 0; i < first.size(); i++) {
		temp.push_back(first[i] - second[i]);
	}
	return temp;
}

/**
 * @brief var-vector
 *
 * @tparam D
 * @param s
 * @param v
 * @return std::vector<D>
 */
template <typename D>
std::vector<D> operator-(D s, std::vector<D> v)
{
	std::vector<D> temp;
	for(int i = 0; i < v.size(); i++) {
		temp.push_back(s - v[i]);
	}
	return temp;
}

/**
 * @brief vector-var
 *
 * @tparam D
 * @param v
 * @param s
 * @return std::vector<D>
 */
template <typename D>
std::vector<D> operator-(std::vector<D> v, D s)
{
	std::vector<D> temp;
	for(int i = 0; i < v.size(); i++) {
		temp.push_back(v[i] - s);
	}
	return temp;
}

// ********************** divide ****************************

/**
 * @brief vector/vector
 *
 * @tparam D
 * @param first
 * @param second
 * @return std::vector<D>
 */
template <typename D>
std::vector<D> operator/(std::vector<D> first, std::vector<D> second)
{
	if(first.size() != second.size()) {
		throw std::invalid_argument("std::vector::operator / -> Invalid size");
	}
	std::vector<D> temp;
	for(int i = 0; i < first.size(); i++) {
		temp.push_back(first[i] / second[i]);
	}
	return temp;
}

/**
 * @brief var/vector
 *
 * @tparam D
 * @param s
 * @param v
 * @return std::vector<D>
 */
template <typename D>
std::vector<D> operator/(D s, std::vector<D> v)
{
	std::vector<D> temp;
	for(int i = 0; i < v.size(); i++) {
		temp.push_back(s / v[i]);
	}
	return temp;
}

/**
 * @brief vector/var
 *
 * @tparam D
 * @param v
 * @param s
 * @return std::vector<D>
 */
template <typename D>
std::vector<D> operator/(std::vector<D> v, D s)
{
	std::vector<D> temp;
	for(int i = 0; i < v.size(); i++) {
		temp.push_back(v[i] / s);
	}
	return temp;
}

// ********************** streams ****************************

/**
 * @brief cout << vector
 *
 * @tparam D
 * @param out
 * @param other
 * @return std::ostream&
 */
template <typename D>
std::ostream &operator<<(std::ostream &out, std::vector<D> &other)
{
	for(int i = 0; i < other.size(); i++) {
		out << other[i];
		if(other[i] != other[other.size() - 1]) {
			out << ",";
		}
	}
	return out;
}

/**
 * @brief input operator
 *
 * @tparam D
 * @param input
 * @param other
 * @return std::istream&
 */
template <typename D>
std::istream &operator>>(std::istream &input, std::vector<D> &other)
{
	std::string line;
	getline(input, line);

	std::stringstream LINE;
	LINE << line;

	std::string temp;
	D var;
	while(LINE.good()) {
		getline(LINE, temp, ',');
		if(std::stringstream(temp) >> var) {
			other.push_back(var);
		}
	}
	return input;
}

// ********************** others operators ****************************

template <typename D>
std::vector<D> operator%(std::vector<D> v, D s)
{
	std::vector<D> temp;
	for(int i = 0; i < v.size(); i++) {
		temp.push_back(v[i] % s);
	}
	return temp;
}

// *********************** comparison ********************************
// TODOconditional operators

/**
 * @brief equal operator
 *
 * @tparam D
 * @param a
 * @param b
 * @return true
 * @return false
 */
template <typename D>
bool operator==(std::vector<D> a, std::vector<D> b)
{
	if(a.size() != b.size()) {
		throw std::invalid_argument("std::vector::operator == -> Invalid size");
	}
	for(int i = 0; i < a.size(); i++) {
		if(a[i] != b[i]) {
			return false;
		}
	}
	return true;
}