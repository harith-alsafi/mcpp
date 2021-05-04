#include "../../includes/calculus/differential.hpp"
#include "../../lib/googletest/googletest/include/gtest/gtest.h"
#include <cmath>

using namespace cal;

TEST(calc, diff)
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

}

int main(int argc, char **argv) 
{
   testing::InitGoogleTest(&argc, argv);
   return RUN_ALL_TESTS();
}