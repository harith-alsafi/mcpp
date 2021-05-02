#include <vector>
// TODO differentiation 
// TODO Eular method 
// TODO power series 
// TODO limits 
namespace cal
{
    template<typename LAMBDA, typename S>
    S diff(LAMBDA f, S b){
 
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
    std::vector<S> diff(LAMBDA f, S min, S max){
        std::vector<S> temp;
        for(S i = min; i < max; i++){
            temp.push_back(diff(f, i));
        }
        return temp;
    }

}