#include<iostream>
#include<ctime>
#include<conio.h>
#include<string>
#include<string.h>
#include"Account.h"
using namespace std;
Account A[50]; //Global (class)Account Object array.
int UI_Input = 0, loop = 1, Input[2];
char PIN[5];
void Bank_Main_Menu() {
	cout << "Welcome to Bank Account Management System" << endl;
	cout << "0. Manage Account DataBase" << "\t1. Create a Account" << endl;
	UI_Input = _getch() - '0';
}
int main()
{
	int static No_of_AccountsCounter = 0;
	long double Amount;
	char sure;
	Bank_Main_Menu();
	if (UI_Input == 0)
		validate_Input(0, UI_Input, 1);//Input validation
	while (UI_Input == 0 || UI_Input == 1 || UI_Input == 2 || UI_Input == 3 || UI_Input == 4 || UI_Input == 5)//Input 6 terminates this loop.
	{
		switch (UI_Input)
		{
		case 0:
			system("CLS");
			cout << "0. Import\t1. Export As Readable\t2. Export As Backup\n";
			Input[0] = _getch() - '0';
			if (Input[0] == 0)
				A[0].read_and_store_accounts(A, No_of_AccountsCounter);
			else if (Input[0] == 1)
				ExportAsReadable(A, No_of_AccountsCounter);
			else if (Input[0] == 2)
				ExportAsBackup(A, No_of_AccountsCounter);
			break;
		case 1: //Create Account
		{
			system("CLS");
			No_of_AccountsCounter++;
			cout << "# of As:" << No_of_AccountsCounter << endl;
			A[No_of_AccountsCounter].Account_Creation();
			//No_of_AccountsCounter++;
			break;
		}//end of Case 1
		case 2: //Manage Accounts
		{
			system("CLS");
			cout << "Select Account To Manage" << endl;
			cout << "Account exsiting:" << No_of_AccountsCounter << endl;
			for (loop = 1; loop <= No_of_AccountsCounter; loop++)
				cout << loop << "\. " << A[loop].get_Account_Holder_Name() << endl;
			cout << "0. for Main Menu\n";
			Input[1] = _getch() - '0';
			validate_Input(0, Input[1], No_of_AccountsCounter); //Input validation
			if (Input[1] == 0)
				break;
			A[Input[1]].get();
			if (!(A[Input[1]].is_Active()))
			{
				cout << "0. Back Menu" << "\t1. Activate Account" << endl;
				Input[0] = _getch() - '0';
				validate_Input(0, Input[0], 1); //Input validation
				if (Input[0] == 1)
				{
					cout << "Desposit Amount to Activate Account:";
					cin >> Amount;
					A[Input[1]].update_balance(Amount);
				}
			}
			else
			{
				cout << "0. Back To Menu" << "\t\t1. Reset PIN" << "\t2. Close Account" << endl;
				Input[0] = _getch() - '0';
				validate_Input(0, Input[0], 2); //Input validation
				if (Input[0] == 1)//Reset PIN
				{
					A[Input[1]].set_PIN();
					cout << "New PIN is:" << A[Input[1]].getPIN() << endl;	//To remove
				}
				if (Input[0] == 2) //Close Account
				{
					cout << "Are you sure you want to close your account?: Y. proceed\\N. stop:";
					sure = _getch();
					if (sure == 'Y' || sure == 'y') //Confirmation. close Account
					{
						A[Input[1]].~Account(); //To Delete an account.
						for (loop = Input[1]; loop < No_of_AccountsCounter; loop++)
						{
							cout << "\t loop is:" << loop << endl;
							A[loop] = A[loop + 1];
							cout << "A[loop] = A[loop + 1]\n";
							A[loop + 1].~Account(); //To Delete an account.
						}
						No_of_AccountsCounter--;
					}
				}
			}
			break;
		}//end of Case 2
		case 3: //Deposit Money
		{
			system("CLS");
			cout << "Select Account To Deposit Money To" << endl;
			for (loop = 1; loop <= No_of_AccountsCounter; loop++)
				cout << loop << ". Deposit Money into " << A[loop].get_Account_Holder_Name() << endl;
			Input[1] = _getch() - '0';
			validate_Input(1, Input[1], No_of_AccountsCounter);
			A[Input[1]].Deposit();
			break;
		}//end of Case 3
		case 4: //Withdraw Money
		{
			system("CLS");
			cout << "Select Account To Withdraw Money From" << endl;
			for (loop = 1; loop <= No_of_AccountsCounter; loop++)
				cout << loop << ". " << A[loop].get_Account_Holder_Name() << endl;
			Input[1] = _getch() - '0';
			validate_Input(1, Input[1], No_of_AccountsCounter); //Input validation
			A[Input[1]].Withdraw();
			break;
		}
		case 5: //Transfer Money
		{
			system("CLS");
			for (loop = 1; loop <= No_of_AccountsCounter; loop++)
				cout << "\'" << loop << "\'. Select Account " << A[loop].get_Account_Holder_Name() << endl;
			cout << "Select Account. Transfer Funds FROM:";
			Input[0] = _getch() - '0';
			validate_Input(1, Input[0], No_of_AccountsCounter); //Input validation
			cout << "Enter the 4-digit PIN. perform Transaction:";
			for (loop = 0; loop < 4; loop++)
			{
				PIN[loop] = _getch();	//User Entering PIN
				cout << "*";
			}PIN[4] = '\0';
			if (!(strcmp(A[Input[0]].getPIN(), PIN))) //PIN Matching
			{
				cout << "\nSelect Account. Transfer Amount TO:";
				Input[1] = _getch() - '0';				validate_Input(1, Input[1], No_of_AccountsCounter);//Input validation
				cout << "Enter Amount. Transfer:";
				cin >> Amount;
				if (transfer(A[Input[0]], A[Input[1]], Amount)) //transfer() function returns bool(1/0).
					cout << "Transaction is Sucessful" << endl;
				else
					cout << "Transaction is unSuccessful" << endl;
			}
			else
				cout << "\nInvalid PIN";
			break;
		}
		}//End of switch Statement.
		cout << "\n0. Manage Account DataBase" << "\t1. Create Account\t";
		if (No_of_AccountsCounter >= 1)
		{
			cout << "2. Manage Accounts" << "\n3. Deposit Money\t"
				<< "\t4. Withdraw Money\t";
			if (No_of_AccountsCounter >= 2)
				cout << "5. Transfer Funds\n";

			cout << "6. Exit Program" << endl;
		}
		UI_Input = _getch() - '0';
		if (No_of_AccountsCounter == 0)
			validate_Input(0, UI_Input, 1);//Import and creation allowed only
		else if (No_of_AccountsCounter >= 1)
			if (No_of_AccountsCounter < 2)
				while (UI_Input < 0 || UI_Input == 5 || UI_Input > 6) //Can't Transfer
					UI_Input = _getch() - '0';
			else
				validate_Input(0, UI_Input, 6);//Input validation for all options

	}//End of While Loop controlling switch Statement.
}
