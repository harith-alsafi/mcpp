/**
 * @file others.hpp
 * @author Harith Al-Safi (harith.alsafi@gmail.com)
 * @brief Contains other data structures 
 * @version 1.0
 * @date 14/08/2022
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#pragma once

namespace var
{
	/**
	 * @brief Struct to contain the quartile range
	 *
	 */
	template <typename D>
	struct QR
	{
		D LQ; ///< Lower quartile
		D Q1; ///< Q1 (25%)
		D Q2; ///< Q2 (50%)
		D Q3; ///< Q3 (75%)
		D UQ; ///< Upper quartile
	};
}