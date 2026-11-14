#include <iostream>
#include <vector>
#include <fstream>
#include <iomanip>
#include "myFileLib.h"
#include "myInputLib.h"
#include "myStringLib.h"

using namespace std;


// Features :
// 1- Display all Clients Data ✅
//     - get clients from file and fill a vector of client with them.
//     - print client info in a table.
// 2- Add new client ✅
//     - read new client's info.
//     - convert this client to line.
//     - append that line to the file.
// 3- Delete client ✅
//     - read account number of client.
//     - get clients from file and fill a vector of client with them
//     - search for client in vector, if found delete it and save new clients to file
//     - if not found tell user that client not found
// 4- Update Client info ✅
//     - read account number of client to update.
//     - if client found read new client info and replace old info with new info.
//     - if client not found tell user client not found.
//     - save new version of clients to file.
// 5- Find client by account number ✅
//     - get clients from file and fill a vector of client with them.
//     - search for the client by his/her account number in the vector.
//     - if the client exists, print his info. else print client does not exist.
// 6- Transactions
//     - Transactions menu consist of 4 options :
//          1- Deposit ✅
//              - read account number of client.
//              - search for that account, if it doesn't exist, read another account number.
//              - if it exists, read amount to deposit then add this amount to account balance of client
//              - save updates to file
//          2- Withdraw
//              - read account number of client. ✅
//              - search for that account, if it doesn't exist, read another account number. ✅
//              - if it exists, read amount of withdrawal, and check if that amount is less than the total balance. ✅
//              - if it is, read another amount of withdrawal. ✅
//              - if it is not, withdraw that amount from the account. ✅
//              - save updates to file.
//          3- Total balances
//          4- Main Menu
// 7- Manage Users
//     - List all users.
//     - Add new user.
//     - Delete user.
//     - Update user.
//     - Find user by username.
//     - Main Menu.
// 8- Logout.
//     - to log in to the system, i have to be a user (username, password, permmisions)
//     - users are stored in a file.

string Delim = "/##/";
string ClientsFile = "clients_records.txt";
string UsersFile = "users_records.txt";
enum enMainMenuOptions { eDisplayClientsInfo = 1, eAddNewClient = 2, eDeleteClient = 4, eUpdateClient = 8, eFindClient = 16, eTransactions = 32, eManageUsers = 64, eLogout = 128 };


