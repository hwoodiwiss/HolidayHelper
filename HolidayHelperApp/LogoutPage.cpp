#include "LogoutPage.h"



LogoutPage::LogoutPage()
{
}

string LogoutPage::Execute(string prevPage, shared_ptr<DataManager> appDataManager, shared_ptr<User>& appUser)
{
	appUser = nullptr;
	return "Welcome";
}
