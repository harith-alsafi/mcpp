#include "../../lib/googletest/googletest/include/gtest/gtest.h"
#include "../../includes/variables/table.hpp"

using namespace var;

TEST(var, table_read_csv)
{
	table<long double> t;
	ASSERT_TRUE(t.read_csv("homes.csv"));
	ASSERT_TRUE(t.save_csv("test.csv"));
}

TEST(var, table_header)
{
	table<long double> t;
	t.read_csv("homes.csv");
	std::vector<long double> sold = t["Sell"];
	ASSERT_TRUE(t.size() == sold.size());
	for(int i = 0; i < sold.size(); i++){
		ASSERT_TRUE(t.at(i).at(0) == sold[i]);
	}
}

TEST(var, table_qr_sort_asc)
{
	// to string 
	auto qr = table<long double>::get_qr(
		{5.0, 8.2, 10.3, 10.3, 15.2, 18.2, 23.1});
	table<long double>::QR qr_answer = {5.0, 8.2, 10.3, 18.2, 23.1};
	ASSERT_TRUE(qr_answer.LQ == qr.LQ);
	ASSERT_TRUE(qr_answer.Q1 == qr.Q1);
	ASSERT_TRUE(qr_answer.Q2 == qr.Q2);
	ASSERT_TRUE(qr_answer.Q3 == qr.Q3);
	ASSERT_TRUE(qr_answer.UQ == qr.UQ);
}

TEST(var, table_mean_std_var_sum)
{
	std::vector<long double> a = {10.0, 8.0, 10.0, 8.0, 8.0, 4.0};  
	ASSERT_DOUBLE_EQ(table<long double>::get_std(a), 2.0);
}

TEST(var, table_describe_all)
{
	table<long double> t;
	t.read_csv("homes.csv");
	auto t2 = t.describe_all();
	t2.show();
}


TEST(var, table_show_row)
{
	table<long double> t;
	t.read_csv("homes.csv");
	auto tt = t.get_row(2);
	tt.show();
}

TEST(var, table_show_col)
{
	table<long double> t;
	t.read_csv("homes.csv");
	auto tt = t.get_col("Sell");
	tt.show();
}

TEST(var, table_add_col)
{
	table<long double> t;
	t.add_col("x1", {1, 2, 3, 4});
	t.add_col("x2", {5, 6, 7, 8});
	t.add_col("x3", {9, 10, 11, 12});
	t.show();

}

int main(int argc, char **argv) 
{
   testing::InitGoogleTest(&argc, argv);
   return RUN_ALL_TESTS();
}