struct stUser {
	string Username;
	string Password;
	short Permission = 0;
};
stUser LoggedinUser;
struct stClient {
	string AccountNumber;
	string PinCode;
	string Name;
	string PhoneNumber;
	float AccountBalance = 0;
};
// 1- Display all Clients Data 
//     - get clients from file and fill a vector of client with them. ✅
//     - print client info in a table. ✅
stClient SplittedLineToClient(vector<string> SplittedLine) {
	stClient Client;
	Client.AccountNumber = SplittedLine[0];
	Client.PinCode = SplittedLine[1];
	Client.Name = SplittedLine[2];
	Client.PhoneNumber = SplittedLine[3];
	Client.AccountBalance = stof(SplittedLine[4]);
	return Client;
}
vector<stClient> LoadClientsInfoFromFile(string FileName) {
	vector<stClient> vAllClients;
	fstream myFile;
	myFile.open(FileName, ios::in);
	if (myFile.is_open()) {
		stClient TempClient;
		string Line;
		vector<string> vSplittedLine;
		while (getline(myFile, Line)) {
			if (Line != "") {
				vSplittedLine = myStringLib::SplitString(Line, ::Delim);
				vAllClients.push_back(SplittedLineToClient(vSplittedLine));
			}
		}
	}
	return vAllClients;
}
void ShowAccessDenied();
void PrintAllClientsInfo() {
	enMainMenuOptions eDisplayClientsOption = enMainMenuOptions::eDisplayClientsInfo;
	if ((::LoggedinUser.Permission & eDisplayClientsOption) != eDisplayClientsOption) {
		ShowAccessDenied();
		return;
	}
	vector<stClient>vAllClients = LoadClientsInfoFromFile(::ClientsFile);
	cout << "\t\t\t Clients List (" << vAllClients.size() << ") client(s)";
	cout << "\n______________________________________________________________________________________________________________\n";
	cout << "\n| " << left << setw(18) << "Account Number  " << "| " << setw(15) << "Pin Code  " << "| " << setw(30) << "Client Name  " << "| " << setw(20) << "Phone Number  " << "| " << setw(18) << "Account Balance  \n";
	cout << "\n______________________________________________________________________________________________________________\n";
	for (stClient& Client : vAllClients) {
		cout << "\n| " << left << setw(18) << Client.AccountNumber << "| " << setw(15) << Client.PinCode << "| " << setw(30) << Client.Name << "| " << setw(20) << Client.PhoneNumber << "| " << setw(18) << Client.AccountBalance;
	}
	cout << "\n______________________________________________________________________________________________________________\n";
}
// 5- Find client by account number
//     - get clients from file and fill a vector of client with them. ✅
//     - search for the client by his/her account number in the vector. ✅
//     - if the client exists, print his info. else print client does not exist. ✅
bool IsClientFoundByAccountNumber(string AccNumber, stClient& FoundClient) {
	vector<stClient> vAllClients = LoadClientsInfoFromFile(::ClientsFile);
	for (stClient& Client : vAllClients) {
		if (Client.AccountNumber == AccNumber) {
			FoundClient = Client;
			return true;
		}
	}
	return false;
}
void PrintClientCard(stClient Client) {
	cout << "\nClient Card :\n";
	cout << "- Account Number : " << Client.AccountNumber << endl;
	cout << "- Pin Code : " << Client.PinCode << endl;
	cout << "- Name : " << Client.Name << endl;
	cout << "- Phone Number : " << Client.PhoneNumber << endl;
	cout << "- Account Balance : " << Client.AccountBalance << endl;

}
void PrintCurrentScreenHeader(string currentScreen) {
	cout << "=============================================\n";
	cout << "\t\t" << currentScreen << " Screen\n";
	cout << "=============================================\n";
}
void FindClientByAccountNumber() {
	enMainMenuOptions eFindClientOption = enMainMenuOptions::eFindClient;
	if ((::LoggedinUser.Permission & eFindClientOption) != eFindClientOption) {
		ShowAccessDenied();
		return;
	}
	PrintCurrentScreenHeader("Find Client");
	string AccNumber = myStringLib::ReadString("\nPlease enter the account number of client  ");
	stClient Client;
	if (IsClientFoundByAccountNumber(AccNumber, Client)) {
		PrintClientCard(Client);
	}
	else {
		cout << "\nClient with account number [" << AccNumber << "] was not found!!\n";
	}
}
// 2- Add new client
//     - read new client's info. ✅
//     - convert this client to line. ✅
//     - append that line to the file. ✅
stClient ReadClientInfo() {
	stClient Client;
	cout << "Enter account number : ";
	getline(cin >> std::ws, Client.AccountNumber);
	while (IsClientFoundByAccountNumber(Client.AccountNumber, Client)) {
		cout << "Client with account number (" << Client.AccountNumber << ") already exists, Enter another account number\n";
		getline(cin >> std::ws, Client.AccountNumber);
	};
	cout << "Enter pin code : ";
	getline(cin, Client.PinCode);
	cout << "Enter Name : ";
	getline(cin, Client.Name);
	cout << "Enter phone number : ";
	getline(cin, Client.PhoneNumber);
	cout << "Enter account balance : ";
	cin >> Client.AccountBalance;
	return Client;
}
string ClientToLine(stClient Client) {
	string ClientLine = "";
	ClientLine.append(Client.AccountNumber + ::Delim);
	ClientLine.append(Client.PinCode + ::Delim);
	ClientLine.append(Client.Name + ::Delim);
	ClientLine.append(Client.PhoneNumber + ::Delim);
	ClientLine.append(to_string(Client.AccountBalance));
	return ClientLine;
}
void AddNewClient() {
	enMainMenuOptions eAddClientOption = enMainMenuOptions::eAddNewClient;
	if ((::LoggedinUser.Permission & eAddClientOption) != eAddClientOption) {
		ShowAccessDenied();
		return;
	}
	PrintCurrentScreenHeader("Add New Client");
	stClient NewClient = ReadClientInfo();
	if (myFileLib::AppendLineToFile(ClientToLine(NewClient), ::ClientsFile)) {
		cout << "\nClient was added successfuly\n";
	}
}
// 3- Delete client 
//     - read account number of client. ✅
//     - get clients from file and fill a vector of client with them. ✅
//     - search for client in vector, if found delete it and save new clients to file. ✅
//     - if not found tell user that client not found. ✅
vector<stClient> ClientsAfterDeleteClientByAccountNumber(string AccNumber, vector<stClient> vClients) {
	vector<stClient> vClientsAfterDeletion;
	for (stClient& Client : vClients) {
		if (Client.AccountNumber != AccNumber) {
			vClientsAfterDeletion.push_back(Client);
		}
	}
	return vClientsAfterDeletion;
}
void SaveClientsInfoToFile(vector<stClient> vClients, string FileName) {
	fstream myFile;
	myFile.open(FileName, ios::out);
	if (myFile.is_open()) {
		for (stClient& Client : vClients) {
			myFile << ClientToLine(Client) << endl;
		}
		myFile.close();
	}
}
bool DeleteClientByAccountNumber(string AccNumber) {
	vector<stClient> vAllClients = LoadClientsInfoFromFile(::ClientsFile);
	stClient ClientToDelete;
	char Answer;
	if (IsClientFoundByAccountNumber(AccNumber, ClientToDelete)) {
		PrintClientCard(ClientToDelete);
		Answer = myStringLib::ReadChar("Are you sure you want to delete this client? (y,n) ");
		if (tolower(Answer) == 'y') {
			SaveClientsInfoToFile(ClientsAfterDeleteClientByAccountNumber(AccNumber, vAllClients), ::ClientsFile);
			return true;
		}
	}
	return false;
}
void DeleteClient() {
	enMainMenuOptions eDeleteClientOption = enMainMenuOptions::eDeleteClient;
	if ((::LoggedinUser.Permission & eDeleteClientOption) != eDeleteClientOption) {
		ShowAccessDenied();
		return;
	}
	PrintCurrentScreenHeader("Delete Client");
	string AccNumber = myStringLib::ReadString("Enter the account number of the client you want to delete?  ");
	if (DeleteClientByAccountNumber(AccNumber)) {
		cout << "\nClient was deleted successfuly\n";
	}
}
// 4- Update Client info
//     - read account number of client to update. ✅
//     - if client found read new client info and replace old info with new info. ✅
//     - if client not found tell user client not found. ✅
//     - save new version of clients to file. ✅
stClient ReadClientInfoToUpdate(string AccNumber) {
	stClient Client;
	Client.AccountNumber = AccNumber;
	Client.PinCode = myStringLib::ReadString("\nEnter the pin code  ");
	Client.Name = myStringLib::ReadString("Enter the name  ");
	Client.PhoneNumber = myStringLib::ReadString("Enter the phone number  ");
	Client.AccountBalance = stof(myStringLib::ReadString("Enter the account balance  "));
	return Client;
}
vector<stClient> ClientsAfterUpdateClientInfo(string AccNumber, vector<stClient> vClients) {
	for (stClient& Client : vClients) {
		if (Client.AccountNumber == AccNumber) {
			Client = ReadClientInfoToUpdate(AccNumber);
			return vClients;
		}
	}
	return vClients;
}
bool UpdateClientInfoByAccountNumber(string AccNumber) {
	vector<stClient> vAllClients = LoadClientsInfoFromFile(::ClientsFile);
	stClient FoundClient;
	char Answer;
	if (IsClientFoundByAccountNumber(AccNumber, FoundClient)) {
		PrintClientCard(FoundClient);
		cout << "\nAre you sure you want to update this client? (y,n)  ";
		cin >> Answer;
		if (tolower(Answer) == 'y') {
			SaveClientsInfoToFile(ClientsAfterUpdateClientInfo(AccNumber, vAllClients), ::ClientsFile);
			return true;
		}
	}
	return false;
}
void UpdateClientInfo() {
	enMainMenuOptions eUpdateClientOption = enMainMenuOptions::eUpdateClient;
	if ((::LoggedinUser.Permission & eUpdateClientOption) != eUpdateClientOption) {
		ShowAccessDenied();
		return;
	}
	PrintCurrentScreenHeader("Update Client");
	string AccNumber = myStringLib::ReadString("Enter the account number of the client you want to update?  ");
	if (UpdateClientInfoByAccountNumber(AccNumber)) {
		cout << "\nClient was updated successfuly\n";
	}
}
// 6- Transactions
//     - Transactions menu consist of 4 options :
//          1- Deposit
//              - read account number of client. ✅
//              - search for that account, if it doesn't exist, read another account number. ✅
//              - if it exists, read amount to deposit then add this amount to account balance of client. ✅
//              - save updates to file. ✅
enum enTransactionsMenuOptions { eDeposit = 1, eWithdraw, eTotalBalances, eMainMenu };
void DepositAmountToClient(float Amount, string AccNumber, vector<stClient>& vAllClients) {
	for (stClient& Client : vAllClients) {
		if (Client.AccountNumber == AccNumber) {
			Client.AccountBalance += Amount;
			break;
		}
	}
}
bool DepositByAccountNumber(string AccNumber) {
	vector<stClient> vAllClients = LoadClientsInfoFromFile(::ClientsFile);
	stClient FoundClient;
	char Answer;
	if (IsClientFoundByAccountNumber(AccNumber, FoundClient)) {
		PrintClientCard(FoundClient);
		float AmountToDeposit = myInputLib::ReadFloat("\nPlease enter the deposit amount? ");
		Answer = myStringLib::ReadChar("\nAre you sure you want to perform this transaction? (y,n) ");
		if (tolower(Answer) == 'y') {
			DepositAmountToClient(AmountToDeposit, AccNumber, vAllClients);
			SaveClientsInfoToFile(vAllClients, ::ClientsFile);
			cout << "\nDone successfuly, New balance is " << FoundClient.AccountBalance + AmountToDeposit << endl;
		}
		return true;
	}
	return false;
}
void Deposit() {
	PrintCurrentScreenHeader("Deposit");
	string AccNumber = myStringLib::ReadString("\nEnter the account number? ");
	while (!DepositByAccountNumber(AccNumber)) {
		AccNumber = myStringLib::ReadString("\nClient with account number [" + AccNumber + "] doesn't exist, Enter another one? ");
	}

}
//          2- Withdraw
//              - read account number of client. ✅
//              - search for that account, if it doesn't exist, read another account number. ✅
//              - if it exists, read amount of withdrawal, and check if that amount is less than the total balance. ✅
//              - if it is, read another amount of withdrawal. ✅
//              - if it is not, withdraw that amount from the account. ✅
//              - save updates to file.
bool WithdrawByAccountNumber(string AccNumber) {
	vector<stClient> vAllClients = LoadClientsInfoFromFile(::ClientsFile);
	stClient FoundClient;
	char Answer;
	if (IsClientFoundByAccountNumber(AccNumber, FoundClient)) {
		PrintClientCard(FoundClient);
		float WithdrawAmount = myInputLib::ReadFloat("\nEnter withdraw amount? ");
		while (WithdrawAmount > FoundClient.AccountBalance) {
			WithdrawAmount = myInputLib::ReadFloat("\nAmount Exceeds the balance, you can withdraw up to : " + to_string(FoundClient.AccountBalance) + "\nEnter another amount? ");
		}
		Answer = myStringLib::ReadChar("Are you sure you want to perform this transaction? (y,n) ");
		if (tolower(Answer) == 'y') {
			DepositAmountToClient(WithdrawAmount * -1, AccNumber, vAllClients);
			SaveClientsInfoToFile(vAllClients, ::ClientsFile);
			cout << "\nDone successfuly, New balance is " << FoundClient.AccountBalance - WithdrawAmount << endl;
			return true;
		}
	}
	return false;
}
void Withdraw() {
	PrintCurrentScreenHeader("Withdraw");
	string AccNumber = myStringLib::ReadString("\nEnter account number? ");
	while (!WithdrawByAccountNumber(AccNumber)) {
		AccNumber = myStringLib::ReadString("\nClient with account number [" + AccNumber + "] doesn't exist, Enter another one? ");
	}
}
//          3- Total balances
void PrintAllClientsBalances() {
	vector<stClient>vAllClients = LoadClientsInfoFromFile(::ClientsFile);
	float BalancesSum = 0;
	cout << "\t\t\t Clients List (" << vAllClients.size() << ") client(s)";
	cout << "\n______________________________________________________________________________________________________________\n";
	cout << "\n| " << left << setw(18) << "Account Number  " << "| " << setw(30) << "Client Name  " << "| " << setw(18) << "Account Balance  \n";
	cout << "\n______________________________________________________________________________________________________________\n";
	for (stClient& Client : vAllClients) {
		BalancesSum += Client.AccountBalance;
		cout << "\n| " << left << setw(18) << Client.AccountNumber << "| " << setw(30) << Client.Name << "| " << setw(18) << Client.AccountBalance;
	}
	cout << "\n______________________________________________________________________________________________________________\n";
	cout << "\t\t\t\tTotal Balances = " << BalancesSum << endl;
}
//          4- Main Menu
void Login();
void ShowMainMenu();
void TransactionsMenuScreen();
void GoBackToTransactionsScreen() {
	cout << "Press any key to go back to transactions menu...";
	system("pause>0");
	TransactionsMenuScreen();
}
void PerformTransactionsMenuOption(enTransactionsMenuOptions Option) {
	switch (Option) {
	case enTransactionsMenuOptions::eDeposit:
		system("cls");
		Deposit();
		GoBackToTransactionsScreen();
		break;
	case enTransactionsMenuOptions::eWithdraw:
		system("cls");
		Withdraw();
		GoBackToTransactionsScreen();
		break;
	case enTransactionsMenuOptions::eTotalBalances:
		system("cls");
		PrintAllClientsBalances();
		GoBackToTransactionsScreen();
		break;
	case enTransactionsMenuOptions::eMainMenu:
		system("cls");
		ShowMainMenu();
		break;
	}
}
void TransactionsMenuScreen() {
	enMainMenuOptions eTransactionsOption = enMainMenuOptions::eTransactions;
	if ((::LoggedinUser.Permission & eTransactionsOption) != eTransactionsOption) {
		ShowAccessDenied();
		return;
	}
	system("cls");
	cout << "=================================================\n";
	cout << "\t\tTransactions Menu Screen\n";
	cout << "=================================================\n";
	cout << "\t [1] Deposit\n";
	cout << "\t [2] Withdraw\n";
	cout << "\t [3] Total Balances\n";
	cout << "\t [4] Main Menu\n";
	cout << "=================================================\n";
	PerformTransactionsMenuOption((enTransactionsMenuOptions)myInputLib::ReadInteger("Choose what do you want to do? [1 - 4] "));
}
void ShowMainMenu();
void GoBackToMainMenu() {
	cout << "Press any key to go back to main menu...";
	system("pause>0");
	ShowMainMenu();
}
void ShowManageUsersMenu();
void GoBackToManageUsersMenu();

