#include <iostream>

using std::cout;
using std::string;
using std::cin;
using std::endl;

void menu(int &a)
{
	cout << "[1]-Tempreature converter \n";
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

void menu_temp_conversion(int &a, double &b)
{
	cout << "[1]-Celsuis to Fahrenheit \n";
	cout << "[2]-Fahrenheit to Celsuis \n";
	cout << "------------------ \n";
	cout << "Enter you choice: ";
	if(!(cin >> a)){
		cin.clear();
		cin.ignore();
		cout << "Please input a correct choice \n";
	}
	cout << "Enter the tempreature: ";
	if(!(cin >> b)){
		cin.clear();
		cin.ignore();
		cout << "Please input a correct value \n";
	}
}

void convert_c_f(double a)
{
	double f = (a*9.0)/5.0+32.0;
	cout << "Your tempreature is: " << f << "Fahrenheit" << "\n";
}

void convert_f_c(double a)
{
	double c = 5.0*(a-32.0)/9.0;
	cout << "Your tempreature is: " << c << "Celsuis" << "\n";
}

int main()
{
	int main_choice;
	while(1)
	{
		menu(main_choice);
		// option-1 (temp)
		if(main_choice == 1){
			double temp;
			int temp_choice;
			menu_temp_conversion(temp_choice, temp);
			// c to f
			if(temp_choice == 1){
				convert_c_f(temp);
			}
			// f to c
			if(temp_choice == 2){
				convert_f_c(temp);
			}

		}
	}
	cout << endl;

}