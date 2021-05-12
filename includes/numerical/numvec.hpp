#pragma once
#include <vector>
#include <cmath>

namespace num
{
    /**
     * @brief overriding default round 
     * 
     * @tparam D 
     * @param a 
     * @param dp 
     * @return D 
     */
    template<typename D>
    D round(D &a, int dp = 0){
        if(a < D(0)){
            return D((int)(a*pow(10, dp)-.5)/pow(10, dp));
        }
        return D((int)(a*pow(10, dp)+.5)/pow(10, dp));
    }

    /**
     * @brief rounding the vector
     * 
     * @tparam D 
     * @param a 
     * @param dp 
     * @return std::vector<D> 
     */
    template<typename D> 
    std::vector<D> round(std::vector<D> &a, int dp = 0){
        std::vector<D> b;
        for(int i = 0; i< a.size(); i++){

            b.push_back(round(a[i], dp));

        }
        return b;
    }

    template<typename D> 
    D min(std::vector<D> &a){
       D mmin = *std::min_element(a.begin(), a.end());
       return mmin; 
    }

    template<typename D> 
    D max(std::vector<D> &a){
       D mmax = *std::max_element(a.begin(), a.end());
       return mmax;   
    }

    template<typename D> 
    std::vector<D> abs(std::vector<D> &a){

    }





    /**
     * @brief vector^b
     * 
     * @tparam D 
     * @param a 
     * @param b 
     * @return std::vector<D> 
     */
    template<typename D>
    std::vector<D> pow(std::vector<D> a, D b){
        std::vector<D> temp;
        for(int i = 0; i < a.size(); i++){
            temp.push_back(std::pow(a[i], b));
        }
        return temp;
    }

    /**
     * @brief vector^vector
     * 
     * @tparam D 
     * @param a 
     * @param b 
     * @return std::vector<D> 
     */
    template<typename D>
    std::vector<D> pow(std::vector<D> a, std::vector<D> b){
        if(a.size() != b.size()){
            throw std::invalid_argument("Invalid size");
        }
        std::vector<D> temp;
        D temp2 = 1;
        for(int i = 0; i < a.size(); i++){
            temp.push_back(std::pow(a[i], b[i]));
        }
        return temp;
    }

// ********************************************************* //
    template<typename D>
    std::vector<D> sin(std::vector<D> a){

    }
    template<typename D>
    std::vector<D> cos(std::vector<D> a){

    }
    template<typename D>
    std::vector<D> tan(std::vector<D> a){

    }
    template<typename D>
    std::vector<D> sec(std::vector<D> a){

    }
    template<typename D>
    std::vector<D> csc(std::vector<D> a){

    }
    template<typename D>
    std::vector<D> cot(std::vector<D> a){

    }

    template<typename D>
    std::vector<D> asin(std::vector<D> a){

    }

    template<typename D>
    std::vector<D> acos(std::vector<D> a){

    }
    template<typename D>
    std::vector<D> atan(std::vector<D> a){

    }
    template<typename D>
    std::vector<D> asec(std::vector<D> a){

    }
    template<typename D>
    std::vector<D> acsc(std::vector<D> a){

    }
    template<typename D>
    std::vector<D> acot(std::vector<D> a){

    }
// ********************************************************* //
    template<typename D>
    std::vector<D> sinh(std::vector<D> a){

    }
    template<typename D>
    std::vector<D> cosh(std::vector<D> a){

    }
    template<typename D>
    std::vector<D> tanh(std::vector<D> a){

    }
    template<typename D>
    std::vector<D> sech(std::vector<D> a){

    }
    template<typename D>
    std::vector<D> csch(std::vector<D> a){

    }
    template<typename D>
    std::vector<D> coth(std::vector<D> a){

    }

    template<typename D>
    std::vector<D> asinh(std::vector<D> a){

    }
    
    template<typename D>
    std::vector<D> acosh(std::vector<D> a){

    }
    template<typename D>
    std::vector<D> atanh(std::vector<D> a){

    }
    template<typename D>
    std::vector<D> asech(std::vector<D> a){

    }
    template<typename D>
    std::vector<D> acsch(std::vector<D> a){

    }
    template<typename D>
    std::vector<D> acoth(std::vector<D> a){

    }
// ********************************************************* //
    template<typename D>
    std::vector<D> exp(std::vector<D> a){

    }
}