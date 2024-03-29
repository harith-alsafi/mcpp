/**
 * @file table.hpp
 * @author Harith Al-Safi (harith.alsafi@gmail.com)
 * @brief Implementation and declaration of table.hpp
 * @version 1.0
 * @date 17/07/2022
 *
 * @copyright Copyright (c) 2022
 *
 */
#pragma once
#include "../mathematic/mathematic.hpp"
#include "../statistics/stat.hpp"
#include "others.hpp"
#include <exception>
#include <map>
#include <sstream>
#include <stdexcept>
#include <string>
#include <variant>
#include <vector>

// TODO: complete testing
// TODO: fix documentation and code

namespace var
{
	/**
	 * @brief 2D array class
	 */
	template <typename D>
	class table
	{
	  protected:
		std::vector<D> data;                  ///< Data container
		std::map<int, std::string> col_names; ///< Column names
		std::map<int, std::string> row_names; ///< Row names
		int _row;                             ///< Row size
		int _col;                             ///< Colum size
		int sz = 10;                          ///< Spacing size for print
	    inline static const std::string empty_name = "n/a";

		/**
		 * @brief Get the index (maps 1D vector to 2D vector)
		 *
		 * @param i row index
		 * @param j column index
		 * @return `int` used for `data` index <br>
		 */
		int get_index(int i, int j)
		{
			return i * _col + j;
		}

		/**
		 * @brief Returns column index of given column name
		 *
		 * @param name string of column name
		 * @return `int` $[-1]$: index not found <br>
		 * @return `int` $[\geq 0]$: index found
		 */
		int check_col_name(std::string name)
		{
			for(int j = 0; j < _col; j++) {
				if(col_names.find(j) != col_names.end()) { // if index exists
					if(col_names[j] == name) {
						return j;
					}
				}
			}
			return -1;
		}

		/**
		 * @brief Returns row index of given row name
		 *
		 * @param name string of row name
		 * @return `int` $[-1]$: index not found <br>
		 * @return `int` $[\geq 0]$: index found
		 */
		int check_row_name(std::string name)
		{
			for(int i = 0; i < (int) row_names.size(); i++) {
				if(row_names.find(i) != row_names.end()) {
					if(row_names[i] == name) {
						return i;
					}
				}
			}
			return -1;
		}

		/**
		 * @brief Re-centers a string based on given width
		 *
		 * @param s string given
		 * @param w width to center the string to
		 * @return `std::string`
		 */
		static std::string center(const std::string s, const int w)
		{
			std::stringstream ss, spaces;
			int padding = w - s.size(); // count excess room to pad
			for(int i = 0; i < padding / 2; ++i) {
				spaces << " ";
			}
			ss << spaces.str() << s << spaces.str(); // format with padding
			// if odd #, add 1 space
			if(padding > 0 && padding % 2 != 0) {
				ss << " ";
			}
			return ss.str();
		}

		/**
		 * @brief Fills the string with given width with empty space
		 *
		 * @param x string given
		 * @param width width to center the string to
		 * @return `std::string`
		 */
		static std::string prd(D x, int width)
		{
			std::stringstream ss;
			ss << std::fixed << std::left;
			ss.fill(' ');    // fill space around displayed #
			ss.width(width); // set  width around displayed #
			ss.precision(2); // set # places after decimal
			ss << x;
			return center(ss.str(), width);
		}

		/**
		 * @brief Gives spacing to a string
		 *
		 * @see Similar to @ref var::table::prd(D, int)
		 *
		 * @param x string given
		 * @param width width to center the string to
		 * @return `std::string`
		 */
		static std::string prd(std::string x, int width)
		{
			std::stringstream ss;
			ss << std::left;
			ss.fill(' ');    // fill space around displayed #
			ss.width(width); // set  width around displayed #
			ss << x;
			return center(ss.str(), width);
		}

