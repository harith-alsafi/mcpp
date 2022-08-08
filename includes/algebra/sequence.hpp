/**
 * @file sequence.hpp
 * @author Harith Al-Safi (harith.alsafi@gmail.com)
 * @brief Implementation and declaration of sequantial arithematics
 * @version 1.0
 * @date 17/07/2022
 *
 * @copyright Copyright (c) 2022
 *
 */
#pragma once

#include <vector>

namespace alg
{
	namespace seq
	{
		template <typename LAMBDA, typename S>
		std::vector<S> sequence(LAMBDA f, int start, int stop)
		{
			auto sum = f(start);
			for(int i = start + 1; i <= stop; i++) {
				sum += f(i);
			}
			return sum;
		}

		template <typename LAMBDA>
		auto sum(LAMBDA f, int start, int stop)
		{
			auto sum = f(start);
			for(int i = start + 1; i <= stop; i++) {
				sum += f(i);
			}
			return sum;
		}
	}

}