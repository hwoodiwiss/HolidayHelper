#include "LogoutPage.h"



LogoutPage::LogoutPage()
{
}

string LogoutPage::Execute(string prevPage, shared_ptr<DataManager> appDataManager, shared_ptr<User>& appUser)
{
	appUser = nullptr;
	//Commit changes made by ther user to disk
	appDataManager->Update();
	return "Welcome";
}
