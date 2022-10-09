#pragma once
#include<string>
#include<iostream>
#include<ctime>
#include<conio.h>
#include<string.h>
#include<fstream>
using namespace std;
class Account
{
private:
	char Name[100];			//Account Holder Name
	string Account_Num;		//Account Number
	long double Balance;	//Total Balance in the account
	bool isActive;			//True if the account is active else false
	int Minimum_Balance;	//Minimum balance that must be maintained
	char Account_Type;		//'S' for saving and 'C' for current 
	char PIN[5];
public:
	Account();//Default Constructor
	Account(char[], string, long double, bool, int, char);//Parametrized Constructor
	void Account_Creation();
	void set_PIN();
	void set_accountNo();
	void set_balance(long double a);
	void update_balance(long double a);
	void setisActive();
	void set_MinBalance();
	void set_accountType();
	void get() const;
	string get_AccountNo() const;
	char* get_Account_Holder_Name();
	long double get_balance() const;
	int get_minBalance();
	bool is_current_or_saving_accountType() const;
	void Deposit();
	char* getPIN();
	void Withdraw();
	bool is_Active() const;
	bool Suffient_Balance(long double Amount) const;
	~Account();//Destructor
	void saving_dedution(long double balance);
	void read_and_store_accounts(Account AccountArray[], int& AccountCounter);
}; //End of class
bool transfer(Account& source, Account& destination, long double amount);
void validate_Input(int start, int& input, int accounts);
void validate_Input(int& input, int numberofaccount, Account account[]);
void ExportAsReadable(Account a[], int num_of_Accounts);
void ExportAsBackup(Account a[], int num_of_Accounts);