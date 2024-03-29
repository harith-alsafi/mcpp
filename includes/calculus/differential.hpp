/**
 * @file differential.hpp
 * @author Harith Al-Safi (harith.alsafi@gmail.com)
 * @brief Differential calculus
 * @version 1.0
 * @date 17/07/2022
 *
 * @copyright Copyright (c) 2022
 *
 */
#pragma once
#include "../mcpp.hpp"
#include <cmath>
#include <vector>

/**
 * @brief Contains differential and integral calculus functions 
 * 
 * Short for CALCulus 
 * 
 */
namespace calc
{
	/**
	 * @brief Nth order derivative at a point
	 * Higher orders are more prone to inaccuracies.
	 * You can assign your dx at higher orders to avoid them
	 * Be aware that the function already approximates
	 * ``dx`` at higher orders.
	 * @tparam LAMBDA: std::function
	 * @tparam D: any floating point type (double, float ..)
	 * @param f Function
	 * @param x Point
	 * @param n Derivative order
	 * @param dx Step size
	 * @return D
	 */
	template <typename LAMBDA, typename D>
	D diff(LAMBDA f, D x, unsigned int n = 1, D dx = D(0.00001))
	{
		// BUG higher orders have high error
		D ans = D(0.0);
		if(n > 2 && x != D(0) && dx == D(0.00001)) {
			dx = x * sqrt(__DBL_EPSILON__) * 1 * pow(10, n);
		}
		for(int k = 0; k <= n; k++) {
			ans +=
				pow((-1), k) * mth::combination(n, k) * f(x + (n - D(2) * k) * dx);
		}
		return D(ans / (pow((D(2) * dx), n)));
	}

	/**
	 * @brief Derivative of 2 std::vectors. It
	 * returns  a vector of size: ``x.size()-n``
	 * @tparam D: any floating point type (double, float ..)
	 * @param x Domain vector
	 * @param y Range vector
	 * @param n Derivative order
	 * @return std::vector<D>
	 */
	template <typename D>
	std::vector<D> diff(std::vector<D> &x, std::vector<D> &y, int n = 1)
	{
		auto dx = vect::difference(x);
		auto dy = vect::difference(y);
		auto yp = dy / dx;
		auto xp = vect::averages(x);
		if(n == 1) {
			return yp;
		}
		return diff(xp, yp, n - 1);
	}

	/**
	 * @brief Derivative of function with given vector.
	 * It returns  a vector of size: ``x.size()-n``
	 * @tparam D
	 * @tparam LAMBDA
	 * @param f Function
	 * @param x Domain vector
	 * @param n Derivative order
	 * @return std::vector<D>
	 */
	template <typename D, typename LAMBDA>
	std::vector<D> diff(LAMBDA f, std::vector<D> &x, int n = 1)
	{
		auto y = vect::vec_op(f, x);
		return diff(x, y, n);
	}

	template <typename D, typename LAMBDA>
	std::vector<D> taylor(LAMBDA f, std::vector<D> &x, D x0 = D(0))
	{
	}

	template <typename D, typename LAMBDA>
	std::vector<D> eular_method(LAMBDA f, D x0, unsigned int n)
	{
	}

}

// TODO differentiation
// TODO Eular method
// TODO power series
// TODO limits
// TODO more testing on 'diff' cases