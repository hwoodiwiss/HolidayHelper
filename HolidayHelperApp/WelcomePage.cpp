#include "WelcomePage.h"

WelcomePage::WelcomePage()
{
	AddPageAction(1, "Login");
	AddPageAction(2, "CreateUser");
	AddPageAction(3, "Exit");
}

string WelcomePage::Execute(string prevPage, shared_ptr<DataManager> appDataManager, shared_ptr<User>& appUser)
{
	int userChoice = 0;

	cout << "Welcome!" << endl << endl;
	cout << "Are you a new or existing user?" << endl;
	cout << "1. Existing User" << endl;
	cout << "2. New User" << endl;
	cout << "3. Exit" << endl;

	userChoice = GetUserPageAction();

	return m_PageActions[userChoice];
}
