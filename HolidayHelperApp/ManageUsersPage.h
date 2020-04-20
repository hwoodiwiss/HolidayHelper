#pragma once
#include <HolidayHelperLib/Page.h>

using HolidayHelper::Presentation::Page;

class ManageUsersPage : public Page
{
public:
	ManageUsersPage();

protected:
	string Execute(string prevPage, shared_ptr<DataManager> appDataManager, shared_ptr<User>& appUser);

private:
	void AddUser(shared_ptr<DataManager> appDataManager, shared_ptr<User> appUser);
	void ResetPassword(shared_ptr<DataManager> appDataManager, shared_ptr<User> appUser);
};