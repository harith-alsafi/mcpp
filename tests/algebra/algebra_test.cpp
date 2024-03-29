#include "../../includes/mcpp.hpp"
#include "../../lib/googletest/googletest/include/gtest/gtest.h"

TEST(solvers, bisection)
{
	auto f = [](double x) -> double {
		return pow(x, 2) * 2.0 + 3.0 * x;
	};
	ASSERT_EQ(mth::decimals(2.000), 1);
	ASSERT_EQ(mth::decimals(2.121), 3);
	ASSERT_EQ(mth::decimals(0.001), 3);
	
	ASSERT_DOUBLE_EQ(mth::round(2.005, 2), 2.01);
	ASSERT_DOUBLE_EQ(mth::round(0.000005, 5), 0.00001);

	auto ans = alg::bisection_root<double>(f, -2.0, -0.5);

	ASSERT_DOUBLE_EQ(ans, -1.5);

	auto ans2 = alg::bisection_root<double>(f, -0.5, 1);

	ASSERT_TRUE(round(ans2) == 0.0);
}

TEST(solvers, sim)
{
	var::matrix<double> A = {
		{ 1, 1, 1, 1 },
		{ 4, 3, -1, 6 },
		{ 3, 5, 3, 4 }
	};
	auto sol                = alg::linear_sim(A);
	std::vector<double> ans = { 1, 0.5, -0.5 };
	ASSERT_TRUE(ans == sol);
}

int main(int argc, char **argv)
{
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}