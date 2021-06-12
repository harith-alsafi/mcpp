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
         * @brief Linear root through inputing Ax+C such that it is represented as vector {A, C}
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
            if(eq.size() > 2){
                throw std::invalid_argument("Vector is more than 2");
            }
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

        /**
         * @brief Solves a system of linear equations expressed as a matrix
         * 
         * Representing the input
         * 
         * $$
         *  \displaylines{\underbrace{\left[\begin{array}
         *  \\ a_1 & b_1 & c_1  \\\\
         *  a_2 & b_2 & c_2  \\\\
         *  a_3 & b_3 & c_3  \\\\
         *  \end{array}\right]}_A \ 
         *  \underbrace{\left[\begin{array}
         *  \\ x_1 \\\\
         *  x_2 \\\\
         *  x_3 \\\\
         *  \end{array}\right]}_x = 
         *  \underbrace{\left[\begin{array}
         *  \\ d_1 \\\\
         *  d_2 \\\\
         *  d_3
         *  \end{array}\right]}_b \\\\
         *  eq = \left[\begin{array}{rrr:r}
         *  a_1 & b_1 & c_1 & d_1 \\\\
         *  a_2 & b_2 & c_2 & d_2 \\\\
         *  a_3 & b_3 & c_3 & d_3 \\\\
         *  \end{array}\right]}
         * $$
         * 
         * @tparam D 
         * @param eq ``matrix``
         * @return std::vector<D> 
         */
        template<typename D>
        std::vector<D> linear_sim(var::matrix<D> eq){
            var::matrix<D> A = eq(0, eq.row(), 0, eq.col()-1);
            if(!A.is_square()){
                throw std::invalid_argument("A in Ax=B should be a square ([AB] is incomplete)");
            }
            
            std::vector<D> C = eq.get_col(eq.col()-1);
            typename var::matrix<D>::LU LU = A.plu();
            
            // LZ = P^T*C
            var::matrix<D> temp;
            temp.push_col(C);
            temp = LU.P.T()*temp;
            C = temp.get_col(temp.col()-1);

            std::vector<D> Z;
            Z.push_back(C[0]/LU.L[0][0]);
            for(int i = 1; i < LU.L.row(); i++){
                D sum = C[i]; 
                for(int j = 0; j <= i; j++){
                    sum -= LU.L[i][j]*Z[j];
                }
                Z.push_back(sum/LU.L[i][i]);
            }

            // UX = Z
            std::vector<D> X(Z.size());
            X[Z.size()-1] = Z[Z.size()-1]/LU.U[LU.U.row()-1][LU.U.row()-1];
            for(int i = LU.U.row()-2; i >= 0; i--){
                D sum = Z[i]; 
                for(int j = LU.U.col(); j > i; j--){
                    sum -= LU.U[i][j]*X[j];
                }
                X[i] = sum/LU.U[i][i];
            }

            return X;
        }

    }

}