void ShowAccessDenied() {
	system("cls");
	cout << "\n==================================================\n";
	cout << "Access denied to this option\nContact your boss.";
	cout << "\n==================================================\n";

	GoBackToMainMenu();
}
void PerformChosenOption(enMainMenuOptions Option) {
	switch (Option) {
	case enMainMenuOptions::eDisplayClientsInfo:
		system("cls");
		PrintAllClientsInfo();
		GoBackToManageUsersMenu();
		break;
	case enMainMenuOptions::eAddNewClient:
		system("cls");
		AddNewClient();
		GoBackToMainMenu();
		break;
	case enMainMenuOptions::eDeleteClient:
		system("cls");
		DeleteClient();
		GoBackToMainMenu();
		break;

	case enMainMenuOptions::eUpdateClient:
		system("cls");
		UpdateClientInfo();
		GoBackToMainMenu();
		break;

	case enMainMenuOptions::eFindClient:
		system("cls");
		FindClientByAccountNumber();
		GoBackToMainMenu();
		break;
	case enMainMenuOptions::eTransactions:
		system("cls");
		TransactionsMenuScreen();
		GoBackToMainMenu();
		break;
	case enMainMenuOptions::eManageUsers:
		system("cls");
		ShowManageUsersMenu();
		break;
	case enMainMenuOptions::eLogout:
		system("cls");
		Login();
		break;
	}
}

