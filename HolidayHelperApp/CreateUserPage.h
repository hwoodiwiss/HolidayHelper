#pragma once
#include <HolidayHelperLib/Page.h>

using HolidayHelper::Presentation::Page;

class CreateUserPage : public Page
{
public:
	CreateUserPage();

protected:
	string Execute(string prevPage, shared_ptr<DataManager> appDataManager, shared_ptr<User>& appUser);

};