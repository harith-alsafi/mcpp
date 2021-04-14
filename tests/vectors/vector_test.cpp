#include "../../lib/googletest/googletest/include/gtest/gtest.h"
#include "../../includes/mcpp.hpp"

TEST(operations, vec_and_vec)
{
   std::vector<float> a = {1, 2, 3, 4};
   std::vector<float> b = {5, 6, 7, 8};
   // multiply 
   auto c1 = a*b;
   ASSERT_EQ(c1.size(), a.size());
   for(int i = 0; i < c1.size(); i++){
      ASSERT_FLOAT_EQ(c1[i], a[i]*b[i]);
   }
   // add
   auto c2 = a+b;
   ASSERT_EQ(c2.size(), a.size());
   for(int i = 0; i < c2.size(); i++){
      ASSERT_FLOAT_EQ(c2[i], a[i]+b[i]);
   }
   // subtract 
   auto c3 = a-b;
   ASSERT_EQ(c3.size(), a.size());
   for(int i = 0; i < c3.size(); i++){
      ASSERT_FLOAT_EQ(c3[i], a[i]-b[i]);
   }
   // divid
   auto c4 = a/b;
   ASSERT_EQ(c4.size(), a.size());
   for(int i = 0; i < c4.size(); i++){
      ASSERT_FLOAT_EQ(c4[i], a[i]/b[i]);
   }
}

TEST(operations, vec_and_var)
{
   std::vector<int> a = {1, 2, 3, 4};
   // multiply 
   auto b1 = a*2;
   auto b2 = 2*a;
   ASSERT_EQ(b1, b2);
   for(int i = 0; i < b2.size(); i++){
      ASSERT_EQ(b2[i], a[i]*2);
   } 
   // addd
   b1 = a+2;
   b2 = 2+a;
   ASSERT_EQ(b1, b2);
   for(int i = 0; i < b2.size(); i++){
      ASSERT_EQ(b2[i], a[i]+2);
   }

   // subtract
   b1 = a-2;
   for(int i = 0; i < b1.size(); i++){
      ASSERT_EQ(b1[i], a[i]-2);
   } 

   // divid
   b1 = a/2;
   for(int i = 0; i < b1.size(); i++){
      ASSERT_EQ(b1[i], a[i]/2);
   }
}

TEST(functions, misc)
{
   std::vector<int> a = {1, 2, 3, 4};
   // power 
   auto c = vec::pow(a, 2);
   testing::internal::CaptureStdout();
   std::cout << c;
   std::string output = testing::internal::GetCapturedStdout();
   EXPECT_TRUE(output == "[1, 4, 9, 16]");

}

TEST(operations, vec_all)
{
   std::vector<int> a = {1, 2, 3, 4};
   auto b = 2*vec::pow(a, 2)+3;
   ASSERT_EQ(a.size(), b.size());
   for(int i = 0; i < a.size(); i++){
      ASSERT_EQ(b[i], 2*std::pow(a[i], 2)+3);
   }
   testing::internal::CaptureStdout();
   std::cout << a;
   std::string output = testing::internal::GetCapturedStdout();
   EXPECT_TRUE(output == "[1, 2, 3, 4]");
}



int main(int argc, char **argv)
{
   testing::InitGoogleTest(&argc, argv);
   return RUN_ALL_TESTS();
}