		/**
		 * @brief Generates line to seperate rows
		 *
		 * @param l number of "―" in the generated string
		 * @return `std::string`
		 */
		std::string generate_line(int l)
		{
			std::string line;
			for(int i = 0; i < l; i++) {
				line += "―";
			}
			return line;
		}

		/**
		 * @brief Clears current column names and generates new ones
		 *
		 */
		void generate_cols()
		{
			for(int j = 0; j < _col; j++) {
				col_names[j] = "Col-" + std::to_string(j);
			}
		}

		/**
		 * @brief Clears current column names and generates new ones
		 * ## Constructors
		 */
		void generate_rows()
		{
			for(int i = 0; i < _row; i++) {
				row_names[i] = "Row-" + std::to_string(i);
			}
		}

	  public:
		/**
		 * @brief Construct a new table object
		 *
		 * * Usage:
		 * ```cpp
		 * var::table<int> t;
		 * ```
		 */
		table() :
			_row(0),
			_col(0) {}

		/**
		 * @brief Construct a new table object
		 *
		 * **Usage**:
		 * ```cpp
		 * var::table<int> t(2, 3); // 2 rows, 3 colums of all 0
		 * ```
		 * @param r number of rows
		 * @param c number of colums
		 */
		table(int r, int c)
		{
			if(r <= 0 || c <= 0) {
				throw std::invalid_argument("var::table -> can't have row or columns <= 0");
			}
			_row = r;
			_col = c;
			data = std::vector<D>(r * c);
			generate_cols();
			generate_rows();
		}

		/**
		 * @brief Construct a new table object
		 *
		 * **Usage**:
		 * ```cpp
		 *  var::table<int> m = {
		 *		{1, 2, 3},
		 *		{4, 5, 6},
		 *		{7, 8, 9}
		 *	};
		 * ```
		 *
		 * ## General getters
		 *
		 * @param a initializer list
		 */
		table(std::initializer_list<std::initializer_list<D>> a) :
			table(a.size(), a.begin()[0].size())
		{
			for(int i = 0; i < _row; i++) {
				for(int j = 0; j < _col; j++) {
					data.at(get_index(i, j)) = a.begin()[i].begin()[j];
				}
			}
		}

		// ************************* Getters ************************ //

		/**
		 * @brief Get the row size
		 *
		 * @return `int`
		 */
		int row()
		{
			return _row;
		}

		/**
		 * @brief Get the col size
		 *
		 * @return `int`
		 */
		int col()
		{
			return _col;
		}

		int size()
		{
			return _col * _row;
		}

		/**
		 * @brief Returns reference to element (i, j)
		 *
		 * ## Column getters
		 *
		 * @param i row index
		 * @param j column index
		 * @return `D&`  element <br>
		 * @throws `std::invalid_argument` if invalid indexes
		 */
		D& at(int i, int j)
		{
			if(i < 0 || i >= _row || j < 0 || j >= _col) {
				throw std::invalid_argument("var::table::at -> given index doesn't exist");
			}
			return data.at(get_index(i, j));
		}

		/**
		 * @brief Get the col names with the index that they refer to
		 * If column name was not added then you won't find the index
		 *
		 * @return `std::map<int, std::string>`  <br>
		 */
		std::map<int, std::string> get_col_names()
		{
			return col_names;
		}

		/**
		 * @brief Get the colum based on index
		 *
		 * @param j index of that colum
		 * @return `std::vector<D>`  <br>
		 * @throws `std::invalid_argument` in case \ref index is invalid
		 */
		std::vector<D> get_col(int j)
		{
			if(j < 0 || j >= _col) {
				throw std::invalid_argument("var::table::get_col -> given column index doesn't exist");
			}
			std::vector<D> a;
			for(int i = 0; i < _row; i++) {
				a.push_back(this->at(i, j));
			}
			return a;
		}

