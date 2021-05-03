#include <vector>
#include "../misc/misc.hpp"
#include <cmath>
namespace cal
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
    S diff(LAMBDA f, S x, int n = 1, S h=S(0.001)){
        S ans = S(0.0);
        for(int k = 0; k <= n; k++){
            ans += 
            std::pow((-1), (k+n))
            *msc::combination(n, k)
            *f(x+k*h);
        }
        return S(ans/(std::pow(h, n)));
    }
    
    /**
     * @brief diff to produce a vector 
     * 
     * @tparam S 
     * @tparam LAMBDA 
     * @param f 
     * @param min 
     * @param max 
     * @return std::vector<S> 
     */
    template<typename S, typename LAMBDA>
    std::vector<S> diff(LAMBDA f, S min, S max, int n = 1){
        std::vector<S> temp;
        for(S i = min; i < max; i++){
            temp.push_back(diff(f, i, n));
        }
        return temp;
    }

    /**
     * @brief taylor series of a function 
     * 
     * @tparam S 
     * @tparam LAMBDA 
     * @param f 
     * @param min 
     * @param max 
     * @return std::vector<S> 
     */
    template<typename S, typename LAMBDA>
    std::vector<S> taylor(LAMBDA f, S min, S max){
        
    }

}
// TODO differentiation 
// TODO Eular method 
// TODO power series 
// TODO limits 
// TODO more testing on 'diff' cases 