#include <iostream>
#include <iomanip>
#include <algorithm>
using namespace std;

//function declaration
float tableGenerator();
void search(int &);
void passInSlip(int &, int &, int &);
int menuDisplay(int &);

//global variable declaration
int menuNum, prodAmount, productsId, salesPersonsId, choice, n;
int dayNum = 0, value1, value2;
string salesPersons[] = {"Abebe", "Hana", "Dawit", "Yordanos"};
string products[] = {"Jeans", "Jackets", "T-Shirts", "Shorts", "Socks"};
int rev[5][4] = {0};
int totalRevenue[4] = {0};
int totalProduct[5] = {0};
float bonusSalary[4] = {0};
float salary[4] = {2500, 2050, 1500, 1600};

int main()
{
menu:
	menuDisplay(menuNum);

	switch (menuNum)
	{
	case 1:
		passInSlip(prodAmount, salesPersonsId, productsId);
		goto menu;
		break;
	case 2:
		tableGenerator();
		goto menu;
		break;
	case 3:
		search(choice);
		goto menu;
		break;
	case 4:
		cout << "\nThank you for using our System!" << endl;
		return 0;
	default:
		cout << "\nPlease Enter Numbers only from 1 to 4!" << endl;
		goto menu;
	}
}

//This function is Responsible for displaying the menu
int menuDisplay(int &num)
{
	cout << "\n================================" << endl;
	cout << "           ABE GARMENT" << endl;
	cout << "  SALES MANAGEMENT SYSTEM MENU" << endl;
	cout << "================================" << endl;
	cout << "\n1. Pass in a Slip" << endl;
	cout << "2. Generate a Monthly Report" << endl;
	cout << "3. Search" << endl;
	cout << "4. Exit" << endl;

	cout << "\nEnter your choice from 1 to 4: ";
	cin >> num;

	return num;
}

//This function is reponsible for receiving user input
//We assume the user enters all slips once at the end of the day.
void passInSlip(int &prodAmount, int &personId, int &productId)
{
	cout << "\nProducts List" << endl;
	cout << "---------------" << endl;
	cout << "1. Jeans" << endl;
	cout << "2. Jackets" << endl;
	cout << "3. T-Shirts" << endl;
	cout << "4. Shorts" << endl;
	cout << "5. Socks" << endl;
	while (dayNum < 1) /*Here we can change the number of days in a month by changing dayNums range. By default here number of days in a month is 1.*/
	{
		for (int i = 0; i < 4; i++)
		{
		prompt1:
			cout << "\nEnter Your Id[1-4]: ";
			cin >> personId;
			if (personId < 1 || personId > 4)
			{
				cout << "\nInvalid Id!" << endl;
				goto prompt1;
			}
			value1 = personId - 1;
			cout << "Welcome " << salesPersons[value1] << "!" << endl;
		prompt3:
			cout << "How many products did you sell today? ";
			cin >> prodAmount;
			if (prodAmount < 1 || prodAmount > 5)
			{
				cout << "\nWe only sell 5 products! Please enter numbers from 1-5!" << endl;
				goto prompt3;
			}
			for (int j = 0; j < prodAmount; j++)
			{
			prompt2:
				cout << "Enter Product Id[1-5]: ";
				cin >> productId;
				if (productId < 1 || productId > 5)
				{
					cout << "\nInvalid Product Id!" << endl;
					goto prompt2;
				}
				value2 = productId - 1;
			prompt:
				cout << "Enter the total birr value of " << products[value2] << ": ";
				cin >> rev[value2][value1];
				//checking for price errors
				if (rev[value2][value1] < 10 || rev[value2][value1] > 2500)
				{
					cout << "\nInvalid Price!" << endl;
					goto prompt;
				}
			}
		}
		dayNum++;
	}
}

