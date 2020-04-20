#include "AdminMainPage.h"

AdminMainPage::AdminMainPage()
{
	AddPageAction(1, "ManageCustomers");
	AddPageAction(2, "ManageLocations");
	AddPageAction(3, "ManageUsers");
	AddPageAction(4, "Logout");
	AddPageAction(5, "Exit");
}

string AdminMainPage::Execute(string prevPage, shared_ptr<DataManager> appDataManager, shared_ptr<User>& appUser)
{
	int UserOption = 0;

	//Ejects users from the application if they manage to get to an authentication requiring page without logging in
	if (!IsLoggedIn(appUser))
	{
		return "Exit";
	}

	cout << "Main Menu" << endl << endl;
	cout << "Please select an option:" << endl;
	cout << "1. View Customers Estimates" << endl;
	cout << "2. Manage Locations" << endl;
	cout << "3. Manage Users" << endl;
	cout << "4. Logout" << endl;
	cout << "5. Exit" << endl;

	UserOption = GetUserPageAction();

	return m_PageActions[UserOption];
}
