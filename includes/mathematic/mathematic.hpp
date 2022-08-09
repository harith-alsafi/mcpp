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
#include <cmath>
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

	/**
	 * @brief overriding default round
	 *
	 * @tparam D
	 * @param a
	 * @param dp
	 * @return D
	 */
	template <typename D>
	D round(D a, int dp = 0)
	{
		if(a < D(0)) {
			return D( (a * pow(10, dp) - .5) / pow(10, dp));
		}
		return D( (a * pow(10, dp) + .5) / pow(10, dp));
	}


}