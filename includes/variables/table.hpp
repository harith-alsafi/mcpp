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
#include <vector>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <sstream>
#include <numeric>
#include <limits>
#include <cmath>

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
		std::vector<std::string> headers; ///< Stores the column names
		std::vector<std::string> rows;    ///< Stores the row names
		int row;                          ///< Row size
		int col;                          ///< Colum size
		int sz = 10;                      ///< Spacing size for print

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
			for(int i = 0; i < (int) headers.size(); i++) {
				if(headers[i] == headname) {
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
		std::vector<D> get_col_(std::string headname)
		{
			int j = check_header(headname);
			std::vector<D> a;
			if(j >= 0) {
				for(int i = 0; i < (int) this->size(); i++) {
					a.push_back(this->at(i).at(j));
				}
			}
			return a;
		}

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
			for(int j = 0; j < (int) headers.size(); j++) {
				a.push_back(get_avg(get_col_(headers[j])));
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
			for(int j = 0; j < headers.size(); j++) {
				a.push_back(get_std(get_col_(headers[j])));
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
			for(int j = 0; j < headers.size(); j++) {
				a.push_back(get_var(get_col_(headers[j])));
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
			for(int j = 0; j < headers.size(); j++) {
				a.push_back(get_qr(get_col_(headers[j])));
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
			for(int j = 0; j < headers.size(); j++) {
				a.push_back(get_sum(get_col_(headers[j])));
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
			for(int i = 0; i < padding / 2; ++i){
				spaces << " ";
			}
			ss << spaces.str() << s << spaces.str(); // format with padding
			// if odd #, add 1 space
			if(padding > 0 && padding % 2 != 0){
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
		 * @brief Generates row names
		 *
		 */
		void generate_rows()
		{
			rows.clear();
			for(int i = 0; i < this->size(); i++) {
				rows.push_back("Row-" + std::to_string(i));
			}
		}

		/**
		 * @brief Sets the \ref row and \ref col according to the current class size 
		 *
		 */
		void check_size()
		{
			if(this->empty()) {
				row = 0;
				col = 0;
				return;
			}
			col = this->at(0).size();
			row = this->size();
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

	  public:
		/**
		 * @brief Construct a new table object
		 *
		 */
		table() {}

		/**
		 * @brief Destroy the table object
		 *
		 */
		~table() {}

		// ******** Getters ************* //

		/**
		 * @brief Get the row size 
		 *
		 * @return `int`
		 */
		int row(){return this->size(); }

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

		std::vector<std::string> get_headers() { return headers;}

		D& get_element(int i, int j)
		{
			
		}

		bool change_header(std::string before, std::string after)
		{

		}

		bool set_headers(std::vector<std::string> heads){

		}

		// ***** operators ** /

		/**
		 * @brief Returns colum of certain header
		 *
		 * @param headname
		 * @return `std::vector<D>&`
		 */
		std::vector<D>& operator[](std::string headname)
		{
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
				headers.clear();

				// col name
				std::string line, colname;
				std::getline(file, line);

				std::stringstream ss(line);
				while(getline(ss, colname, ',')) {
					headers.push_back(colname);
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
				check_size();
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
				for(int i = 0; i < headers.size(); i++) {
					if(i != headers.size() - 1) {
						file << headers[i] << ",";
					}
					else {
						file << headers[i] << "\n";
					}
				}
				check_size();
				for(int i = 0; i < row; i++) {
					for(int j = 0; j < col; j++) {
						if(j != col - 1) {
							file << this->at(i).at(j) << ",";
						}
						else if(j == col - 1) {
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
			if(rows.empty()) {
				generate_rows();
			}
			check_size();
			std::string line;
			if(col == 1) {
				line = generate_line((std::pow(2, 1 / col) + 0.2) * sz * col);
			}
			else {
				line = generate_line((std::pow(1.05, 1 / col) + 1.9 / col) * sz * col);
			}
			for(int i = -1; i < r; i++) {
				for(int j = 0; j < col; j++) {
					// to print header
					if(i == -1) {
						if(j == 0 && col > 1) {
							std::cout << prd("     ", sz) << "│"
									  << prd(headers[j], sz) << "│";
						}
						else if(j == 0 && col == 1) {
							std::cout << prd("     ", sz) << "│"
									  << prd(headers[j], sz) << "\n";
							std::cout << line << "\n";
						}
						else if(j != col - 1) {
							std::cout << prd(headers[j], sz) << "│";
						}
						else {
							std::cout << prd(headers[j], sz) << "\n";
							std::cout << line << "\n";
						}
					}
					// printing values
					else {
						// row name + val
						if(j == 0 && col > 1) {
							std::cout << prd(rows[i], sz) << "│"
									  << prd(get_col_(headers[j]).at(i), sz) << "│";
						}
						else if(j == 0 && col == 1) {
							std::cout << prd(rows[i], sz) << "│"
									  << prd(get_col_(headers[j]).at(i), sz) << "│"
									  << "\n";
							std::cout << line << "\n";
						}
						else if(j != col - 1) {
							std::cout << prd(get_col_(headers[j]).at(i), sz) << "│";
						}

						else {
							std::cout << prd(get_col_(headers[j]).at(i), sz) << "\n";
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
			check_size();
			show(row);
		}

		/**
		 * @brief Shows headers only
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
			check_size();
			// loading row names
			for(int i = 0; i < col; i++) {
				t.rows.push_back(headers[i]);
			}
			// loading col names
			t.headers.push_back("Mean");
			t.headers.push_back("STD");
			t.headers.push_back("VAR");
			t.headers.push_back("Min");
			t.headers.push_back("Q1");
			t.headers.push_back("Q2");
			t.headers.push_back("Q3");
			t.headers.push_back("Max");
			t.headers.push_back("IQR");
			t.headers.push_back("Sum");

			// loading values
			t.row = t.rows.size();
			t.col = t.headers.size();
			for(int i = 0; i < t.row; i++) {
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
			t.check_size();
			t.sz = 11;
			return t;
		}

		/**
		 * @brief Get the row as table
		 *
		 * @param r
		 * @return table
		 */
		table get_row(int r)
		{
			table t;
			t.push_back(this->at(r));
			t.headers = headers;
			if(rows.empty()) {
				generate_rows();
			}
			t.rows.push_back(rows[r]);
			return t;
		}

		/**
		 * @brief Get the col as table
		 *
		 * @param name
		 * @return table
		 */
		table get_col(std::string name)
		{
			table t;
			auto a = get_col_(name);
			for(int i = 0; i < a.size(); i++) {
				t.push_back({ a[i] });
			}
			if(rows.empty()) {
				generate_rows();
			}
			t.headers.push_back(headers[check_header(name)]);
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
		bool add_col(std::string col_name, std::vector<D> col_data)
		{
			check_size();
			if((col_data.size() != row && row != 0) || col_data.empty()) {
				return false;
			}
			headers.push_back(col_name);
			for(int i = 0; i < col_data.size(); i++) {
				if(row == 0) {
					this->push_back({ col_data[i] });
				}
				else {
					this->at(i).push_back(col_data[i]);
				}
			}
			return true;
		}




	};

}