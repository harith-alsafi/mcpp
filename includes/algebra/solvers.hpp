#pragma once
#include <vector>
#include <algorithm>
#include <stdexcept>
#include <complex>
#include "../mcpp.hpp"
namespace alg
{
    namespace slv
    {
        

        template<typename D, typename LAMBDA>
        std::vector<D> root(LAMBDA f, D tol = D(1000)){

        }

        /**
         * @brief Mainly used to get real roots through newton method
         * 
         * @tparam D 
         * @tparam LAMBDA 
         * @param f 
         * @param x0 
         * @return std::vector<D> 
         */
        template<typename D, typename LAMBDA>
        std::vector<D> newton_root(LAMBDA f, D x0){

        }

        template<typename D>
        struct ans
        {
            std::vector<D> real;
            std::vector<std::complex<D>> imag;
        };

        template<typename D>
        ans<D> poly_root(int n, std::vector<D> a){
            
        }

        /**
         * @brief Linear root through inputing Ax+C such that it is represented as {A, C}
         * 
         * **Usage**:
         * ```cpp
         * // answer of x+2 = 0;
         * auto ans = linear({1, 2});
         * ```
         * 
         * @tparam D 
         * @param eq 
         * @return D 
         */
        template<typename D>
        D linear_root(std::vector<D> eq){
            return (-eq[1]/eq[0]); 
        }

        /**
         * @brief Used to get real roots through bisection method
         * 
         * **Usage**:
         * ```cpp
         * // roots between -5 and -1
         * auto ans = bisection_root<double>(f, -5.0, -1.0);
         * ```
         * 
         * @tparam D 
         * @tparam LAMBDA 
         * @param f function 
         * @param min minimum value 
         * @param max maximum value
         * @param tol tolerance 
         * @return ``D``
         */
        template<typename D, typename LAMBDA>
        D bisection_root(LAMBDA f, D min, D max, D tol = D(0.00001)){
            auto check = [&](D a, D b)-> bool{
                return (a < b && f(a)*f(b) < 0);
            };
            auto mid = [&](D a, D b)->D{
                return ((a+b)/D(2));
            };
            if(!check(min, max)){
                throw std::runtime_error("min and max don't have opposite signs");
            }

            D a = min;
            D b = max;
            D t = mid(a, b);
            int counter = 0;
            int max_counter = (int) 100*(D(1)/tol);
            int dp = mth::decimals(tol)-1;

            while(mth::round(f(t), dp) != mth::round(tol, dp) && counter <= max_counter){
                // case 1
                if(check(t, b)){
                    a = t;
                }    
                // case 2
                else{
                    b = t;
                }
                t = mid(a, b);
                counter++;
            }

            if(counter > max_counter){
                throw std::runtime_error("No solution was found");
            }

            return t;
        
        }

    }

}