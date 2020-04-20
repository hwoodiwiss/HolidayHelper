#pragma once
#include <HolidayHelperLib/Page.h>

using HolidayHelper::Presentation::Page;

class ManageCustomersPage : public Page
{
public:
	ManageCustomersPage();

protected:
	string Execute(string prevPage, shared_ptr<DataManager> appDataManager, shared_ptr<User>& appUser);

private:
	shared_ptr<Customer> FindCustomer(shared_ptr<DataManager> appDataManager);
	void ViewEstimates(shared_ptr<DataManager> appDataManager, shared_ptr<Customer> pCustomer);
};