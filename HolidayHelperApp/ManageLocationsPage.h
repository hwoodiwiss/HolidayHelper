#pragma once
#include <HolidayHelperLib/Page.h>
#include <HolidayHelperLib/Customer.h>

using HolidayHelper::Presentation::Page;
using HolidayHelper::Data::Customer;

class ManageLocationsPage : public Page
{
public:
	ManageLocationsPage();

protected:
	string Execute(string prevPage, shared_ptr<DataManager> appDataManager, shared_ptr<User>& appUser);

private:
	void AddLocation(shared_ptr<DataManager> appDataManager);
	void UpdateLocation(shared_ptr<DataManager> appDataManager);
};