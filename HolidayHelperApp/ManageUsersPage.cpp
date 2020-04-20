#include "ManageUsersPage.h"

ManageUsersPage::ManageUsersPage()
{
}

string ManageUsersPage::Execute(string prevPage, shared_ptr<DataManager> appDataManager, shared_ptr<User>& appUser)
{
	if (!IsLoggedIn(appUser))
	{
		return "Exit";
	}

	int userChoice = 0;
	bool userExit = false;

	while (!userExit)
	{
		cout << "User Administration" << endl << endl;
		cout << "1. Reset a password" << endl;
		cout << "2. Add a new user" << endl;
		cout << "3. Back" << endl;
		cout << "4. Exit" << endl;
		userChoice = Input::GetUserInt();

		switch (userChoice)
		{
		case 1:
			ResetPassword(appDataManager, appUser);
			break;
		case 2:
			AddUser(appDataManager, appUser);
			break;
		case 3:
			userExit = true;
			break;
		case 4:
			return "Exit";
		default:
			cout << "Invalid option selected, please try again." << endl;
		}
	}
	return prevPage;
}

void ManageUsersPage::AddUser(shared_ptr<DataManager> appDataManager, shared_ptr<User> appUser)
{
	//Only allow admins to perform this function
	if (appUser->GetUserType() == UT_ADMIN)
	{
		string newUsername = "";
		string newPassword = "";
		int newUserType = 0;
		bool isUnique = false;

		cout << "New User" << endl << endl;

		//Uniquness validation loop
		while (!isUnique)
		{
			//Username input validation loop
			while (newUsername == "")
			{
				cout << "Please enter the new username:" << endl;
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
				newUsername = "";
				cout << "Username already in use, please try again!" << endl;
			}
		}

		//Password input validation loop
		while (newPassword == "")
		{
			cout << "Please enter the new password (User will be prompted to change this on first login):" << endl;
			newPassword = Input::GetUserString();
			newPassword = Input::Trim(newPassword);
		}

		//Access level validation loop
		while (newUserType < 1 || newUserType > 2)
		{
			cout << "Please enter the desired access level for this user (Customer = 1, Admin = 2):" << endl;
			newUserType = Input::GetUserInt();
			if (newUserType < 1 || newUserType > 2)
			{
				cout << "Invalid value, please enter a value within the specified range." << endl;
			}
		}

		if (UserType(newUserType) == UT_CUSTOMER)
		{
			string FirstName = "";
			string LastName = "";
			int NumAdults = -1;
			int NumChildren = -1;


			while (FirstName == "")
			{
				cout << "Please enter the users first name:" << endl;
				FirstName = Input::GetUserString();
				FirstName = Input::Trim(FirstName);
			}

			while (LastName == "")
			{
				cout << "Please enter the users surname:" << endl;
				LastName = Input::GetUserString();
				LastName = Input::Trim(LastName);
			}

			while (NumAdults < 1)
			{
				cout << "How many adults will the user be estimating for? (Must be at least 1)" << endl;
				NumAdults = Input::GetUserInt();
			}

			while (NumChildren < 0)
			{
				cout << "And how many children (Under 16)? (0 for none)" << endl;
				NumChildren = Input::GetUserInt();
			}

			shared_ptr<Customer> newCust = Customer::Create(FirstName, LastName, NumAdults, NumChildren);
			auto NewUser = User::Create(newUsername, newPassword, true, UserType(newUserType), newCust->GetId().AsGuid());
			
			appDataManager->AddCustomer(newCust);
			appDataManager->AddUser(NewUser);
		}
		else
		{
			auto NewUser = User::Create(newUsername, newPassword, true, (UserType)newUserType);

			appDataManager->AddUser(NewUser);
		}
		appDataManager->Update();

		cout << "New user created!" << endl;
	}
	else
	{
		cout << "You do not have the access level required to make this change!" << endl;
	}
}

void ManageUsersPage::ResetPassword(shared_ptr<DataManager> appDataManager, shared_ptr<User> appUser)
{

	string searchUsername = "";
	shared_ptr<User> foundUser = nullptr;
	cout << "Password Reset" << endl << endl;

	while (foundUser == nullptr)
	{
		cout << "Please enter a username (or enter nothing to cancel):" << endl;
		searchUsername = Input::GetUserString();
		if (searchUsername == "")
			return;
		foundUser = appDataManager->FindUser(searchUsername);
		if (foundUser == nullptr)
		{
			cout << "No record could be found for that username!" << endl;
		}
	}

	if (appUser->GetUserType() == UT_ADMIN)
	{
		string newPassword = "";
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
		} while (newPassword != newPasswordVerify);

		//Sets the new password, and forces the user to change it on next logon if the user in question is not the current user.
		foundUser->ChangePassword(newPassword, foundUser == appUser ? false : true);
		appDataManager->Update();

		cout << "Password reset complete!" << endl;
	}
	else
	{
		cout << "You do not have permission to update this users details!" << endl;
	}
}
