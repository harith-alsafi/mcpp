#include <vector>
#include <string>

#define red (int []){247, 55, 49}
#define black (int []){0, 0, 0}

void figure(
    std::string title,
    int width,
    int height,
    int background[3]
);

void plot(
    std::vector<float>& x, 
    std::vector<float>& y,
    std::string legend,
    int draw[3]
);

void plot(
    std::vector<float>& x, 
    std::vector<float>& y,
    std::string legend = ""
);

void point(
    float x,
    float y,
    std::string legend = ""
);