int red[3] = {247, 55, 49};
#include <iostream>
#include <string>
#include <vector>


using namespace std;

struct parameters
{
	std::vector<float> xrange = {-5, 5};
	std::vector<float> yrange = {-5, 5};
	std::vector<int> draw = {0, 0, 0};
	std::string legend = "";
};


void test(int a, parameters p = {{-5,5}, {-5, 5}, {0, 0, 0}, "t"}){
	std::cout << a;
}

void plot(
    std::vector<float> x,
    std::vector<float> y,
	std::vector<float> xrange = {-5, 5},
	std::vector<float> yrange = {-5, 5},
	std::string legend = "",
	std::vector<int> draw = {0, 0, 0}
){
	std::cout << xrange[0];
}



template<typename S>
std::vector<S> operator *(S s, std::vector<S> &v){
    std::vector<S> temp;
    for(int i = 0; i < v.size(); i++){
        temp.push_back(s*v[i]);
    }
    return temp;
}

template<typename S>
std::vector<S> operator *(std::vector<S> &v, S s){
    std::vector<S> temp;
    for(int i = 0; i < v.size(); i++){
        temp.push_back(s*v[i]);
    }
    return temp;
}

// template<typename S>
// std::vector<S> T(std::vector<S> v){
// 	return v;
// }

std::vector<float> operator"" _T( long double d )
{
    return std::vector<float>(d);
}

template<typename T> class AvgOp {
public:
   T operator()(const T& left, const T& right)
   {
      return (left + right) / 2;
   }
};


int main()
{
	vector<int> a = {2, 3};
	auto b = 2*a;
	auto c = a*2;
	auto e = 2.0_T;
}