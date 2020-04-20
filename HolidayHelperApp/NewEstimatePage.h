#pragma once
#include <HolidayHelperLib/Page.h>
#include <HolidayHelperLib/FinanceCalculations.h>

using HolidayHelper::Presentation::Page;
using HolidayHelper::Logic::FinancialCalculations;

class NewEstimatePage : public Page
{
public:
    NewEstimatePage();

protected:
    string Execute(string prevPage, shared_ptr<DataManager> appDataManager, shared_ptr<User>& appUser);

private:
    void AddNewActivity(DataSet<shared_ptr<Activity>>& ActivityList, shared_ptr<Location> Location, shared_ptr<DataManager> appDataManager, shared_ptr<User> appUser);
};
