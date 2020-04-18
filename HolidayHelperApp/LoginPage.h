#pragma once
#include <HolidayHelperLib/Page.h>

using HolidayHelper::Presentation::Page;

class LoginPage : public Page
{
public:
	LoginPage();

protected:
	string Execute(string prevPage, shared_ptr<DataManager> appDataManager, shared_ptr<User>& appUser);

};