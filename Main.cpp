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
	cout << "Press 0 to Manage Account DataBase" << "\tPress 1 to Create a Account" << endl;
	UI_Input = _getch() - '0';
}
int main()
{
	int static No_of_AccountsCounter = 0;
	long long int Amount;
	char sure;
	Bank_Main_Menu();
	if (UI_Input == 0)
		validate_Input(0, UI_Input, 1);//Input validation
	while (UI_Input == 0 || UI_Input == 1 || UI_Input == 2 || UI_Input == 3 || UI_Input == 4 || UI_Input == 5)//Input 6 terminates this loop.
	{
		switch (UI_Input)
		{
		case 0:
			cout << "Press 0 to Import\tPress 1 to Export As Readable\tPress 2 to Export As Backup\n";
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
			No_of_AccountsCounter++;
			cout << "# of As:" << No_of_AccountsCounter << endl;
			A[No_of_AccountsCounter].set();
			No_of_AccountsCounter++;
			break;
		}//end of Case 1
		case 2: //Manage Accounts
		{
			for (loop = 1; loop <= No_of_AccountsCounter; loop++)
				cout << "Press \'" << loop << "\' to Manage details of " << A[loop].get_Account_Holder_Name() << endl;
			cout << "Press 0 for Main Menu\n";
			Input[1] = _getch() - '0';
			validate_Input(0, Input[1], No_of_AccountsCounter); //Input validation
			if (Input[1] == 0)
				break;
			A[Input[1]].get();
			if (!(A[Input[1]].is_Active()))
			{
				cout << "Press 0 to go to back Menu" << "\tPress 1 to active your Account";
				Input[0] = _getch() - '0';
				validate_Input(0, Input[0], 1); //Input validation
				if (Input[0] == 1)
				{
					cout << "Desposit Amount to make Account Active:";
					cin >> Amount;
					A[Input[1]].update_balance(Amount);
				}
			}
			else
			{
				cout << "Press 0 to go to back Menu" << "\tPress 1 to reset PIN" << "\tPress 2 to Close Account";
				Input[0] = _getch() - '0';
				validate_Input(0, Input[0], 2); //Input validation
				if (Input[0] == 1)//Reset PIN
				{
					A[Input[1]].set_PIN();
					cout << "New PIN is:" << A[Input[1]].getPIN() << endl;
				}
				if (Input[0] == 2) //Close Account
				{
					cout << "Are you sure you want to close your account: Press Y to proceed\\N to stop:";
					sure = _getch();
					if (sure == 'Y' || sure == 'y') //Confirmation to close Account
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
			for (loop = 1; loop <= No_of_AccountsCounter; loop++)
				cout << "Press \'" << loop << "\' to Deposit Money into " << A[loop].get_Account_Holder_Name() << endl;
			Input[1] = _getch() - '0';
			validate_Input(1, Input[1], No_of_AccountsCounter);
			A[Input[1]].Deposit();
			break;
		}//end of Case 3
		case 4: //Withdraw Money
		{
			for (loop = 1; loop <= No_of_AccountsCounter; loop++)
				cout << "Press \'" << loop << "\' to Withdraw Money from " << A[loop].get_Account_Holder_Name() << endl;
			Input[1] = _getch() - '0';
			validate_Input(1, Input[1], No_of_AccountsCounter); //Input validation
			A[Input[1]].Withdraw();
			break;
		}
		case 5: //Transfer Money
		{
			for (loop = 1; loop <= No_of_AccountsCounter; loop++)
				cout << "Press \'" << loop << "\' to Select Account " << A[loop].get_Account_Holder_Name() << endl;
			cout << "Select Account to Transfer Funds FROM:";
			Input[0] = _getch() - '0';
			validate_Input(1, Input[0], No_of_AccountsCounter); //Input validation
			cout << "Enter the 4-digit PIN to perform Transaction:";
			for (loop = 0; loop < 4; loop++)
			{
				PIN[loop] = _getch();	//User Entering PIN
				cout << "*";
			}PIN[4] = '\0';
			if (!(strcmp(A[Input[0]].getPIN(), PIN))) //PIN Matching
			{
				cout << "\nSelect Account to Transfer Amount TO:";
				Input[1] = _getch() - '0';				validate_Input(1, Input[1], No_of_AccountsCounter);//Input validation
				cout << "Enter Amount to Transfer:";
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
		cout << "\nPress 0 to Manage Account DataBase" << "\tPress 1 to Create Account\t";
		if (No_of_AccountsCounter >= 1)
		{
			cout << "Press 2 to Manage Accounts" << "\nPress 3 to Deposit Money\t"
				<< "\tPress 4 to Withdraw Money\t";
			if (No_of_AccountsCounter >= 2) cout << "Press 5 to Transfer Funds\n";
			cout << "Press 6 to Exit Program" << endl;
		}
		UI_Input = _getch() - '0';
		if (No_of_AccountsCounter == 0)
			validate_Input(0, UI_Input, 1);
		else if (No_of_AccountsCounter >= 1) {
			if (No_of_AccountsCounter < 2)
				while (UI_Input < 0 || UI_Input == 5 || UI_Input > 6)
					UI_Input = _getch() - '0';
			else
				validate_Input(0, UI_Input, 6);//Input validation
		}
	}//End of While Loop controlling switch Statement.
}
