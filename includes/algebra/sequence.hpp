#include <vector>
namespace alg
{
    namespace seq
    {
        template<typename LAMBDA, typename S>
        std::vector<S> sequence(LAMBDA f, int start, int stop){
            auto sum = f(start);
            for(int i =  start+1; i <= stop; i++){
                sum += f(i);
            }
            return sum;        
        } 

        template<typename LAMBDA>
        auto sum(LAMBDA f, int start, int stop){
            auto sum = f(start);
            for(int i =  start+1; i <= stop; i++){
                sum += f(i);
            }
            return sum; 
        }
    }

}