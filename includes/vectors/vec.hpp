#include <vector>
#include <cmath>
namespace vec
{
    template<typename S>
    std::vector<S> dot(std::vector<S> a, std::vector<S> b){
        if(a.size() != b.size()){
            throw std::invalid_argument("Invalid size");
        }
    }

    template<typename S>
    std::vector<S> cross(std::vector<S> a, std::vector<S> b){
        if(a.size() != b.size()){
            throw std::invalid_argument("Invalid size");
        } 
    }

    template<typename S>
    std::vector<S> pow(std::vector<S> a, S b){
        std::vector<S> temp;
        S temp2 = 1;
        for(int i = 0; i < a.size(); i++){
            temp.push_back(std::pow(a[i], b));
        }
        return temp;
    }

    template<typename S>
    std::vector<S> pow(std::vector<S> a, std::vector<S> b){
        if(a.size() != b.size()){
            throw std::invalid_argument("Invalid size");
        }
        std::vector<S> temp;
        S temp2 = 1;
        for(int i = 0; i < a.size(); i++){
            temp.push_back(std::pow(a[i], b[i]));
        }
        return temp;
    }
// ********************************************************* //
    template<typename S>
    std::vector<S> sin(std::vector<S> a){

    }
    template<typename S>
    std::vector<S> cos(std::vector<S> a){

    }
    template<typename S>
    std::vector<S> tan(std::vector<S> a){

    }
    template<typename S>
    std::vector<S> sec(std::vector<S> a){

    }
    template<typename S>
    std::vector<S> csc(std::vector<S> a){

    }
    template<typename S>
    std::vector<S> cot(std::vector<S> a){

    }

    template<typename S>
    std::vector<S> asin(std::vector<S> a){

    }

    template<typename S>
    std::vector<S> acos(std::vector<S> a){

    }
    template<typename S>
    std::vector<S> atan(std::vector<S> a){

    }
    template<typename S>
    std::vector<S> asec(std::vector<S> a){

    }
    template<typename S>
    std::vector<S> acsc(std::vector<S> a){

    }
    template<typename S>
    std::vector<S> acot(std::vector<S> a){

    }
// ********************************************************* //
    template<typename S>
    std::vector<S> sinh(std::vector<S> a){

    }
    template<typename S>
    std::vector<S> cosh(std::vector<S> a){

    }
    template<typename S>
    std::vector<S> tanh(std::vector<S> a){

    }
    template<typename S>
    std::vector<S> sech(std::vector<S> a){

    }
    template<typename S>
    std::vector<S> csch(std::vector<S> a){

    }
    template<typename S>
    std::vector<S> coth(std::vector<S> a){

    }

    template<typename S>
    std::vector<S> asinh(std::vector<S> a){

    }
    
    template<typename S>
    std::vector<S> acosh(std::vector<S> a){

    }
    template<typename S>
    std::vector<S> atanh(std::vector<S> a){

    }
    template<typename S>
    std::vector<S> asech(std::vector<S> a){

    }
    template<typename S>
    std::vector<S> acsch(std::vector<S> a){

    }
    template<typename S>
    std::vector<S> acoth(std::vector<S> a){

    }
// ********************************************************* //
    template<typename S>
    std::vector<S> exp(std::vector<S> a){

    }
}
