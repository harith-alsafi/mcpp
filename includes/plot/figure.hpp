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

	/**
	 * @brief checks parameter for the functions
	 * 
	 * @param exp 
	 * @param act 
	 */
	void check_param(int exp, int act);

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
	void plot(
		std::vector<float> x, 
		std::vector<float> y,
		std::vector<float> xrange = {-5, 5},
		std::vector<float> yrange = {-5, 5},
		std::vector<int> draw = BLACK,
		std::string legend = ""
	);

	void point(
		float x,
		float y,
		std::vector<float> xrange = {-5, 5},
		std::vector<float> yrange = {-5, 5},
		std::vector<int> draw = BLACK,
		std::string legend = ""
	);

	void hline(
		float x,
		float y,
		std::vector<float> xrange = {-5, 5},
		std::vector<float> yrange = {-5, 5},
		std::vector<int> draw = BLACK,
		std::string legend = ""
	);

	void vline(
		float x,
		float y,
		std::vector<float> xrange = {-5, 5},
		std::vector<float> yrange = {-5, 5},
		std::string legend = "",
		std::vector<int> draw = BLACK
	);
}
