#include <vector>
#include <string>

/**
 * @brief RGB values for colors
 */
extern const std::vector<int> RED = {247, 55, 49};
extern const std::vector<int> BLACK = {0, 0, 0};
extern const std::vector<int> BLUE = {36, 114, 200};
extern const std::vector<int> GREEN = {53, 200, 36};
extern const std::vector<int> WHITE = {255, 255, 255};

struct param_plot
{
	std::vector<float> xrange = {-5, 5};
	std::vector<float> yrange = {-5, 5};
	std::string legend = "";
	std::vector<int> draw = BLACK;
};

struct param_fig
{
    std::string title = "Window";
    int size = 400;
    std::vector<int> background = WHITE;
};

void figure(param_fig f);

void plot(
    std::vector<float>& x, 
    std::vector<float>& y,
    param_plot p
);

void point(
    float x,
    float y,
    param_plot p
);

void hline(
    float x,
    float y,
    param_plot p
);

void vline(
    float x,
    float y,
    param_plot p
);