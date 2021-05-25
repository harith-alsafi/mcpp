#include "../../lib/googletest/googletest/include/gtest/gtest.h"
#include "../../includes/mcpp.hpp"
#include <cmath>

TEST(solvers, roots)
{
   auto f = [](double x)->double{
      return pow(x, 2)*2.0+3.0*x;
   };
   auto ans = alg::slv::root<double>(f);
   
}


int main(int argc, char **argv) 
{
   testing::InitGoogleTest(&argc, argv);
   return RUN_ALL_TESTS();
}