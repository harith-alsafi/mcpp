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
#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>
#include <limits>
#include <numeric>
#include <sstream>
#include <stdexcept>
#include <vector>

// TODO: complete testing
// TODO: fix documentation and code

namespace var
{
	/**
	 * @brief 2D array class inheriting from `std::vector<std::vector<D>>`
	 */
	template <typename D>
	class table: public std::vector<std::vector<D>>
	{
	  public:
		/**
		 * @brief Struct to contain the quartile range
		 *
		 */
		struct QR
		{
			D LQ; ///< Lower quartile
			D Q1; ///< Q1 (25%)
			D Q2; ///< Q2 (50%)
			D Q3; ///< Q3 (75%)
			D UQ; ///< Upper quartile
		};

	  protected:
		std::vector<std::string> col_names; ///< Stores the column names
		std::vector<std::string> row_names; ///< Stores the row names
		int _row;                            ///< Row size
		int _col;                            ///< Colum size
		int sz = 10;                        ///< Spacing size for print

		/**
		 * @brief Sets the \ref _row and \ref _col according to the current class size
		 *
		 */
		void set_size()
		{
			if(this->empty()) {
				_row = 0;
				_col = 0;
				return;
			}
			_col = (int) this->at(0).size();
			_row = (int) this->size();
		}

		/**
		 * @brief Returns column index of given header/column name
		 *
		 * @param headname: string of column name
		 * @return `int`: $[-1]$: index not found <br>
		 * @return `int`: $[\geq 0]$: index found
		 *
		 */
		int check_header(std::string headname)
		{
			for(int i = 0; i < (int) col_names.size(); i++) {
				if(col_names[i] == headname) {
					return i;
				}
			}
			return -1;
		}

