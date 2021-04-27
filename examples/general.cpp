#include <iostream>
#include <string>

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

int main()
{

	int main_choice;
	while(1)
	{
		menu(main_choice);
		if(main_choice == 1){
			cout << "You choose option-1 \n";
		}
	}

}