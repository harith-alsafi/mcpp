

#include "../../includes/mcpp.hpp"
#include "../../lib/googletest/googletest/include/gtest/gtest.h"

using namespace var;
using namespace stats;

TEST(stats, qr)
{
	// to string
	auto qr = get_qr<long double>(
		{ 5.0, 8.2, 10.3, 10.3, 15.2, 18.2, 23.1 }
	);
	var::QR<long double> qr_answer = { 5.0, 8.2, 10.3, 18.2, 23.1 };
	ASSERT_TRUE(qr_answer.LQ == qr.LQ);
	ASSERT_TRUE(qr_answer.Q1 == qr.Q1);
	ASSERT_TRUE(qr_answer.Q2 == qr.Q2);
	ASSERT_TRUE(qr_answer.Q3 == qr.Q3);
	ASSERT_TRUE(qr_answer.UQ == qr.UQ);
}

TEST(stats, std_var)
{
	std::vector<long double> a = { 10.0, 8.0, 10.0, 8.0, 8.0, 4.0 };
	ASSERT_DOUBLE_EQ(get_std(a), 2.0);
}

int main(int argc, char **argv)
{
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}