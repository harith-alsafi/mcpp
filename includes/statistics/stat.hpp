/**
 * @file statistics.hpp
 * @author Harith Al-Safi (harith.alsafi@gmail.com)
 * @brief Containst statistics
 * @version 1.0
 * @date 08/08/2022
 *
 * @copyright Copyright (c) 2022
 *
 */
#pragma once

#include "../mathematic/mathematic.hpp"
#include "../numerical/vect.hpp"
#include "../variables/others.hpp"
#include "../variables/vecop.hpp"

/**
 * @brief Statistical functions
 *
 * Short for STATiStics
 *
 */
namespace stats
{

	/**
	 * @brief Get the avgerage of vector
	 *
	 * @tparam D: Type
	 * @param a: input vector
	 * @return D: output average
	 */
	template <typename D>
	D get_avg(std::vector<D> a)
	{
		return vect::sum(a) / D(a.size());
	}

	/**
	 * @brief Get the variance object
	 *
	 * @tparam D: Type
	 * @param a: input vector
	 * @return D: output variance
	 */
	template <typename D>
	D get_var(std::vector<D> a)
	{
		D mean = get_avg(a);
		int N  = (int) a.size();
		D sum  = D(0);
		for(int i = 0; i < N; i++) {
			sum += D(std::pow((a[i] - mean), D(2)));
		}
		return (D) sum / N;
	}

	/**
	 * @brief Get the standard diviation of vector
	 *
	 *
	 * @tparam D: Type
	 * @param a: input vector
	 * @return D: output standard diviation
	 */
	template <typename D>
	D get_std(std::vector<D> a)
	{
		return D(std::sqrt(get_var(a)));
	}

	/**
	 * @brief Get the quartile range of a vector
	 *
	 * @param a: input vector
	 * @return `QR`: the quartile range
	 */
	template <typename D>
	var::QR<D> get_qr(std::vector<D> a)
	{
		var::QR<D> qr;
		qr.LQ = vect::min(a);
		qr.UQ = vect::max(a);

		std::vector<D> a_sorted = a;
		std::sort(a_sorted.begin(), a_sorted.end());

		qr.Q1 = a_sorted.at(D(a_sorted.size()) / D(4));
		qr.Q2 = a_sorted.at(D(a_sorted.size()) / D(2));
		qr.Q3 = a_sorted.at(D(D(3) * (a_sorted.size())) / D(4));
		return qr;
	}

	/**
	 * @brief Get the corelation coefficient of two vectors
	 *
	 * @param x: x vector
	 * @param y: y vector
	 * @return D: corelation coefficient 
	 */
	template <typename D>
	D get_r(std::vector<D> x, std::vector<D> y)
	{
		if(x.size() != y.size()) {
			throw std::invalid_argument("stats::get_r -> Size mismatch");
		}
		D sumx  = get_sum(x);
		D sumy  = get_sum(y);
		D sumxx = get_sum(x * x);
		D sumxy = get_sum(x * y);
		D sumyy = get_sum(y * y);
		return (D(x.size()) * sumxy - (sumx * sumy)) /
			   D(D(std::sqrt((D(x.size())) * sumxx - D(std::pow(sumx, D(2)))) *
				   (D(x.size()) * sumyy - D(std::pow(sumy, D(2))))));
	}
}