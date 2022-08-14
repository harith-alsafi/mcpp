#include <bits/stdc++.h>

using namespace std;

template <typename T>
concept Type = requires(T t) {
	{t.operator+(T())};
};

template<Type D>
void f(D d){
    d+d;
}

class meow
{
    public:
    int a;
    meow(){}
    void operator+(meow b){

    }
};

int main(int argc, const char *argv[])
{
    meow m;

    f(m);
	return 0;
}
