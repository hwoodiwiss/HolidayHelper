#pragma once
#include <HolidayHelperLib/Page.h>

using HolidayHelper::Presentation::Page;

class LogoutPage : public Page
{
public:
	LogoutPage();

protected:
	string Execute(string prevPage, shared_ptr<DataManager> appDataManager, shared_ptr<User>& appUser);
};

