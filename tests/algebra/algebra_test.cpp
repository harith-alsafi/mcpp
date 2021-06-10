#include "../../lib/googletest/googletest/include/gtest/gtest.h"
#include "../../includes/mcpp.hpp"
#include <cmath>

TEST(solvers, bisection)
{
   auto f = [](double x)->double{
      return pow(x, 2)*2.0+3.0*x;
   };
   auto ans = alg::slv::bisection_root<double>(f, -5.0, -1.0);

   ASSERT_EQ(mth::decimals(2.000), 1);
   ASSERT_EQ(mth::decimals(2.121), 3);
   ASSERT_EQ(mth::decimals(0.001), 3);
   ASSERT_TRUE(ans == -1.5);

   auto ans2 = alg::slv::bisection_root<double>(f, -0.5, 1);

   ASSERT_TRUE(round(ans2) == 0.0);

}

TEST(solvers, newton)
{

}



int main(int argc, char **argv) 
{
   testing::InitGoogleTest(&argc, argv);
   return RUN_ALL_TESTS();
}