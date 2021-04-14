int red[3] = {247, 55, 49};
#include <iostream>
#include <string>
#include <vector>
#include <complex>
template<typename S>
std::vector<S> operator *(std::vector<S> first, std::vector<S> second){
    if(first.size() != second.size()){
        throw std::invalid_argument("Invalid size");
    }
    std::vector<S> temp;
    for(int i = 0; i < first.size(); i++){
        temp.push_back(first[i]*second[i]);
    }
    return temp;
}

template<typename S>
std::vector<S> operator *(S s, std::vector<S> v){
    std::vector<S> temp;
    for(int i = 0; i < v.size(); i++){
        temp.push_back(s*v[i]);
    }
    return temp;
}

template<typename S>
std::vector<S> operator *(std::vector<S> v, S s){
    std::vector<S> temp;
    for(int i = 0; i < v.size(); i++){
        temp.push_back(v[i]*s);
    }
    return temp;
}

template<typename S>
std::vector<S> operator +(std::vector<S> first, std::vector<S> second){
    if(first.size() != second.size()){
        throw std::invalid_argument("Invalid size");
    }
    std::vector<S> temp;
    for(int i = 0; i < first.size(); i++){
        temp.push_back(first[i]+second[i]);
    }
    return temp;
}

template<typename S>
std::vector<S> operator +(S s, std::vector<S> v){
    std::vector<S> temp;
    for(int i = 0; i < v.size(); i++){
        temp.push_back(s+v[i]);
    }
    return temp;
}

template<typename S>
std::vector<S> operator +(std::vector<S> v, S s){
    std::vector<S> temp;
    for(int i = 0; i < v.size(); i++){
        temp.push_back(v[i]+s);
    }
    return temp;
}

// template<typename S>
// S pow(S a, S b){
//     S temp2 = 1;
// 	for(S j = 0; j < b; j++){
// 		temp2 *= a;
// 	}
// 	return temp2;
// }

template<typename S>
std::vector<S> vpow(std::vector<S> a, S b){
    std::vector<S> temp;
    S temp2 = 1;
    for(int i = 0; i < a.size(); i++){
        temp.push_back(std::pow(a[i], b));
    }
    return temp;
}

template<typename S>
std::vector<S> vpow(std::vector<S> a, std::vector<S> b){
    std::vector<S> temp;
    S temp2 = 1;
    for(int i = 0; i < a.size(); i++){
        temp.push_back(std::pow(a[i], b[i]));
    }
    return temp;
}

int main()
{
	std::complex<int> H;
	std::vector<int> a = {2, 3};
	std::vector<int> b = {4, 3};
	auto c = 2*vpow(a, 2)+3;
	auto d = vpow(a, b);
	std::cout << c[1] << "\n";
	std::cout << d[0];
	std::cout << std::sin(2);

}