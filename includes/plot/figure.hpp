#pragma once
#include <string>
#include <vector>

namespace plt
{


	/**
	 * @brief RGB values for colors
	 */
	static std::vector<int> RED = {247, 55, 49};
	static std::vector<int> BLACK = {0, 0, 0};
	static std::vector<int> BLUE = {36, 114, 200};
	static std::vector<int> GREEN = {53, 200, 36};
	static std::vector<int> WHITE = {255, 255, 255};

	struct details
	{
		std::vector<double> xrange = {-5, 5};
		std::vector<double> yrange = {-5, 5};
		std::vector<int> color = BLACK;
		std::string legend = "";
		int thickness = 1;
	};

	/**
	 * @brief initializes figure
	 * 
	 * @param title 
	 * @param size 
	 * @param background 
	 */
	void figure(
		std::string title = "Window",
		int size = 400,
		std::vector<int> background = WHITE
	);

	/**
	 * @brief plots values 
	 * 
	 * @param x 
	 * @param y 
	 * @param xrange 
	 * @param yrange 
	 * @param draw 
	 * @param legend 
	 */
	template<typename S>
	void plot(
		std::vector<S> x, 
		std::vector<S> y,
		details d
	);

	template<typename S>
	void point(
		std::vector<S> x, 
		std::vector<S> y,
		details d
	);

	template<typename S>
	void hline(
		std::vector<S> x, 
		std::vector<S> y,
		details d
	);

	template<typename S>
	void vline(
		std::vector<S> x, 
		std::vector<S> y,
		details d
	);
}
