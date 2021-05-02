#include <vector>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <ctype.h>
#include <limits.h>
using namespace std;

template<typename S, typename LAMBDA>
S test(S a, LAMBDA f){
	return a*f(a);
}

template<typename S, typename LAMBDA>
std::vector<S> diff(LAMBDA f){
	vector<S> a = {1, 2, 3};
	return a;
}

int main()
{
	auto f = [](int a){return a*2;};
	std::vector<int> v;
	auto a = diff<int>(f);
	cout << a[0];
}