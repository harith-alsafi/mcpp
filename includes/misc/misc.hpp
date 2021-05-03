#pragma once
namespace msc
{


    int factorial(int n){
        int sum = 1;
        for(int i = n; i > 0; i--){
            sum = sum*i;
        }
        return sum;
    }

    int combination(int n, int k){
        return factorial(n)/(factorial(k)*factorial(n-k));
    }

    
}
// TODO polyfit
// TODO binomial 
// TODO combination (n, k)