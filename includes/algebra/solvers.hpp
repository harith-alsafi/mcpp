#pragma once
#include <vector>
#include <algorithm>
#include <stdexcept>
#include <complex>
namespace alg
{
    namespace slv
    {
        template<typename D, typename LAMBDA>
        auto root(LAMBDA f, D tol = D(1000)){
            std::vector<D> real;
            for(D x = -tol; x < tol; x++){
                if(f(x) == D(0)){
                    real.push_back(x);
                }
            }
            if(real.empty()){
                // std::vector<std::complex<D>> imag;
                // std::complex<D> imax(tol, D(0));
                // std::complex<D> jmax(D(0), tol);
                // for(std::complex<D> i(-tol, D(0)); i < imax; i++){
                //     for(std::complex<D> j(D(0), -tol); j < jmax; j++){
                //         if(f(i.real()+j.imag()*std::sqrt(-1)) == D(0)){
                //             std::complex<D> temp(i, j);
                //             imag.push_back(temp);
                //             temp.
                //         }
                //     }
                // }
            }
            return real;
        }

        template<typename D, typename LAMBDA>
        std::vector<D> newton_root(LAMBDA f, D x0){

        }


        template<typename D, typename LAMBDA>
        std::vector<D> bisection_root(LAMBDA f, D min, D max, D tol = D(0.0001)){
            
        }

    }

}