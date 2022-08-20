#include "../../includes/variables/table.hpp"
#include "../../lib/googletest/googletest/include/gtest/gtest.h"

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
	for(int i = 0; i < sold.size(); i++) {
		ASSERT_TRUE(t.at(i).at(0) == sold[i]);
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
	t.add_col({ 1, 2, 3, 4 }, "x1");
	t.add_col({ 5, 6, 7, 8 }, "x2");
	t.add_col({ 9, 10, 11, 12 }, "x3");
	t.show();
}

int main(int argc, char **argv)
{
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}