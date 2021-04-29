#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

int main()
{
	vector<int> a = {1, 2, 23, 3};
	int b = *min_element(a.begin(), a.end());
	cout << b;
}