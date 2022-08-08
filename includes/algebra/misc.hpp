#pragma once

namespace alg
{
	namespace msc
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

	}
}

// TODO polyfit
// TODO binomial
// TODO roots