#include "../../includes/mcpp.hpp"
#include "../../lib/googletest/googletest/include/gtest/gtest.h"
#include <vector>

using namespace var;

TEST(table, constructors)
{
	// declaration -1
	table<int> m1(2, 5);
	ASSERT_EQ(2, m1.row());
	ASSERT_EQ(5, m1.col());
	ASSERT_EQ(5 * 2, m1.size());

	// declaration -2
	table<int> m2 = { { 1, 2 }, { 3, 4 } };
	std::vector<std::vector<int>> v = { { 1, 2 }, { 3, 4 } };

	for(int i = 0; i < m2.row(); i++){
		for(int j = 0; j < m2.col(); j++){
			ASSERT_EQ(v[i][j], m2.at(i, j));
		}
	}

	std::vector<int> _row = {1, 2};
	std::vector<int> _col = {1, 3};
	ASSERT_TRUE(_row == m2.get_row(0));
	ASSERT_TRUE(_col == m2.get_col(0));


	// declaration -3
	table<int> m3;
	ASSERT_EQ(0, m3.row());
	ASSERT_EQ(0, m3.col());
}

TEST(table, col_data)
{
	table<int> t;

	std::vector<int> a = {0, 1, 2};
	t.insert_col(a, 0);

	ASSERT_EQ(a.size(), t.row());
	ASSERT_EQ(1, t.col());

	for(int i = 0; i < t.row(); i++){
		ASSERT_EQ(a[i], t.at(i, 0));
	}

	std::vector<int> b = {50, 51, 52};
	t.insert_col(b, 0);

	std::vector<int> c = {11, 12, 13};
	t.push_col(c);

	t.swap_col(0, t.col()-1);

	std::vector<std::vector<int>> v1 = { { 11, 0, 50 }, { 12, 1, 51 }, {13, 2, 52} };
	for(int i = 0; i < t.row(); i++){
		for(int j = 0; j < t.col(); j++){
			ASSERT_EQ(v1[i][j], t.at(i, j));
		}
	}

	auto t2 = t;
	std::vector<int> _col = {0, 1, 2};
	ASSERT_TRUE(_col == t.get_col(1));

	t.erase_col(t.col()-1);
	std::vector<int> d = {3, 4, 5};
	t.replace_col(t.col()-1, d);

	std::vector<std::vector<int>> v2 = { { 11, 3 }, { 12, 4 }, {13, 5} };
	for(int i = 0; i < t.row(); i++){
		for(int j = 0; j < t.col(); j++){
			ASSERT_EQ(v2[i][j], t.at(i, j));
		}
	}

	t.pop_col();
	std::vector<std::vector<int>> v3 = { { 11 }, { 12 }, {13} };
	for(int i = 0; i < t.row(); i++){
		for(int j = 0; j < t.col(); j++){
			ASSERT_EQ(v3[i][j], t.at(i, j));
		}
	}

	t.join_col(t2);
	std::vector<std::vector<int>> v4 = { { 11, 11, 0, 50 }, { 12,  12, 1, 51  }, {13, 13, 2, 52} };
	for(int i = 0; i < t.row(); i++){
		for(int j = 0; j < t.col(); j++){
			ASSERT_EQ(v4[i][j], t.at(i, j));
		}
	}
}

TEST(table, row_data)
{
	table<int> t;

	std::vector<int> a = {0, 1, 2};
	t.insert_row(a, 0);

	ASSERT_EQ(a.size(), t.col());
	ASSERT_EQ(1, t.row());

	for(int j = 0; j < t.col(); j++){
		ASSERT_EQ(a[j], t.at(0, j));
	}

	std::vector<int> b = {50, 51, 52};
	t.insert_row(b, 0);

	std::vector<int> c = {11, 12, 13};
	t.push_row(c);

	t.swap_row(0, t.row()-1);

	std::vector<std::vector<int>> v1 = { c, a, b };
	for(int i = 0; i < t.row(); i++){
		for(int j = 0; j < t.col(); j++){
			ASSERT_EQ(v1[i][j], t.at(i, j));
		}
	}

	auto t2 = t;
	ASSERT_TRUE(a == t.get_row(1));

	t.erase_row(0);
	std::vector<int> d = {3, 4, 5};
	t.replace_row(t.row()-1, d);

	std::vector<std::vector<int>> v2 = { a, d };
	for(int i = 0; i < t.row(); i++){
		for(int j = 0; j < t.col(); j++){
			ASSERT_EQ(v2[i][j], t.at(i, j));
		}
	}

	t.pop_row();
	std::vector<std::vector<int>> v3 = { a };
	for(int i = 0; i < t.row(); i++){
		for(int j = 0; j < t.col(); j++){
			ASSERT_EQ(v3[i][j], t.at(i, j));
		}
	}

	t.join_row(t2);
	std::vector<std::vector<int>> v4 = { a, c, a, b };
	for(int i = 0; i < t.row(); i++){
		for(int j = 0; j < t.col(); j++){
			ASSERT_EQ(v4[i][j], t.at(i, j));
		}
	}


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