/**
 * @file mathematic.hpp
 * @author Harith Al-Safi (harith.alsafi@gmail.com)
 * @brief General math functionality
 * @version 1.0
 * @date 17/07/2022
 *
 * @copyright Copyright (c) 2022
 *
 */
#pragma once
#include <algorithm>
#include <cmath>
#include <complex>
#include <fstream>
#include <iostream>
#include <limits>
#include <numeric>
#include <sstream>
#include <stdexcept>
#include <vector>

/**
 * @brief Generic mathematical functions
 * 
 * Short for MaTHematics
 *
 */
namespace mth
{

	/**
	 * @brief Factorial
	 *
	 * @param n
	 * @return int
	 */
	int factorial(int n)
	{
		int sum = 1;
		for(int i = n; i > 0; i--) {
			sum = sum * i;
		}
		return sum;
	}

	/**
	 * @brief Combination (Cr)
	 *
	 * @param n
	 * @param k
	 * @return int
	 */
	int combination(int n, int k)
	{
		return factorial(n) / (factorial(k) * factorial(n - k));
	}

	/**
	 * @brief Gets number of decimal places
	 *
	 * @tparam D
	 * @param a
	 * @return int
	 */
	template <typename D>
	int decimals(D a)
	{
		std::string s;
		std::string t;
		std::stringstream out;
		out << a;
		s = out.str();
		t = s.substr(s.find(".") + 1);
		return t.length();
	}

	template <typename D>
	D round(D a)
	{
		static_assert(std::is_floating_point<D>::value, "mth::round -> input must be floating point");
		return (a > 0) ? ::floor(a + static_cast<D>(0.5)) : ::ceil(a - static_cast<D>(0.5));
	}

	/**
	 * @brief overriding default round
	 *
	 * @tparam D
	 * @param a
	 * @param dp
	 * @return D
	 */
	template <typename D>
	D round(D a, int dp)
	{
		if(dp == 0){
			return mth::round(a);
		}
    	const D shift = pow(static_cast<D>(10.0), dp);
    	return mth::round(a * shift) / shift;
	}
}