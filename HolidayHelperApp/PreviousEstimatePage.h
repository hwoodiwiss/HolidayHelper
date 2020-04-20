#pragma once
#include <HolidayHelperLib/Page.h>
#include <HolidayHelperLib/FinanceCalculations.h>

using HolidayHelper::Presentation::Page;
using HolidayHelper::Logic::FinancialCalculations;

class PreviousEstimatePage : public Page
{
public:
    PreviousEstimatePage();

protected:
    string Execute(string prevPage, shared_ptr<DataManager> appDataManager, shared_ptr<User>& appUser);

private:
    void PrintEstimates(DataSet<EstimateView> Estimates);
};
