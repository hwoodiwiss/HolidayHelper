#pragma once
#include <HolidayHelperLib/Page.h>

using HolidayHelper::Presentation::Page;

class AdminMainPage : public Page
{
public:
	AdminMainPage();

protected:
	string Execute(string prevPage, shared_ptr<DataManager> appDataManager, shared_ptr<User>& appUser);

};