void ShowMainMenu() {
	system("cls");
	cout << "=================================================\n";
	cout << "\t\tMain Menu Screen\n";
	cout << "=================================================\n";
	cout << "\t [1] Show Clients List\n";
	cout << "\t [2] Add New Client\n";
	cout << "\t [3] Delete Client\n";
	cout << "\t [4] Update Client\n";
	cout << "\t [5] Find Client By Account Number\n";
	cout << "\t [6] Transactions\n";
	cout << "\t [7] Manage Users\n";
	cout << "\t [8] Logout\n";
	cout << "=================================================\n";
	PerformChosenOption((enMainMenuOptions)int(pow(2, myInputLib::ReadInteger("Enter what do you want to do? [1 - 7] ") - 1)));
}

string UserToLine(stUser User) {
	return User.Username + "/##/" + User.Password + "/##/" + to_string(User.Permission);
}
stUser LineToUser(string Line) {
	stUser User;
	vector<string> SplittedLine = myStringLib::SplitString(Line, ::Delim);
	User.Username = SplittedLine.at(0);
	User.Password = SplittedLine.at(1);
	User.Permission = stoi(SplittedLine.at(2));
	return User;
}
// 7- Manage Users
//     - List all users.
//     - Add new user.
//     - Delete user.
//     - Update user.
//     - Find user by username.
//     - Main Menu.
vector<stUser> LoadUsersDataFromFile(string FileName) {
	fstream myFile;
	myFile.open(FileName, ios::in);
	vector<stUser> vAllUsers;
	string Line;
	if (myFile.is_open()) {
		while (getline(myFile, Line)) {
			vAllUsers.push_back(LineToUser(Line));
		}
		myFile.close();
	}
	return vAllUsers;
}
bool IsUserFoundByUsernamePassword(string Username, string Password) {
	vector<stUser> vAllUsers = LoadUsersDataFromFile(::UsersFile);
	for (stUser& User : vAllUsers) {
		if (User.Username == Username && User.Password == Password)
			return true;
	}
	return false;
}
stUser ReadFullUser() {
	stUser User;
	cout << "Enter Username? ";
	getline(cin >> ws, User.Username);
	cout << "Enter Password? ";
	getline(cin >> ws, User.Password);
	return User;
}
enum enManageUsersMenuOptions { eListUsers = 1, eAddNewUser = 2, eDeleteUser = 3, eUpdateUser = 4, eFindUser = 5, MainMenu = 6 };
void PrintAllUsersInfo() {
	vector<stUser> vAllUsers = LoadUsersDataFromFile(::UsersFile);
	cout << "\t\t\t Users List (" << vAllUsers.size() << ") user(s)";
	cout << "\n______________________________________________________________________________________________________________\n";
	cout << "\n| " << left << setw(18) << "Username  " << "| " << setw(15) << "Password  " << "| " << setw(30) << "Permission  ";
	cout << "\n______________________________________________________________________________________________________________\n";
	for (stUser& User : vAllUsers) {
		cout << "\n| " << left << setw(18) << User.Username << "| " << setw(15) << User.Password << "| " << setw(15) << User.Permission;
	}
	cout << "\n______________________________________________________________________________________________________________\n";

}


