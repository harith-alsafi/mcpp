#pragma once
#include "../mcpp.hpp"
// forward declaration 
namespace var
{
    template<typename D>
    class matrix;
}
namespace num
{
    namespace mat
    {
        /**
         * @brief Produeces identity matrix of length ``n``
         * 
         * @tparam D 
         * @param n 
         * @return ``var::matrix<D>`` 
         */
        template<typename D>
        var::matrix<D> eye(int n){
            var::matrix<D> temp(n, n);
            for(int i = 0; i < n; i++){
                for(int j = 0; j < n; j++){
                    if(i == j){
                        temp[i][j] = D(1);
                    }
                    else{
                        temp[i][j] = D(0);
                    }
                }
            }
            return temp;
        }

        template<typename D>
        var::matrix<D> perms(D a, D b){
            
        }

    }
}