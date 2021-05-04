#include "../../includes/calculus/differential.hpp"
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
    std::vector<double> dy1 = {-5, -1.2, 1, 5, 8};
    

}

int main(int argc, char **argv) 
{
   testing::InitGoogleTest(&argc, argv);
   return RUN_ALL_TESTS();
}