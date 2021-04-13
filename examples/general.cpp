int red[3] = {247, 55, 49};
#include <iostream>
#include <string>
#include <vector>


struct parameters
{
	std::vector<float> xrange = {-5, 5};
	std::vector<float> yrange = {-5, 5};
	std::vector<int> draw;
	std::string legend = "";
};

void fun(parameters p){
	std::cout << p.xrange[0];
}

int main()
{
    std::string
        str1( "Hello" ),
        str2( "world" );
    fun({{-10, 10}, {-10, 10}, {1, 2, 3}});

}