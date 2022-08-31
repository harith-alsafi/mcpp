#include "../../includes/variables/table.hpp"
#include "../../lib/googletest/googletest/include/gtest/gtest.h"

using namespace var;

TEST(table,constructors)
{
	// declaration -1
	table<int> m1(2, 5);
	ASSERT_EQ(2, m1.row());
	ASSERT_EQ(5, m1.col());
	ASSERT_EQ(5 * 2, m1.row() * m1.col());

	// declaration -2
	table<int> m2 = { { 2, 3 }, { 3, 4 } };
	ASSERT_EQ(2, m2.at(0, 0));
	ASSERT_EQ(3, m2.at(0, 1));
	ASSERT_EQ(4, m2.at(1, 1));

	// declaration -3
	table<int> m3;
	ASSERT_EQ(0, m3.row());
	ASSERT_EQ(0, m3.col());
}

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
	std::vector<long double> sold = t.get_col("Sell");
	ASSERT_TRUE(t.row() == sold.size());
	for(int i = 0; i < sold.size(); i++) {
		ASSERT_TRUE(t.at(i, 0) == sold[i]);
	}
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
	auto tt = t.get_row_table(2);
	tt.show();
}

TEST(var, table_show_col)
{
	table<long double> t;
	t.read_csv("homes.csv");
	auto tt = t.get_col_table("Sell");
	tt.show();
}

TEST(var, table_add_col)
{
	table<long double> t;
	t.push_col({ 1, 2, 3, 4 }, "x1");
	t.push_col({ 5, 6, 7, 8 }, "x2");
	t.push_col({ 9, 10, 11, 12 }, "x3");
	t.show();
}

int main(int argc, char **argv)
{
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}