		/**
		 * @brief Get the column vector based on header name
		 *
		 * ## Row getters
		 * @param name name of the column
		 * @return `std::vector<D>`
		 * @throws `std::invalid_argument` in case \ref name is invalid
		 */
		std::vector<D> get_col(std::string name)
		{
			return get_col(check_col_name(name));
		}

		/**
		 * @brief Get the col as `table`
		 *
		 * @param j index ofo that column
		 * @return `table`
		 * @throws `std::invalid_argument` in case \ref index is invalid
		 */
		table get_col_table(int j)
		{
			table t;
			if(j < 0 || j >= _col) {
				throw std::invalid_argument("var::table::get_col_table -> given column index doesn't exist");
			}
			for(int i = 0; i < _row; i++) {
				t.push_row({ this->at(i, j) }, row_names[i]);
			}
			t.col_names[j] = col_names[j];
			return t;
		}

		/**
		 * @brief Get the col as `table`
		 *
		 * @param name column name
		 * @return `table`
		 * @throws `std::invalid_argument` in case \ref name is invalid
		 */
		table get_col_table(std::string name)
		{
			return get_col_table(check_col_name(name));
		}

		/**
		 * @brief Get the row names
		 *
		 * @return `std::map<int, std::string> `  <br>
		 */
		std::map<int, std::string> get_row_names()
		{
			return row_names;
		}

		/**
		 * @brief Get the row based on index
		 *
		 * @param i index of that row
		 * @return `std::vector<&D>`  <br>
		 * @throws `std::invalid_argument` in case \ref index is invalid
		 */
		std::vector<D> get_row(int i)
		{
			if(i < 0 || i >= _row) {
				throw std::invalid_argument("var::table::get_row -> given row index doesn't exist");
			}
			std::vector<D> a;
			for(int j = 0; j < _col; j++) {
				a.push_back(this->at(i, j));
			}
			return a;
		}

		/**
		 * @brief Get the row vector based on header name
		 *
		 *
		 * @param name name of the row
		 * @return `std::vector<D>`: Empty if nothing exits <br>
		 * @throws `std::invalid_argument` in case \ref name is invalid
		 */
		std::vector<D> get_row(std::string name)
		{
			return get_row(check_row_name(name));
		}

		/**
		 * @brief Get the row as table
		 *
		 * @param i
		 * @return table
		 * @throws `std::invalid_argument` in case \ref index is invalid
		 */
		table get_row_table(int i)
		{
			table t;
			if(i < 0 || i >= _row) {
				throw std::invalid_argument("var::table::get_row_table -> given column index doesn't exist");
			}
			for(int j = 0; j < _col; j++) {
				t.push_col({ this->at(i, j) }, col_names.at(j));
			}
			t.row_names[i] = row_names[i];
			return t;
		}

		/**
		 * @brief Get the row as table
		 *
		 *  ## Column setters
		 *
		 * @param name
		 * @return table
		 * @throws `std::invalid_argument` in case \ref name is invalid
		 */
		table get_row_table(std::string name)
		{
			return get_row_table(check_row_name(name));
		}

		// ************************* Setters ************************ //

		/**
		 * @brief Set the col names
		 *
		 * @param names `vector` of column names
		 * @throws `std::invalid_argument` size of `vector` names doesnt match column size
		 */
		void set_col_names(std::vector<std::string> names)
		{
			if(names.size() != _col) {
				throw std::invalid_argument("table::set_col_names -> Input parameter size doesn't match curret column size");
			}
			for(int j = 0; j < _col; j++) {
				set_col_name(j, names[j]);
			}
		}

		/**
		 * @brief Set the col name
		 * Doesn't set empty names (no exception) 
		 * @param j index of column
		 * @param name name of column
		 * @throws `std::invalid_argument` invalid index `j`
		 */
		void set_col_name(int j, std::string name)
		{
			if(j < 0 || j >= _col) {
				throw std::invalid_argument("var::table::set_col_name -> given column index doesn't exist");
			}
			if(!name.empty()){
				col_names[j] = name;
			}
		}