//  - Add new user.
//      - load users.
//      - read user info.
//      - add user.
//      - save users to file
bool IsUserFoundByUsername(string Username, stUser& FoundUser) {
	vector<stUser> vAllUsers = LoadUsersDataFromFile(::UsersFile);
	for (stUser& User : vAllUsers) {
		if (User.Username == Username) {
			FoundUser = User;
			return true;
		}
	}
	return false;
}
short ReadPermissions() {
	short FinalPermission = 0;
	char FullAccess = myStringLib::ReadChar("Do you want to give full access? y/n ");
	if (tolower(FullAccess) == 'y') {
		return -1;
	}
	cout << "Do you want to give access to :\n";
	char PartialPermissions = myStringLib::ReadChar("\nShow clients list? y/n ");
	if (tolower((PartialPermissions)) == 'y') {
		FinalPermission += enMainMenuOptions::eDisplayClientsInfo;
	}
	PartialPermissions = myStringLib::ReadChar("\nAdd new client? y/n ");
	if (tolower((PartialPermissions)) == 'y') {
		FinalPermission += enMainMenuOptions::eAddNewClient ;
	}
	PartialPermissions = myStringLib::ReadChar("Delete client? y/n ");
	if (tolower((PartialPermissions)) == 'y') {
		FinalPermission += enMainMenuOptions::eDeleteClient;
	}
	PartialPermissions = myStringLib::ReadChar("Update client? y/n ");
	if (tolower((PartialPermissions)) == 'y') {
		FinalPermission += enMainMenuOptions::eUpdateClient ;
	}
	PartialPermissions = myStringLib::ReadChar("Find client by account number? y/n ");
	if (tolower((PartialPermissions)) == 'y') {
		FinalPermission += enMainMenuOptions::eFindClient;
	}
	PartialPermissions = myStringLib::ReadChar("Transactions menu? y/n ");
	if (tolower((PartialPermissions)) == 'y') {
		FinalPermission += enMainMenuOptions::eTransactions;
	}
	PartialPermissions = myStringLib::ReadChar("Manage users? y/n ");
	if (tolower((PartialPermissions)) == 'y') {
		FinalPermission +=  enMainMenuOptions::eManageUsers;
	}
	return FinalPermission;
}
stUser ReadFullUserInfo() {
	stUser User;
	User.Username = myStringLib::ReadString("Enter username  ");
	while (IsUserFoundByUsername(User.Username, User)) {
		User.Username = myStringLib::ReadString("[" + User.Username + "] already exists, enter another username  ");
	}
	User.Password = myStringLib::ReadString("Enter passwore  ");
	User.Permission = ReadPermissions();
	return User;
}
bool SaveUsersToFile(vector<stUser> vAllUsers) {
	fstream myFile;
	myFile.open(::UsersFile, ios::out);
	if (myFile.is_open()) {
		for (stUser& User : vAllUsers) {
			myFile << UserToLine(User) << endl;
		}
		myFile.close();
		return true;
	}
	return false;
}
void AddNewUser() {
	PrintCurrentScreenHeader("Add User");
	stUser NewUser = ReadFullUserInfo();
	vector<stUser> vAllUsers = LoadUsersDataFromFile(::UsersFile);
	vAllUsers.push_back(NewUser);
	if (SaveUsersToFile(vAllUsers)) {
		cout << "User was added successfuly\n";
	}
}
//  - Delete user.
//      - load users.
//      - read username and check if it exists.
//      - delete user and save new users to file.
void PrintUserCard(stUser User) {
	cout << "User Card:\n";
	cout << "\nUsername : " << User.Username;
	cout << "\nPassword : " << User.Password;
	cout << "\nPermission : " << User.Permission<<endl;

}
bool DeleteUserByUsername(string Username) {
	vector<stUser> vOldUsers = LoadUsersDataFromFile(::UsersFile);
	vector<stUser> vNewUsers;
	for (stUser& User : vOldUsers) {
		if (User.Username != Username) {
			vNewUsers.push_back(User);
		}
	}
	return SaveUsersToFile(vNewUsers);
}
void DeleteUser() {
	PrintCurrentScreenHeader("Delete User");
	string Username = myStringLib::ReadString("Enter Username  ");
	stUser User;
	if (Username == "Admin") {
		cout << "This User is not deletable.\n";
		return;
	}
	if (!IsUserFoundByUsername(Username, User)) {
		cout << "User with [" << Username << "] is not found\n";
		return;
	}
	PrintUserCard(User);
	char Answer = myStringLib::ReadChar("\nAre you sure you want to delete this user? (y,n)  ");
	if (tolower(Answer) == 'y') {
		if (DeleteUserByUsername(Username)) {
			cout << "User was deleted successfuly\n";
		}
	}
}
//  - Update user.
//      - load users.
//      - read username and new user info.
//      - update user and save new users to file.
bool UpdateUserByUsername(string Username) {
	vector<stUser> vAllUsers = LoadUsersDataFromFile(::UsersFile);
	for (stUser& User : vAllUsers) {
		if (User.Username == Username) {
			User.Password = myStringLib::ReadString("Enter new password  ");
			User.Permission = ReadPermissions();
		}
	}
	if (SaveUsersToFile(vAllUsers)) {
		return true;
	}
	return false;
}
void UpdateUser() {
	PrintCurrentScreenHeader("Update User");
	string Username = myStringLib::ReadString("Enter username  ");
	stUser User;
	if (!IsUserFoundByUsername(Username, User)) {
		cout << "\nUser with [" << Username << "] is not found\n";
		return;
	}
	PrintUserCard(User);
	char Answer = myStringLib::ReadChar("\nAre you sure you want to update this user? (y,n) ");
	if (tolower(Answer) == 'y') {
		if (UpdateUserByUsername(Username)) {
			cout << "User was updated successfuly\n";
		}
	}
}

