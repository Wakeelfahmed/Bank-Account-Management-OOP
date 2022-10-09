#include "Account.h"
Account::Account() :Name(""), Balance(0), isActive(0), Minimum_Balance(1000), Account_Type('S'), PIN("0000") {}
Account::Account(char Name[], string Account_Num, long double Balance, bool isActive, int Minimum_Balance, char accountType1)//Parametrized Constructor
{
	strcpy_s(this->Name, Name);
	this->Account_Num = Account_Num; this->Balance = Balance;
	this->isActive = isActive;		this->Minimum_Balance = Minimum_Balance;
	this->Account_Type = accountType1;	strcpy_s(PIN, "0000");
}
void Account::Account_Creation() {
	srand(time(0));
	cout << "Account Creation" << endl 
		<< "Note Minimum Balance limit: Current Account: Rs.5000/- \t Saving Account: Rs.1000/-";
	cout << "\nSelect Account Type" << endl;
	cout << "\'C\'. Current Account \n\'S\'. Saving Account" << endl;
	Account_Type = _getch();
	while (!(Account_Type == 's' || Account_Type == 'S' || Account_Type == 'C' || Account_Type == 'c'))
		Account_Type = _getch();
	if (is_current_or_saving_accountType())
		Minimum_Balance = 5000;
	else
		Minimum_Balance = 1000;
	cout << "AccountNo Assigned:";
	for (int i = 0; i < 10; i++)
	{
		int randomNum; char random;
		randomNum = rand() % 101;
		if (randomNum >= 50)
		{
			random = ((char)65 + rand() % 26);
			Account_Num = Account_Num + random;
			//Account_Num = Account_Num + ((char)65 + rand() % 26);
		}
		else {
			random = 48 + rand() % 10;
			Account_Num = Account_Num + random;
		}
	}
	cout << Account_Num;
	cout << "\nEnter Account Holder Name:";
	cin >> Name;
	cout << "Enter the Amount You Want To Add in account:";
	cin >> Balance;
	saving_dedution(Balance);
	set_PIN();
	cout << "PIN Assigned:" << PIN << endl;
}
void Account::set_PIN() {
	for (int i = 0; i < 4; i++)
		PIN[i] = 48 + rand() % 10;
	PIN[4] = '\0';
}
void Account::set_accountNo() {
	cout << "AccountNo:";
	cin >> Account_Num;
}
void Account::set_balance(long double a) {
	Balance = a;
}
void Account::update_balance(long double a) {
	Balance = Balance + a;
}
void Account::setisActive() {
	cout << "\nisActive:";
	isActive = _getch();
}
void Account::set_MinBalance() {
	cout << "\nMinimum Balance:";
	Minimum_Balance = _getch();
}
void Account::set_accountType() {
	cout << "\nAccountType:";
	Account_Type = _getch();
}
void Account::get() const
{
	cout << "\nACCOUNT DETAILS" << endl
		<< "AccountNo:" << Account_Num << endl
		<< "Account Holder Name:" << Name << endl
		<< "Balance:Rs." << Balance << "/-" << endl;
	if (is_Active())
		cout << "Account Status:Active" << endl;
	else
		cout << "Account Status:Dormant" << endl << "Please go to Account Management to active your account" << endl;
	cout << "Minimum Balance:Rs." << Minimum_Balance << "/-" << endl;
	if (is_current_or_saving_accountType())
		cout << "Account Type:Current Account" << endl;
	else
		cout << "Account Type:Saving Account" << endl;
}
string Account::get_AccountNo() const {
	return Account_Num;
}
char* Account::get_Account_Holder_Name() {
	return Name;
}
long double Account::get_balance()  const {
	return Balance;
}
int Account::get_minBalance() {
	if (Account_Type == 'C' || Account_Type == 'c')
		Minimum_Balance = 5000;
	else if (Account_Type == 'S' || Account_Type == 's')
		Minimum_Balance = 1000;
	return Minimum_Balance;
}
bool Account::is_current_or_saving_accountType()  const {
	if (Account_Type == 'C' || Account_Type == 'c')
		return 1;
	else if (Account_Type == 'S' || Account_Type == 's')
		return 0;
}
void Account::Deposit() {
	long double Deposit_Amount = 0, SUM = 0;
	if (Balance >= Minimum_Balance)
	{
		cout << "Enter Amount to Deposit:";
		cin >> Deposit_Amount;
		SUM = Deposit_Amount + get_balance();
		set_balance(SUM);
		cout << "Transaction Successful !!" << endl;
	}
	else
		cout << "Transaction Failed !!" << endl << "Account is Dormant" << endl;
}
char* Account::getPIN()
{
	return PIN;
}
void Account::Withdraw()
{
	int Withdraw_Amount;
	if (Balance >= Minimum_Balance)
	{
		cout << "Enter the Amount to Withdraw:";
		cin >> Withdraw_Amount;
		if (Balance >= Withdraw_Amount)
		{
			Balance = Balance - Withdraw_Amount;
			cout << "Transaction Sucessful" << endl;
		}
		else
			cout << "Transaction failed!!" << endl << "Insuffient Balance" << endl;
	}
	else
		cout << "Transaction failed!!" << endl << "Account is Dormant" << endl;
}
bool Account::is_Active() const
{
	if (Balance >= Minimum_Balance)
		return true;
	else
		return false;
}
bool Account::Suffient_Balance(long double Amount)  const
{
	if (Balance >= Amount)
		return 1;
	else
		return 0;
}
void Account::saving_dedution(long double balance) {
	if (!is_current_or_saving_accountType())
	{
		Balance = (Balance - (balance * float(float(2.5) / 100)));
		cout << "2.5% of the amount has been deducted\nNew Balance is:" << Balance << endl;
	}
}
Account::~Account() //Destructor
{
	isActive = 0; Balance = 0;
}
bool transfer(Account& source, Account& destination, long double amount)
{
	if (source.is_Active())
	{
		if (source.Suffient_Balance(amount))
		{
			source.set_balance((source.get_balance() - amount));
			destination.set_balance((destination.get_balance() + amount));
			return 1;
		}
		else
			cout << "Insufficient Balance" << endl; return 0;
	}
	else
		cout << "Inactive account" << endl; return 0;
}
void validate_Input(int start, int& input, int end) {
	while (input < start || input > end)
		input = _getch() - '0';
}
void validate_Input(int& input, int numberofaccount, Account account[]) {
	while ((input > numberofaccount || input <= 0) || (account[input].get_AccountNo() == ""))
		input = _getch();
}
void Account::read_and_store_accounts(Account AccountArray[], int& AccountCounter)
{
	string FileCheck, AccountStatus, AccountType;

	ifstream AccoutFile("AccountsSeverDataBase.txt");
	if (!AccoutFile)
	{
		cout << "Sever File Missing" << endl;
		return;
	}
	AccoutFile >> FileCheck;
	if (!(FileCheck == "SeverFile"))
	{
		cout << "Incorrect or Corrupt Sever File\n";
		return;
	}
	while (!AccoutFile.eof())
	{
		AccountCounter++;
		cout << "Reading Accountnumber" << AccountCounter << endl;
		AccoutFile >> (AccountArray[AccountCounter].Account_Num);
		cout << "Read" << endl;
		AccoutFile >> (AccountArray[AccountCounter].Name);
		AccoutFile >> (AccountArray[AccountCounter].Balance);
		AccoutFile >> AccountStatus;
		if (AccountStatus == "Active")
			AccountArray[AccountCounter].isActive = 1;
		else
			AccountArray[AccountCounter].isActive = 0;
		AccoutFile >> (AccountArray[AccountCounter].Minimum_Balance)
			>> AccountType;
		if (AccountType == "Saving")
			AccountArray[AccountCounter].Account_Type = 'S';
		else
			AccountArray[AccountCounter].isActive = 'C';
		AccoutFile >> (AccountArray[AccountCounter].PIN);
	}
	cout << "Data has been successfully Imported\n";
	AccoutFile.close();
}
void ExportAsReadable(Account A[], int num_of_Accounts) {
	ofstream Accoufile;
	Accoufile.open("AccountsDetails.txt");
	for (int i = 1; i <= num_of_Accounts; i++)
	{
		Accoufile << "Account \'" << i << "\' Details:\n";
		Accoufile << "AccountNo:" << A[i].get_AccountNo() << endl;
		Accoufile << "Account Holder Name:" << A[i].get_Account_Holder_Name() << endl;
		Accoufile << "Balance:Rs." << A[i].get_balance() << "/-\n";
		if (A[i].is_Active())
			Accoufile << "Active Status:Active\n";
		else
			Accoufile << "Active Status:Dormant\n";
		Accoufile << "Minimum Balance:Rs." << A[i].get_minBalance() << "/-\n";
		if (A[i].is_current_or_saving_accountType())
			Accoufile << "Account Type:Current Account" << endl;
		else
			Accoufile << "Account Type:Saving Account" << endl;
	}
	cout << "Data has been successfully exported\n";
}
void ExportAsBackup(Account A[], int num_of_Accounts) {
	ofstream Accoufile;
	Accoufile.open("AccountsSeverDataBase.txt");
	Accoufile << "SeverFile";
	for (int i = 1; i <= num_of_Accounts; i++)
	{
		Accoufile << endl << A[i].get_AccountNo() << endl;
		Accoufile << A[i].get_Account_Holder_Name() << endl;
		Accoufile << A[i].get_balance() << endl;
		if (A[i].is_Active())
			Accoufile << "Active\n";
		else
			Accoufile << "Dormant\n";
		Accoufile << A[i].get_minBalance() << endl;
		if (A[i].is_current_or_saving_accountType())
			Accoufile << "Current\n";
		else
			Accoufile << "Saving\n";
		Accoufile << A[i].getPIN();
	}
	cout << "Data has been successfully exported\n";
}