		/**
		 * @brief Inserts new column into given index
		 * Doesn't set empty names (no exception)
		 * @param a column to be inserted
		 * @param j column index to insert at
		 * @param name `default("n/a")` name of the column
		 * @throws `std::invalid_argument` invalid column index
		 * @throws `std::invalid_argument` `a.size()` $\neq$ row size
		 */
		void insert_col(std::vector<D> a, int j, std::string name = empty_name)
		{
			if(j < 0 || j > _col) {
				throw std::invalid_argument("var::table::insert_col -> invalid column index");
			}
			if(_row != 0 && a.size() != _row) {
				throw std::invalid_argument("var::table::insert_col -> invalid given column size (must match number of rows)");
			}
			if(_col == 0 || _row == 0) {
				*this = table(a.size(), 1);
				for(int i = 0; i < _row; i++) {
					this->at(i, 0) = a[i];
				}
				if(!name.empty()){
					set_col_name(0, name);
				}
			}
			else {
				_col++;
				for(int i = 0; i < _row; i++) {
					data.insert(data.begin() + get_index(i, j), a[i]);
				}
				if(!name.empty()){
					col_names[j+1] = col_names[j];
					set_col_name(j, name);
				}
			}
		}

		/**
		 * @brief Pushes column at the end of the table
		 * Doesn't set empty names (no exception)
		 * @param a column to be inserted
		 * @param name `default("n/a")` name of the column
		 * @throws `std::invalid_argument` `a.size()` $\neq$ row size
		 */
		void push_col(std::vector<D> a, std::string name = empty_name)
		{
			if(_row != 0 && a.size() != _row) {
				throw std::invalid_argument("var::table::push_col -> invalid given column size (must match number of rows)");
			}
			insert_col(a, _col, name);
		}

		/**
		 * @brief Swaps two column with their names
		 *
		 * @param j1 index 1
		 * @param j2 index 2
		 * @throws `std::invalid_argument` invalid index
		 */
		void swap_col(int j1, int j2)
		{
			if(j1 < 0 || j1 >= _col || j2 < 0 || j2 >= _col) {
				throw std::invalid_argument("var::table::swap_col -> invalid column index");
			}
			for(int i = 0; i < _row; i++) {
				std::swap(data[get_index(i, j1)], data[get_index(i, j2)]);
			}
			std::swap(col_names[j1], col_names[j2]);
		}

		/**
		 * @brief Replaces given column index
		 * Doesn't set empty names (no exception) 
		 * @param j column index
		 * @param a new column
		 * @param name `default("n/a")` name of column
		 * @throw `std::invalid_argument` invalid `j` index
		 * @throw `std::invalid_argument` `a.size()` $\neq$ row size
		 */
		void replace_col(int j, std::vector<D> a, std::string name = empty_name)
		{
			if(j < 0 || j >= _col) {
				throw std::invalid_argument("var::table::erase_col -> invalid column index");
			}
			if(a.size() != _row) {
				throw std::invalid_argument("var::table::replace_col -> invalid given column size (must match number of rows)");
			}
			for(int i = 0; i < _row; i++) {
				this->at(i, j) = a.at(i);
			}
			if(!name.empty()){
				set_col_name(j, name);
			}
		}

		/**
		 * @brief Combines the columns of another table
		 *
		 * @param other `table`
		 * @throw `std::invalid_argument` `other` doesn't have same number of rows
		 */
		void join_col(table other)
		{
			if(other.row() != _row) {
				throw std::invalid_argument("var::table::join_col -> Size mismatch");
			}
			for(int j = 0; j < other.col(); j++) {
				push_col(other.get_col(j), other.col_names[j]);
			}
		}

