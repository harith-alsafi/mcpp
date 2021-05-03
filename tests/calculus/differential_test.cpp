#include "../../includes/calculus/differential.hpp"
#include "../../lib/googletest/googletest/include/gtest/gtest.h"
#include <cmath>

using namespace cal;

TEST(calc, diff)
{
    // function
    auto f = [](double a){
        return std::pow(a, 3);
    };

    // first order
    ASSERT_EQ(std::round(diff(f, 2.0)), 12.0);

    // 2nd order 
    ASSERT_EQ(std::round(diff(f, 2.0, 2)), 12.0);

    // 3rd order 
    ASSERT_EQ(std::round(diff(f, 2.0, 3)), 6.0);

}

int main(int argc, char **argv) 
{
   testing::InitGoogleTest(&argc, argv);
   return RUN_ALL_TESTS();
}