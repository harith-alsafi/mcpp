#pragma once
#include <vector>
#include <algorithm>
namespace alg
{
    namespace slv
    {
        template<typename D, typename LAMBDA>
        std::vector<D> root(LAMBDA f, D tol = D(1000)){
            std::vector<D> temp;
            for(D x = -tol; x < tol; x++){
                if(f(x) == D(0)){
                    temp.push(0);
                }
            }
            return temp;
        }
    }

}