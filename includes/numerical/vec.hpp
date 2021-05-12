#pragma once
#include <vector>
#include <cmath>

namespace num
{
    namespace vec
    {
        /**
         * @brief operation on vectors
         * 
         * @tparam D 
         * @tparam LAMBDA 
         * @param f 
         * @param x 
         * @return std::vector<D> 
         */
        template<typename D, typename LAMBDA>
        std::vector<D> vec_op(LAMBDA f, std::vector<D> &x){
            std::vector<D> y;
            for(int i = 0; i < x.size(); i++){
                y.push_back(f(x[i]));
            }
            return y;
        }
        
        /**
         * @brief difference of elements in vector
         * 
         * @tparam D 
         * @param a 
         * @return std::vector<D> 
         */
        template<typename D> 
        std::vector<D> difference(std::vector<D> &a){
            std::vector<D> temp;
            for(int i = 0; i < a.size()-1; i++){
                temp.push_back(a[i+1]-a[i]);
            }
            return temp;
        }

        /**
         * @brief average of elements in vector
         * 
         * @tparam D 
         * @param a 
         * @return std::vector<D> 
         */
        template<typename D> 
        std::vector<D> averages(std::vector<D> &a){
            std::vector<D> temp;
            for(int i = 0; i < a.size()-1; i++){
                temp.push_back((a[i+1]+a[i])*D(0.5));
            }
            return temp;
        }


        template<typename D>
        std::vector<D> arange(D start, D end, D diff){
            std::vector<D> temp;
            for(D i = start; i < end; i+=diff){
                temp.push_back(i);
            }
            return temp;
        }

        template<typename D> 
        std::vector<D> linspace(D start, D end, int count){

        }

        template<typename D>
        std::vector<D> dot(std::vector<D> a, std::vector<D> b){
            if(a.size() != b.size()){
                throw std::invalid_argument("Invalid size");
            }
        }

        template<typename D>
        std::vector<D> cross(std::vector<D> a, std::vector<D> b){
            if(a.size() != b.size()){
                throw std::invalid_argument("Invalid size");
            } 
        }
    }
}