		/**
		 * @brief Erases given index column
		 *
		 * @param j column index
		 * @throws `std::invalid_argument` invalid index
		 * @throws `std::runtime_error` table is empty
		 */
		void erase_col(int j)
		{
			if(j < 0 || j >= _col) {
				throw std::invalid_argument("var::table::erase_col -> invalid column index");
			}
			if(_col == 0) {
				throw std::runtime_error("var::table::erase_col -> table is empty");
			}
			for(int i = 0; i < _row; i++) {
				data.erase(data.begin() + get_index(i, j) - i);
			}
			col_names.erase(j);
			if(_col != 0) {
				_col--;
			}
		}

		/**
		 * @brief Removes last column
		 *
		 * ## Row setters
		 * @throws `std::runtime_error` table is empty
		 */
		void pop_col()
		{
			if(_col == 0) {
				throw std::runtime_error("var::table::pop_col -> table is empty");
			}
			erase_col(_col - 1);
		}

		/**
		 * @brief Set the row names
		 * Doesn't set empty names (no exception) 
		 * @param names vector of row names
		 * @throws `std::invalid_argument` if `names.size()` doesnt match row size
		 */
		void set_row_names(std::vector<std::string> names)
		{
			if(names.size() != _row) {
				throw std::invalid_argument("table::set_row_names -> Input parameter size doesn't match curret row size");
			}
			for(int i = 0; i < _row; i++) {
				set_row_name(i, names[i]);
			}
		}

		/**
		 * @brief Set the row name
		 * Doesn't set empty names (no exception) 
		 * @param i index of row
		 * @param name name of row
		 * @throws `std::invalid_argument` invalid index `i`
		 */
		void set_row_name(int i, std::string name)
		{
			if(i < 0 || i >= _row) {
				throw std::invalid_argument("var::table::set_col_name -> given row index doesn't exist");
			}
			if(!name.empty()){
				row_names[i] = name;
			}
		}

		/**
		 * @brief Inserts new row into given index
		 * Doesn't set empty names (no exception)
		 * @param a row to be inserted
		 * @param i row index to insert at
		 * @param name `default("n/a")` name of the row
		 * @throws `std::invalid_argument` invalid row index
		 * @throws `std::invalid_argument` `a.size()` $\neq$ column size
		 */
		void insert_row(std::vector<D> a, int i, std::string name = empty_name)
		{
			if(i < 0 || i > _row) {
				throw std::invalid_argument("var::table::insert_row -> invalid rowumn index");
			}
			if(_col != 0 && a.size() != _col) {
				throw std::invalid_argument("var::table::insert_row -> invalid given rowumn size (must match number of rows)");
			}
			if(_col == 0 || _row == 0) {
				*this = table(1, a.size());
				for(int j = 0; j < _col; j++) {
					this->at(0, j) = a[j];
				}
				if(!name.empty()){
					set_row_name(0, name);
				}
			}
			else {
				_row++;
				for(int j = 0; j < _col; j++) {
					data.insert(data.begin() + get_index(i, j), a[j]);
				}
				if(!name.empty()){
					row_names[i+1] = row_names[i];
					set_row_name(i, name);
				}
			}
		}

		/**
		 * @brief Pushes row at the end of the table
		 * Doesn't set empty names (no exception) 
		 * @param a row to be inserted
		 * @param name name of the row
		 * @throws `std::invalid_argument` `a.size()` $\neq$ column size
		 */
		void push_row(std::vector<D> a, std::string name = empty_name)
		{
			if(_row != 0 && a.size() != _col) {
				throw std::invalid_argument("var::table::push_row -> invalid given rowumn size (must match number of rows)");
			}
			insert_row(a, _row, name);
		}

		/**
		 * @brief Swaps two rows with theri names
		 * 
		 * @param i1 index 1
		 * @param i2 index 2
		 * @throws `std::invalid_argument` invalid index
		 */
		void swap_row(int i1, int i2)
		{
			if(i1 < 0 || i1 >= _row || i2 < 0 || i2 >= _row) {
				throw std::invalid_argument("var::table::swap_row -> invalid rowumn index");
			}
			for(int j = 0; j < _col; j++) {
				std::swap(data[get_index(i1, j)], data[get_index(i2, j)]);
			}
			std::swap(row_names[i1], row_names[i2]);
		}