		/**
		 * @brief Get the column vector based on header name
		 *
		 * @param headname
		 * @return `std::vector<D>`: Empty if nothing exits <br>
		 *
		 */
		std::vector<D>& get_col_(std::string headname)
		{
			int j = check_header(headname);
			set_size();
			std::vector<D> a;
			if(j >= 0) {
				for(int i = 0; i < _row; i++) {
					a.push_back(&this->at(i).at(j));
				}
			}
			return a;
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
		 * @param l: number of "―" in the generated string
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
		 * @brief Clears current row names and generates new ones
		 *
		 */
		void generate_rows()
		{
			if(!row_names.empty()) {
				row_names.clear();
			}
			set_size();
			for(int i = 0; i < _row; i++) {
				row_names.push_back("Row-" + std::to_string(i));
			}
		}

		/**
		 * @brief Clears current column names and generates new ones 
		 * 
		 */
		void generate_cols()
		{
			if(!col_names.empty()) {
				col_names.clear();
			}
			set_size();
			for(int i = 0; i < _col; i++) {
				row_names.push_back("Col-" + std::to_string(i));
			}
		}

	  public:
		/**
		 * @brief Construct a new table object
		 *
		 */
		table(): _row(0), _col(0) {}

		/**
		 * @brief Extract average of each column into a vector
		 *
		 * Used in `describe_all()`
		 *
		 * @return `std::vector<D>`
		 */
		std::vector<D> get_avgs()
		{
			std::vector<D> a;
			for(int j = 0; j < (int) col_names.size(); j++) {
				a.push_back(get_avg(get_col_(col_names[j])));
			}
			return a;
		}

		/**
		 * @brief Extract STD of each column into a vector
		 *
		 * Used in `describe_all()`
		 *
		 * @return `std::vector<D>`
		 */
		std::vector<D> get_stds()
		{
			std::vector<D> a;
			for(int j = 0; j < col_names.size(); j++) {
				a.push_back(get_std(get_col_(col_names[j])));
			}
			return a;
		}

		/**
		 * @brief Extract variance of each column into a vector
		 *
		 * Used in `describe_all()`
		 *
		 * @return `std::vector<D>`
		 */
		std::vector<D> get_vars()
		{
			std::vector<D> a;
			for(int j = 0; j < col_names.size(); j++) {
				a.push_back(get_var(get_col_(col_names[j])));
			}
			return a;
		}

		/**
		 * @brief Extract QR of each column into a vector
		 *
		 * Used in `describe_all()`
		 *
		 * @return `std::vector<QR>`
		 */
		std::vector<QR> get_qrs()
		{
			std::vector<QR> a;
			for(int j = 0; j < col_names.size(); j++) {
				a.push_back(get_qr(get_col_(col_names[j])));
			}
			return a;
		}

		/**
		 * @brief Extract sum of each column into a vector
		 *
		 * Used in `describe_all()`
		 *
		 * @return `std::vector<D>`
		 */
		std::vector<D> get_sums()
		{
			std::vector<D> a;
			for(int j = 0; j < col_names.size(); j++) {
				a.push_back(get_sum(get_col_(col_names[j])));
			}
			return a;
		}



		// ******** Getters ************* //

		/**
		 * @brief Get the row size
		 *
		 * @return `int`
		 */
		int row() { return this->size(); }

		/**
		 * @brief Get the col size
		 *
		 * @return `int`
		 */
		int col()
		{
			if(!this->empty()) {
				return this->at(0).size();
			}
			else {
				return 0;
			}
		}

		std::vector<std::string>& get_col_names() { return col_names; }

		D& get_element(int i, int j)
		{
		}

		// ***** operators ** /

		/**
		 * @brief Returns refrence to colum of given column name
		 *
		 * @param headname
		 * @return `std::vector<D>&` Refrence to given column name
		 * @throws `std::invalid_argument` given column name doesn't exist
		 */
		std::vector<D>& operator[](std::string headname)
		{
			if(check_header(headname) < 0) {
				throw std::invalid_argument("var::table::operator[] -> given column name doesn't exist");
			}
			return get_col_(headname);
		}

		/**
		 * @brief Sorts data ascending
		 *
		 * @param a
		 * @return std::vector<D>
		 */
		static std::vector<D> sort_asc(std::vector<D>& a)
		{
			std::vector<D> v_sorted(a.size());
			std::partial_sort_copy(a.begin(), a.end(), v_sorted.begin(), v_sorted.end());
			return v_sorted;
		}

		static std::vector<D> sort_des(std::vector<D>& a)
		{
			std::vector<D> v_sorted(a.size());
			std::partial_sort_copy(a.begin(), a.end(), v_sorted.begin(), v_sorted.end());
			return v_sorted;
		}

		/**
		 * @brief Get the min value of vector
		 *
		 * @param a
		 * @return D
		 */
		static D get_min(std::vector<D> a)
		{
			return *std::min_element(a.begin(), a.end());
		}

		/**
		 * @brief Get the max value of vector
		 *
		 * @param a
		 * @return D
		 */
		static D get_max(std::vector<D> a)
		{
			return *std::max_element(a.begin(), a.end());
		}

		/**
		 * @brief Get the sum of vector
		 *
		 * @param a
		 * @return D
		 */
		static D get_sum(std::vector<D> a)
		{
			return std::accumulate(a.begin(), a.end(), 0);
		}

		/**
		 * @brief Get the avg of vector
		 *
		 * @param a
		 * @return D
		 */
		static D get_avg(std::vector<D> a)
		{
			return get_sum(a) / a.size();
		}

		/**
		 * @brief Get the variance of vector
		 *
		 * @param a
		 * @return D
		 */
		static D get_var(std::vector<D> a)
		{
			D mean = get_avg(a);
			int N  = a.size();
			D sum  = 0;
			for(int i = 0; i < N; i++) {
				sum += pow((a[i] - mean), 2);
			}
			return (D) sum / N;
		}

		/**
		 * @brief Get the standard diviation of vector
		 *
		 * @param a
		 * @return D
		 */
		static D get_std(std::vector<D> a)
		{
			return sqrt(get_var(a));
		}

		/**
		 * @brief Get the quartile range of a vector
		 *
		 * @param a
		 * @return QR
		 */
		static QR get_qr(std::vector<D> a)
		{
			QR qr;
			qr.LQ         = get_min(a);
			qr.UQ         = get_max(a);
			auto a_sorted = sort_asc(a);
			qr.Q1         = a_sorted.at((int) (a_sorted.size()) / 4);
			qr.Q2         = a_sorted.at((int) (a_sorted.size()) / 2);
			qr.Q3         = a_sorted.at((int) (3 * (a_sorted.size())) / 4);
			return qr;
		}

		/**
		 * @brief Get the relation coefficient of two vectors
		 *
		 * @param _x
		 * @param _y
		 * @return D
		 */
		static D get_r(
			std::vector<D> _x, std::vector<D> _y
		)
		{
			if(_x.size() != _y.size()) {
				throw std::invalid_argument("var::table::get_r -> Size mismatch");
			}
			D sumx  = table::get_sum(_x);
			D sumy  = table::get_sum(_y);
			D sumxx = table::get_sum(_x * _x);
			D sumxy = table::get_sum(_x * _y);
			D sumyy = table::get_sum(_y * _y);
			return (_x.size() * sumxy - (sumx * sumy)) /
				   (sqrt((_x.size() * sumxx - pow(sumx, 2)) * (_x.size() * sumyy - pow(sumy, 2))));
		}

		/**
		 * @brief Reads from csv file
		 *
		 * @param file: file name
		 * @return `true` : if read is success
		 * @return `false`: if read did not complete
		 */
		bool read_csv(std::string filename)
		{
			std::ifstream file(filename);
			if(file.is_open()) {
				this->clear();
				col_names.clear();

				// col name
				std::string line, colname;
				std::getline(file, line);

				std::stringstream ss(line);
				while(getline(ss, colname, ',')) {
					col_names.push_back(colname);
				}

				// data
				D val;
				while(std::getline(file, line)) {
					// Create a stringstream of the current line
					std::stringstream ss(line);

					std::vector<D> r;
					while(ss >> val) {
						r.push_back(val);

						// If the next token is a comma, ignore it and move on
						if(ss.peek() == ',') ss.ignore();
					}
					this->push_back(r);
				}
				set_size();
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
				set_size();
				for(int i = 0; i < _row; i++) {
					for(int j = 0; j < _col; j++) {
						if(j != _col - 1) {
							file << this->at(i).at(j) << ",";
						}
						else if(j == _col - 1) {
							file << this->at(i).at(j) << "\n";
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
			if(row_names.empty()) {
				generate_rows();
			}
			set_size();
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
									  << prd(get_col_(col_names[j]).at(i), sz) << "│";
						}
						else if(j == 0 && _col == 1) {
							std::cout << prd(row_names[i], sz) << "│"
									  << prd(get_col_(col_names[j]).at(i), sz) << "│"
									  << "\n";
							std::cout << line << "\n";
						}
						else if(j != _col - 1) {
							std::cout << prd(get_col_(col_names[j]).at(i), sz) << "│";
						}

						else {
							std::cout << prd(get_col_(col_names[j]).at(i), sz) << "\n";
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
			set_size();
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

		/**
		 * @brief Statistical summary of all colums in table
		 *
		 * @return table
		 */
		table describe_all()
		{
			table t;
			auto avg = get_avgs();
			auto std = get_stds();
			auto var = get_vars();
			auto qrs = get_qrs();
			auto sms = get_sums();
			set_size();
			// loading row names
			for(int i = 0; i < _col; i++) {
				t.row_names.push_back(col_names[i]);
			}
			// loading col names
			t.col_names.push_back("Mean");
			t.col_names.push_back("STD");
			t.col_names.push_back("VAR");
			t.col_names.push_back("Min");
			t.col_names.push_back("Q1");
			t.col_names.push_back("Q2");
			t.col_names.push_back("Q3");
			t.col_names.push_back("Max");
			t.col_names.push_back("IQR");
			t.col_names.push_back("Sum");

			// loading values
			t._row = t.row_names.size();
			t._col = t.col_names.size();
			for(int i = 0; i < t._row; i++) {
				std::vector<D> rr;
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
				t.push_back(rr);
			}
			t.set_size();
			t.sz = 11;
			return t;
		}

		/**
		 * @brief Get the row as table
		 *
		 * @param r
		 * @return table
		 */
		table get_row_table(int r)
		{
			table t;
			t.push_back(this->at(r));
			t.col_names = col_names;
			if(row_names.empty()) {
				generate_rows();
			}
			t.row_names.push_back(row_names[r]);
			return t;
		}

		/**
		 * @brief Get the col as table
		 *
		 * @param name
		 * @return table
		 */
		table get_col_table(std::string name)
		{
			table t;
			auto a = get_col_(name);
			for(int i = 0; i < a.size(); i++) {
				t.push_back({ a[i] });
			}
			if(row_names.empty()) {
				generate_rows();
			}
			t.col_names.push_back(col_names[check_header(name)]);
			return t;
		}

		/**
		 * @brief Adds new colum
		 *
		 * @param col_name
		 * @param col_data
		 * @return true
		 * @return false
		 */
		bool add_col(std::vector<D> col_data, std::string col_name = std::string())
		{
			set_size();
			if((col_data.size() != _row && _row != 0) || col_data.empty()) {
				return false;
			}
			col_names.push_back(col_name);
			for(int i = 0; i < col_data.size(); i++) {
				if(_row == 0) {
					this->push_back({ col_data[i] });
				}
				else {
					this->at(i).push_back(col_data[i]);
				}
			}
			return true;
		}

		bool add_row(std::vector<D> row_data)
		{
		}
	};

}