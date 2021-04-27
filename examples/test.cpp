#include <mcpp/mcpp.hpp>
var::matrix<int> a;

int main()
{
    a.resize(2, 2);
    a.insert_col({1, 2});
    
}