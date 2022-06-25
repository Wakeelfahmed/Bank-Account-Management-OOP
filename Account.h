#include<string>
#include<iostream>
#include<ctime>
#include<conio.h>
#include<string.h>
#include<fstream>
using namespace std;
#pragma once
class Account
{
private:
	string Account_Holder_Name;
	string Account_Num; //Account Number
	long long int Balance; //Total Balance in the account
	bool isActive; //True if the account is active else false
	int Minimum_Balance; //Minimum balance that must be maintained
	char Account_Type; //'S' for saving and 'C' for current 
	char PIN[5];
public:
	Account();//Default Constructor
	Account(string, long long int, bool, int, char);//Parametrized Constructor
	void set();
	void set_PIN();
	void set_accountNo();
	void set_balance(long long int a);
	void update_balance(long long int a);
	void setisActive();
	void set_MinBalance();
	void set_accountType();
	void get();
	string get_AccountNo();
	string get_Account_Holder_Name();
	long long int get_balance();
	int get_minBalance();
	bool is_current_or_saving_accountType();
	void Deposit();
	char* getPIN();
	void Withdraw();
	bool is_Active();
	bool Suffient_Balance(long long int Amount);
	~Account();//Destructor
	void saving_dedution(long long int balance);
	void read_and_store_accounts(Account AccountArray[], int & AccountCounter);
}; //End of class
bool transfer(Account& source, Account& destination, long long int amount);
void validate_Input(int start, int& input, int accounts);
void validate_Input(int& input, int numberofaccount, Account account[]);
void ExportAsReadable(Account a[], int num_of_Accounts);
void ExportAsBackup(Account a[], int num_of_Accounts);