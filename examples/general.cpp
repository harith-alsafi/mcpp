<<<<<<< HEAD
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
=======
#include<vector>
#include <iostream>
#include <cstdio>
using namespace std;

int8_t a = 200;
uint8_t b = 100;
int main()
{
    if(a > b){
        cout << "h";
    }
    else{
        cout < < 
    }

>>>>>>> d002b6b9a211bdee581980b417c82bf213281910

}