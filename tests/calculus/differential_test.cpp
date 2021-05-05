#include "../../includes/mcpp.hpp"
#include "../../lib/googletest/googletest/include/gtest/gtest.h"
#include <cmath>

using namespace calc;

TEST(diff, point)
{
    // function
    auto f = [](double a){
        return pow(a, 2)+sin(a)*exp(a)+pow(cos(a), 2);
    };

    // first order
    ASSERT_EQ(round(diff(f, 2.0)), 8.0);

    // 2nd order 
    ASSERT_EQ(round(diff(f, 2.0, 2)), -3.0);

    // 3rd order 
    ASSERT_EQ(round(diff(f, 2.0, 3)), -23.0);

    // 4th order 
    ASSERT_EQ(round(diff(f, 2.0, 4)), -32.0);

    // 5th order 
    ASSERT_EQ(round(diff(f, 2.0, 5)), -2.0);

    // 6th order 
    ASSERT_EQ(round(diff(f, 2.0, 6)), 46);
}

TEST(diff, fun)
{
    // function
    auto f = [](double a){
        return pow(a, 2)+sin(a)*exp(a)+pow(cos(a), 2);
    };

    std::vector<double> x = {-2, -1, 0, 1, 2};
    
    // first derivative
    std::vector<double> dy1 = {-3, 0, 3, 7};
    auto ansdy1 = diff(f, x, 1);
    ASSERT_TRUE(num::round(ansdy1) == dy1);

    // 2nd derivative
    std::vector<double> dy2 = {3, 3, 5};
    auto ansdy2 = diff(f, x, 2);
    ASSERT_TRUE(num::round(ansdy2) == dy2);

    // 3rd derivative
    std::vector<double> dy3 = {-1, 2};
    auto ansdy3 = diff(f, x, 3);
    ASSERT_TRUE(num::round(ansdy3) == dy3);

    // 3rd derivative
    std::vector<double> dy4 = {3};
    auto ansdy4 = diff(f, x, 4);
    ASSERT_TRUE(num::round(ansdy4) == dy4);

}

int main(int argc, char **argv) 
{
   testing::InitGoogleTest(&argc, argv);
   return RUN_ALL_TESTS();
}