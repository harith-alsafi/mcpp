#include <iostream>
#include <string>
#include <complex>

using std::cout;
using std::string;
using std::cin;

void menu(int &a)
{
	cout << "[1]-Option A \n";
	cout << "[2]-Option B \n";
	cout << "[3]-Option A \n";
	cout << "------------------ \n";
	cout << "Enter you choice: ";
	if(!(cin >> a)){
		cin.clear();
		cin.ignore();
		cout << "Please input a correct choice \n";
	}
}

struct point{
	int x;
	int y;
};

int main()
{

	std::complex<point> p;

}