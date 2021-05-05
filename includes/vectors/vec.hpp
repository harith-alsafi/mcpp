#pragma once
#include <vector>
#include <cmath>



namespace num
{
    /**
     * @brief overriding default round 
     * 
     * @tparam S 
     * @param a 
     * @param dp 
     * @return S 
     */
    template<typename S>
    S round(S &a, int dp = 0){
        if(a < S(0)){
            return S((int)(a*pow(10, dp)-.5)/pow(10, dp));
        }
        return S((int)(a*pow(10, dp)+.5)/pow(10, dp));
    }

    /**
     * @brief operation on vectors
     * 
     * @tparam S 
     * @tparam LAMBDA 
     * @param f 
     * @param x 
     * @return std::vector<S> 
     */
    template<typename S, typename LAMBDA>
    std::vector<S> vec_op(LAMBDA f, std::vector<S> &x){
        std::vector<S> y;
        for(int i = 0; i < x.size(); i++){
            y.push_back(f(x[i]));
        }
        return y;
    }
    
    /**
     * @brief difference of elements in vector
     * 
     * @tparam S 
     * @param a 
     * @return std::vector<S> 
     */
    template<typename S> 
    std::vector<S> difference(std::vector<S> &a){
        std::vector<S> temp;
        for(int i = 0; i < a.size()-1; i++){
            temp.push_back(a[i+1]-a[i]);
        }
        return temp;
    }

    /**
     * @brief average of elements in vector
     * 
     * @tparam S 
     * @param a 
     * @return std::vector<S> 
     */
    template<typename S> 
    std::vector<S> averages(std::vector<S> &a){
        std::vector<S> temp;
        for(int i = 0; i < a.size()-1; i++){
            temp.push_back((a[i+1]+a[i])*S(0.5));
        }
        return temp;
    }


    template<typename S> 
    std::vector<S> linspace(S start, S end, int count){

    }

    /**
     * @brief rounding the vector
     * 
     * @tparam S 
     * @param a 
     * @param dp 
     * @return std::vector<S> 
     */
    template<typename S> 
    std::vector<S> round(std::vector<S> &a, int dp = 0){
        std::vector<S> b;
        for(int i = 0; i< a.size(); i++){

            b.push_back(round(a[i], dp));

        }
        return b;
    }

    template<typename S> 
    S min(std::vector<S> &a){
       S mmin = *std::min_element(a.begin(), a.end());
       return mmin; 
    }

    template<typename S> 
    S max(std::vector<S> &a){
       S mmax = *std::max_element(a.begin(), a.end());
       return mmax;   
    }

    template<typename S> 
    std::vector<S> abs(std::vector<S> &a){

    }

    /**
     * @brief difference
     * 
     * @tparam S 
     * @param start 
     * @param end 
     * @param diff 
     * @return std::vector<S> 
     */
    template<typename S>
    std::vector<S> arange(S start, S end, S diff){

    }

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

    /**
     * @brief vector^b
     * 
     * @tparam S 
     * @param a 
     * @param b 
     * @return std::vector<S> 
     */
    template<typename S>
    std::vector<S> pow(std::vector<S> a, S b){
        std::vector<S> temp;
        for(int i = 0; i < a.size(); i++){
            temp.push_back(std::pow(a[i], b));
        }
        return temp;
    }

    /**
     * @brief vector^vector
     * 
     * @tparam S 
     * @param a 
     * @param b 
     * @return std::vector<S> 
     */
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
// TODO add matrix power
// TODO add matrix functions
