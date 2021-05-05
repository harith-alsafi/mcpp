#pragma once
#include <vector>
#include "../mcpp.hpp"
#include <cmath>
namespace calc
{
    /**
     * @brief nth derivative at a point 
     * 
     * @tparam LAMBDA 
     * @tparam S 
     * @param f 
     * @param x 
     * @param n 
     * @param h 
     * @return S 
     */
    template<typename LAMBDA, typename S>
    S diff(LAMBDA f, S x, int n = 1, S h=S(0.00001)){
        // BUG higher orders have high error 
        S ans = S(0.0);
        if(n > 2 && x!= S(0)){
            h = x*sqrt(__DBL_EPSILON__)*1*pow(10, n);
        }
        for(int k = 0; k <= n; k++){
            ans += 
            pow((-1), k)
            *msc::combination(n, k)
            *f(x+(n-S(2)*k)*h);

        }
        return S(ans/(pow((S(2)*h), n)));
    }
    
    /**
     * @brief derivative of 2 vectors
     * 
     * @tparam S 
     * @param x 
     * @param y 
     * @param n 
     * @return std::vector<S> 
     */
    template<typename S>
    std::vector<S> diff(std::vector<S> &x, std::vector<S> &y, int n = 1){
        auto dx = num::difference(x);
        auto dy = num::difference(y);
        auto yp = dy/dx;
        auto xp = num::averages(x); 
        if(n == 1){
            return yp; 
        }
        return diff(xp, yp, n-1);
    }

    /**
     * @brief derivative of function to a vector
     * 
     * @tparam S 
     * @tparam LAMBDA 
     * @param f 
     * @param x 
     * @param n 
     * @return std::vector<S> 
     */
    template<typename S, typename LAMBDA>
    std::vector<S> diff(LAMBDA f, std::vector<S> &x, int n = 1){
        auto y = num::vec_op(f, x);
        return diff(x, y, n);
    }


    template<typename S, typename LAMBDA>
    std::vector<S> taylor(LAMBDA f, std::vector<S> &x, S x0=(0)){
        
    }

}
// TODO differentiation 
// TODO Eular method 
// TODO power series 
// TODO limits 
// TODO more testing on 'diff' cases 