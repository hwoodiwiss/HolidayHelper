#include "PreviousEstimatePage.h"

PreviousEstimatePage::PreviousEstimatePage()
{
	AddPageAction(1, "NewEstimate");
	AddPageAction(3, "Logout");
}

string PreviousEstimatePage::Execute(string prevPage, shared_ptr<DataManager> appDataManager, shared_ptr<User>& appUser)
{
	AddPageAction(2, prevPage);

	if (!appUser->GetUserType() == UT_CUSTOMER)
	{
		cout << "Invalid user type!" << endl 
			<< "Press enter to go back..." << endl;
		system("pause");
		return prevPage;
	}

	auto CustomerObj = appDataManager->GetCustomer(appUser->GetCustomerId());

	if (CustomerObj == nullptr)
	{
		cout << "Invalid user type!" << endl
			<< "Press enter to go back..." << endl;
		system("pause");
		return prevPage;
	}

	auto CustomerEstimates = appDataManager->GetCustomerEstimates(CustomerObj);
	cout << "Prices displayed are representitive of the time at which the estimate was created!" << endl;
	cout << "We do not guarantee that prices will not differ over time." << endl << endl;

	cout << CustomerObj->GetLastName() << " Family: "
		<< CustomerObj->GetNumAdults() << " Adults "
		<< CustomerObj->GetNumChildren() << " Children" << endl;
	PrintEstimates(CustomerEstimates);
	cout << endl;

	cout << "What would you like to do now?" << endl;
	cout << "1. Create a new Estimate" << endl;
	cout << "2. Back" << endl;
	cout << "3. Logout" << endl;
	int userChoice = GetUserPageAction();

	return m_PageActions[userChoice];
}

void PreviousEstimatePage::PrintEstimates(DataSet<EstimateView> Estimates)
{
	if (Estimates.size() > 0)
	{
		for (auto Estimate : Estimates)
		{
			cout << Estimate.RenderView();
		}
	}
	else
	{
		cout << "No Estimates Found!" << endl;
	}
}
