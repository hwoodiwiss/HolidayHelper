#include "CreateUserPage.h"
#include <HolidayHelperLib/Customer.h>

using HolidayHelper::Data::Customer;

CreateUserPage::CreateUserPage()
{
}

string CreateUserPage::Execute(string prevPage, shared_ptr<DataManager> appDataManager, shared_ptr<User>& appUser)
{
	//User info
	string newUsername = "";
	string newPassword = "";
	bool isUnique = false;

	//Customer info
	string FirstName;
	string LastName;
	int NumAdults = -1;
	int NumChildren = -1;

	cout << "New User" << endl << endl;

	//Uniquness validation loop
	while (!isUnique)
	{
		//Username input validation loop
		while (newUsername == "")
		{
			cout << "Please enter your desired username:" << endl;
			newUsername = Input::GetUserString();
			newUsername = Input::Trim(newUsername);
		}

		//If no user is found with this username, isUnique is true
		if (appDataManager->FindUser(newUsername) == nullptr)
		{
			isUnique = true;
		}
		else
		{
			cout << "Username already in use, please try again!" << endl;
		}
	}

	string newPasswordVerify = "";
	do
	{
		cout << "Please enter a new password: " << endl;
		newPassword = Input::GetUserString();
		cout << "Please reenter the new password: " << endl;
		newPasswordVerify = Input::GetUserString();

		if (newPassword != newPasswordVerify)
		{
			cout << "Passwords did not match!" << endl;
		}
	} while (newPassword != newPasswordVerify && newPassword == "");

	while (FirstName == "")
	{
		cout << "Please enter your first name:" << endl;
		FirstName = Input::GetUserString();
		FirstName = Input::Trim(FirstName);
	}
	
	while (LastName == "")
	{
		cout << "Please enter your surname:" << endl;
		LastName = Input::GetUserString();
		LastName = Input::Trim(LastName);
	}

	while (NumAdults < 1)
	{
		cout << "How many adults are you estimating for? (Must be at least 1, include yourself)" << endl;
		NumAdults = Input::GetUserInt();
	}

	while (NumChildren < 0)
	{
		cout << "And how many children (Under 16)? (0 for none)" << endl;
		NumChildren = Input::GetUserInt();
	}

	shared_ptr<Customer> newCust = Customer::Create(FirstName, LastName, NumAdults, NumChildren);
	auto newUser = User::Create(newUsername, newPassword, false, UT_CUSTOMER, newCust->GetId().AsGuid());

	appDataManager->AddCustomer(newCust);
	appDataManager->AddUser(newUser);

	appUser = newUser;

	cout << "New user created!" << endl;

	return "Main";
}