		/**
		 * @brief Replaces given rowumn index
		 * Doesn't set empty names (no exception) 
		 * @param j rowumn index
		 * @param a new rowumn
		 * @param name `default("n/a")` name of row 
		 * @throw `std::invalid_argument` invalid `j` index
		 * @throw `std::invalid_argument` `a.size()` $\neq$ row size
		 */
		void replace_row(int i, std::vector<D> a, std::string name = empty_name)
		{
			if(i < 0 || i >= _row) {
				throw std::invalid_argument("var::table::erase_row -> invalid rowumn index");
			}
			if(a.size() != _col) {
				throw std::invalid_argument("var::table::replace_row -> invalid given rowumn size (must match number of rows)");
			}
			for(int j = 0; j < _col; j++) {
				this->at(i, j) = a.at(j);
			}
			if(!name.empty()){
				set_row_name(i, name);
			}
		}

		/**
		 * @brief Combines the rows of another table
		 *
		 *
		 * @param other ``table``
		 * @throw `std::invalid_argument` Size mismatch
		 */
		void join_row(table other)
		{
			if(other.col() != _col) {
				throw std::invalid_argument("var::table::join_row -> Size mismatch");
			}
			for(int i = 0; i < other.row(); i++) {
				push_row(other.get_row(i), other.row_names[i]);
			}
		}

		/**
		 * @brief Erases given index rowumn
		 *
		 * @param i rowumn index
		 */
		void erase_row(int i)
		{
			if(i < 0 || i >= _row) {
				throw std::invalid_argument("var::table::erase_row -> invalid rowumn index");
			}
			for(int j = 0; j < _col; j++) {
				data.erase(data.begin() + get_index(i, j) - j);
			}
			row_names.erase(i);
			if(_row != 0) {
				_row--;
			}
		}

		/**
		 * @brief Removes last rowumn
		 *
		 * ## Data manipualtors
		 *
		 */
		void pop_row()
		{
			erase_row(_row - 1);
		}

		// ************************* Data manipulators ************************ //

		/**
		 * @brief Resizes the table
		 *
		 * !!! warning "Warning"
		 * <pre>
		 *     This can impact performance as it calls std::vector::resize
		 * </pre>
		 *
		 * @param r number of rows
		 * @param c number of colums
		 */
		void resize(int r, int c)
		{
			// checking
			if(r < 0 || c < 0) {
				throw std::invalid_argument("var::table::resize -> Invalid values");
			}
			_row = r;
			_col = c;
			data.resize(_row * _col);
		}

		/**
		 * @brief Converts all elements to n
		 *
		 * **Usage**:
		 * ```cpp
		 * t.turn_to(1); // turns all elements to 1
		 * ```
		 *
		 * @param n the specifeid variable
		 *
		 */
		void turn_to(D n)
		{
			for(int i = 0; i < _row; i++) {
				for(int j = 0; j < _col; j++) {
					this->at(i, j) = n;
				}
			}
		}

		/**
		 * @brief Sum of all elements
		 *
		 * **Usage**:
		 * ```cpp
		 * auto sum = m.sum();
		 * ```
		 *
		 * @return ``D``
		 */
		D sum()
		{
			D SUM = D(0);
			for(int i = 0; i < _row; i++) {
				for(int j = 0; j < _col; j++) {
					SUM += this->at(i, j);
				}
			}
			return SUM;
		}

		// ************************* Operators ************************ //

		// ************************* Splits ************************* //