//This function Generates Monthly Report Table
float tableGenerator()
{
	cout << "\n==================================================================" << endl;
	cout << "                     MONTHLY SALES REPORT" << endl;
	cout << "==================================================================" << endl;
	//Generating the Table Headers
	cout << setw(10) << " ";
	for (int i = 0; i < 4; i++)
	{
		cout << setw(10) << left << salesPersons[i];
	}
	cout << setw(10) << left << "Product Total" << endl;
	cout << "------------------------------------------------------------------" << endl;

	//This loop Generates the remaining rows with their correspinding totals
	for (int i = 0; i < 5; i++)
	{
		cout << setw(10) << left << products[i];

		for (int j = 0; j < 4; j++)
		{
			cout << setw(10) << left << rev[i][j];
			totalProduct[i] += rev[i][j];
		}
		cout << setw(10) << totalProduct[i];
		cout << endl;
	}
	cout << "------------------------------------------------------------------" << endl;

	//Generates the sum total of the columns

	cout << setw(10) << left << "Total";
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			totalRevenue[i] += rev[j][i];
		}

		cout << setw(10) << totalRevenue[i];
	}
	cout << endl;
	cout << "------------------------------------------------------------------" << endl;

	//Calculates the bonus and Displays it below the respective column totals
	cout << setw(10) << "Bonus";
	for (int i = 0; i < 4; i++)
	{
		bonusSalary[i] += totalRevenue[i] * (5.0 / 100.0);
		cout << setw(10) << left << bonusSalary[i];
	}
	cout << endl;
	cout << "==================================================================" << endl;

	//Additional feature
	//Displaying who and what was sold the greatest and the lowest
	int n = sizeof(totalRevenue) / sizeof(totalRevenue[0]);
	int n1 = sizeof(totalProduct) / sizeof(totalProduct[0]);
	int max = *max_element(totalRevenue, totalRevenue + n);
	int min = *min_element(totalRevenue, totalRevenue + n);
	int max1 = *max_element(totalProduct, totalProduct + n1);
	int min1 = *min_element(totalProduct, totalProduct + n1);

	//Determining greatest and lowest selllers for that month
	for (int i = 0; i < 4; i++)
	{
		if (max == totalRevenue[i])
		{
			cout << "\n> " << salesPersons[i] << " sold the greatest this month!" << endl;
		}
		else if (min == totalRevenue[i])
		{
			cout << "\n> " << salesPersons[i] << " sold the least this month!" << endl;
		}
	}

	//Determining greatest and lowest products sold that month
	for (int i = 0; i < 5; i++)
	{
		if (max1 == totalProduct[i])
		{
			cout << "\n> " << products[i] << " were sold the greatest this month!" << endl;
		}
		else if (min1 == totalProduct[i])
		{
			cout << "\n> " << products[i] << " were sold the least this month!" << endl;
		}
	}

	return totalRevenue[4], totalProduct[5], salesPersons[4], products[5], bonusSalary[4];
}

//This function handles the search menu
void search(int &choice)
{
srMenu:
	cout << "\n-----------------------------" << endl;
	cout << "         SEARCH MENU" << endl;
	cout << "-----------------------------" << endl;
	cout << "\n1. Search for a Salesperson" << endl;
	cout << "2. Search for a Product" << endl;
	cout << "3. Exit" << endl;
	cout << "Enter your choice from 1 to 3: ";
	cin >> choice;

	if (choice == 1)
	{
		cout << "\nEnter the SalesPerson Number[1-4]: ";
		cin >> n;
		cout << "\n"
			 << salesPersons[n - 1] << ": " << endl;
		cout << "\tSalary: " << salary[n - 1] + bonusSalary[n - 1] << endl;
		cout << "\t"
			 << "Sold " << totalRevenue[n - 1] << " birr last month." << endl;
		goto srMenu;
	}
	else if (choice == 2)
	{
		cout << "\nEnter the Product Number[1-5]: ";
		cin >> n;
		cout << "\n"
			 << products[n - 1] << ": " << endl;
		cout << "\t"
			 << "Were Sold for a total of " << totalProduct[n - 1] << " birr last month.";
		goto srMenu;
	}
	else if (choice == 3)
	{
		cout << "\nYou are back on the main menu!" << endl;
	}
	else
	{
		cout << "\nPlease enter numbers from 1-3 only!" << endl;
		goto srMenu;
	}
}