//  - Find User by username.
void FindUser() {
	PrintCurrentScreenHeader("Find User");
	string Username = myStringLib::ReadString("Enter username  ");
	stUser User;
	if (IsUserFoundByUsername(Username, User)) {
		PrintUserCard(User);
	}
	else {
		cout << "User with [" << Username << "] does not exist\n";
	}
}

void GoBackToManageUsersMenu() {
	cout << "Press any key to go back to manage users menu...";
	system("pause>0");
	ShowManageUsersMenu();
}
void PerformChosenManageUsersMenuOption(enManageUsersMenuOptions Option) {
	switch (Option) {
	case enManageUsersMenuOptions::eListUsers:
		system("cls");
		PrintAllUsersInfo();
		GoBackToManageUsersMenu();
		break;
	case enManageUsersMenuOptions::eAddNewUser:
		system("cls");
		AddNewUser();
		GoBackToManageUsersMenu();
		break;
	case enManageUsersMenuOptions::eDeleteUser:
		system("cls");
		DeleteUser();
		GoBackToManageUsersMenu();
		break;
	case enManageUsersMenuOptions::eUpdateUser:
		system("cls");
		UpdateUser();
		GoBackToManageUsersMenu();
		break;
	case enManageUsersMenuOptions::eFindUser:
		system("cls");
		FindUser();
		GoBackToManageUsersMenu();
		break;
	default:
		system("cls");
		ShowMainMenu();
	}
}
void ShowManageUsersMenu() {
	enMainMenuOptions eManageUsersOption = enMainMenuOptions::eManageUsers;
	if ((::LoggedinUser.Permission & eManageUsersOption) != eManageUsersOption) {
		ShowAccessDenied();
		return;
	}
	system("cls");
	cout << "=================================================\n";
	cout << "\t\tManage Users Menu Screen\n";
	cout << "=================================================\n";
	cout << "\t [1] List Users\n";
	cout << "\t [2] Add New User\n";
	cout << "\t [3] Delete User\n";
	cout << "\t [4] Update User\n";
	cout << "\t [5] Find User By Username\n";
	cout << "\t [6] Main Menu\n";
	cout << "=================================================\n";
	PerformChosenManageUsersMenuOption((enManageUsersMenuOptions)myInputLib::ReadInteger("Choose what do you want to do? [1 - 6] "));
}
void Login() {
	PrintCurrentScreenHeader("Login");
	string Username = myStringLib::ReadString("Enter Username? ");
	string Password = myStringLib::ReadString("Enter Password? ");
	while (!IsUserFoundByUsernamePassword(Username, Password)) {
		cout << "Invalid Username/Password!\n";
		Username = myStringLib::ReadString("Enter Username? ");
		Password = myStringLib::ReadString("Enter Password? ");
	}
	IsUserFoundByUsername(Username, ::LoggedinUser);
	ShowMainMenu();
}

int main()
{
	Login();
	return 0;
}