		// BUG: This needs to check if first line is a string or not
		/**
		 * @brief Reads from csv file
		 *
		 *
		 *
		 * @param fname: file name
		 * @param headers_exist: `default(true)` flag indicating if column names exist in file
		 * @return `true` : if read is success
		 * @return `false`: if read did not complete
		 */
		bool read_csv(std::string fname, bool headers_exist = true)
		{
			std::ifstream file(fname);
			if(file.is_open()) {
				data.clear();
				col_names.clear();
				row_names.clear();

				// col name
				std::string line, str;

				std::vector<std::string> headers;
				if(headers_exist){
					std::getline(file, line);
					std::stringstream ss(line);
					while(getline(ss, str, ',')) {
						headers.push_back(str);
					}
				}

				// data
				while(std::getline(file, line)) {
					// Create a stringstream of the current line
					std::stringstream ss(line);
					std::vector<D> r;

					while(getline(ss, str, ',')) {
						D val = D();
						try {
							std::stringstream(str) >> val;
						} catch (std::exception) {
							val = D();
						}
						r.push_back(val);
					}
					this->push_row(r, std::string());
				}

				if(headers_exist){
					for(int j = 0; j < _col; j++){
						col_names[j] = headers[j];
					}
				}
				file.close();
				return true;
			}
			file.close();
			return false;
		}

		/**
		 * @brief Reads from csv file
		 *
		 * @param file
		 * @return true: if read is success
		 * @return false: if read did not complete
		 */
		bool save_csv(std::string filename)
		{
			std::ofstream file(filename);
			if(file.is_open()) {
				for(int i = 0; i < col_names.size(); i++) {
					if(i != col_names.size() - 1) {
						file << col_names[i] << ",";
					}
					else {
						file << col_names[i] << "\n";
					}
				}
				for(int i = 0; i < _row; i++) {
					for(int j = 0; j < _col; j++) {
						if(j != _col - 1) {
							file << this->at(i, j) << ",";
						}
						else if(j == _col - 1) {
							file << this->at(i, j) << "\n";
						}
					}
				}
				file.close();
				return true;
			}
			file.close();
			return false;
		}

		/**
		 * @brief Shows a certain number of rows in table
		 *
		 * @param r
		 */
		void show(int r)
		{
			std::string line;
			if(_col == 1) {
				line = generate_line((std::pow(2, 1 / _col) + 0.2) * sz * _col);
			}
			else {
				line = generate_line((std::pow(1.05, 1 / _col) + 1.9 / _col) * sz * _col);
			}
			for(int i = -1; i < r; i++) {
				for(int j = 0; j < _col; j++) {
					// to print header
					if(i == -1) {
						// if column header deosnt exist exist
						std::string col_name =
							(col_names.find(j) == col_names.end()) ? "col-" + std::to_string(j) : col_names[j];

						if(j == 0 && _col > 1) {
							std::cout << prd("     ", sz) << "│"
									  << prd(col_names[j], sz) << "│";
						}
						else if(j == 0 && _col == 1) {
							std::cout << prd("     ", sz) << "│"
									  << prd(col_names[j], sz) << "\n";
							std::cout << line << "\n";
						}
						else if(j != _col - 1) {
							std::cout << prd(col_names[j], sz) << "│";
						}
						else {
							std::cout << prd(col_names[j], sz) << "\n";
							std::cout << line << "\n";
						}
					}
					// printing values
					else {
						// row name + val
						if(j == 0 && _col > 1) {
							std::cout << prd(row_names[i], sz) << "│"
									  << prd(get_col(j).at(i), sz) << "│";
						}
						else if(j == 0 && _col == 1) {
							std::cout << prd(row_names[i], sz) << "│"
									  << prd(get_col(j).at(i), sz) << "│"
									  << "\n";
							std::cout << line << "\n";
						}
						else if(j != _col - 1) {
							std::cout << prd(get_col(j).at(i), sz) << "│";
						}

						else {
							std::cout << prd(get_col(j).at(i), sz) << "\n";
							std::cout << line << "\n";
						}
					}
				}
			}
		}

		/**
		 * @brief shows all of the table
		 *
		 */
		void show()
		{
			show(_row);
		}

		/**
		 * @brief Shows col_names only
		 *
		 */
		void show_header()
		{
			show(0);
		}

		// ************************* Statistics ************************ //

		/**
		 * @brief Extract average of each column into a vector
		 *
		 * Used in `describe_all()`
		 *
		 * @return `std::vector<D>`: same size as number of columns
		 */
		std::vector<D> get_avgs()
		{
			std::vector<D> a;
			for(int j = 0; j < _col; j++) {
				a.push_back(stats::get_avg(get_col(j)));
			}
			return a;
		}

		/**
		 * @brief Extract STD of each column into a vector
		 *
		 * Used in `describe_all()`
		 *
		 * @return `std::vector<D>` same size as number of columns
		 */
		std::vector<D> get_stds()
		{
			std::vector<D> a;
			for(int j = 0; j < _col; j++) {
				a.push_back(stats::get_std(get_col(j)));
			}
			return a;
		}

		/**
		 * @brief Extract variance of each column into a vector
		 *
		 * Used in `describe_all()`
		 *
		 * @return `std::vector<D>`: same size as numebr of columns
		 */
		std::vector<D> get_vars()
		{
			std::vector<D> a;
			for(int j = 0; j < _col; j++) {
				a.push_back(stats::get_var(get_col(j)));
			}
			return a;
		}

		/**
		 * @brief Extract QR of each column into a vector
		 *
		 * Used in `describe_all()`
		 *
		 * @return `std::vector<QR>`: same size as number of colums
		 */
		std::vector<QR<D>> get_qrs()
		{
			std::vector<QR<D>> a;
			for(int j = 0; j < _col; j++) {
				a.push_back(stats::get_qr(get_col(j)));
			}
			return a;
		}

		/**
		 * @brief Extract sum of each column into a vector
		 *
		 * @details Used in `describe_all()`
		 *
		 * @return `std::vector<D>` size is same size as number of colums
		 *
		 */
		std::vector<D> get_sums()
		{
			std::vector<D> a;
			for(int j = 0; j < _col; j++) {
				a.push_back(vect::sum(get_col(j)));
			}
			return a;
		}

		/**
		 * @brief Statistical summary of all colums in table
		 *
		 * * Example:
		 *
		 * |       | Avg | STD | VAR | Min | Q1 | Q2 | Q3 | Max | IQR | Sum |
		 * | ---   | --- | --- | --- | --- | ---| ---| ---| --- | --- | --- |
		 * | col-0 |  .. |  .. |  .. |  .. |  ..|  ..|  ..|  .. |  .. |  .. |
		 * | col-1 |  .. |  .. |  .. |  .. |  ..|  ..|  ..|  .. |  .. |  .. |
		 *
		 * @return `table<D>`
		 */
		table describe_all()
		{
			table t(_col, 10);
			auto avg = get_avgs();
			auto std = get_stds();
			auto var = get_vars();
			auto qrs = get_qrs();
			auto sms = get_sums();



			// loading col names
			t.col_names[0] = "Avg";
			t.col_names[1] = "STD";
			t.col_names[2] = "VAR";
			t.col_names[3] = "Min";
			t.col_names[4] = "Q1";
			t.col_names[5] = "Q2";
			t.col_names[6] = "Q3";
			t.col_names[7] = "Max";
			t.col_names[8] = "IQR";
			t.col_names[9] = "Sum";

			for(int i = 0; i < _col; i++) {
				std::vector<D> rr; // row
				rr.push_back(avg[i]);
				rr.push_back(std[i]);
				rr.push_back(var[i]);
				rr.push_back(qrs[i].LQ);
				rr.push_back(qrs[i].Q1);
				rr.push_back(qrs[i].Q2);
				rr.push_back(qrs[i].Q3);
				rr.push_back(qrs[i].UQ);
				rr.push_back(qrs[i].Q3 - qrs[i].Q1);
				rr.push_back(sms[i]);
				t.replace_row(i, rr, col_names[i]);
			}
			return t;
		}
	};
}