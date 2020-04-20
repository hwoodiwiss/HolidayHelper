#include "ManageCustomersPage.h"

ManageCustomersPage::ManageCustomersPage()
{

}

string ManageCustomersPage::Execute(string prevPage, shared_ptr<DataManager> appDataManager, shared_ptr<User>& appUser)
{
	cout << "Find A Customer To Manage:" << endl;
	shared_ptr<Customer> CurrCustomer = FindCustomer(appDataManager);
	if (CurrCustomer == nullptr) return "AdminMain";

	int userChoice = 0;
	bool userExit = false;

	while (!userExit)
	{
		cout << "Customer Management" << endl << endl;
		cout << "1. View Customer Estimates" << endl;
		cout << "2. Select a different customer" << endl;
		cout << "3. Back" << endl;
		cout << "4. Exit" << endl;
		userChoice = Input::GetUserInt();

		switch (userChoice)
		{
		case 1:
			ViewEstimates(appDataManager, CurrCustomer);
			break;
		case 2:
			return "ManageCustomers";
		case 3:
			userExit = true;
			break;
		case 4:
			return "Exit";
		default:
			cout << "Invalid option selected, please try again." << endl;
		}
	}
}

shared_ptr<Customer> ManageCustomersPage::FindCustomer(shared_ptr<DataManager> appDataManager)
{
	string FirstName = "";
	string LastName = "";
	shared_ptr<Customer> foundCustomer = nullptr;
	bool cancelSearch = false;

	while (foundCustomer == nullptr && !cancelSearch)
	{
		cout << "Customer Search (Leave all fields blank to cancel)" << endl << endl;
		cout << "Please enter the customers first name (or leave blank):" << endl;
		FirstName = Input::GetUserString();
		FirstName = Input::Trim(FirstName);

		cout << "Please enter the customers last name (or leave blank):" << endl;
		LastName = Input::GetUserString();
		LastName = Input::Trim(LastName);

		if (FirstName == "" && LastName == "")
			cancelSearch = true;

		if (!cancelSearch)
		{
			vector<shared_ptr<Customer>> foundCustomers = appDataManager->SearchCustomers(FirstName, LastName);
			int countFound = foundCustomers.size();

			cout << "Select Customer:" << endl;

			for (int index = 0; index < countFound; index++)
			{
				shared_ptr<Customer> curr = foundCustomers[index];
				cout << index + 1 << ". Acc: " << curr->GetNameCommaFull() << endl;
			}
			cout << countFound + 1 << ". Not Found (Try Again)" << endl;
			cout << countFound + 2 << ". Cancel" << endl << endl;
			int userSelection = 0;
			while (userSelection < 1 || userSelection > countFound + 2)
			{
				cout << "Please select an option:" << endl;
				userSelection = Input::GetUserInt();

				if (userSelection < 1 || userSelection > countFound + 1)
				{
					cout << "Invalid selection, please try again." << endl;
				}
			}

			if (userSelection < countFound + 1)
			{
				foundCustomer = foundCustomers[userSelection - 1];
			}
			else if (userSelection == countFound + 2)
			{
				cancelSearch = true;
			}

		}
	}

	return foundCustomer;

}

void ManageCustomersPage::ViewEstimates(shared_ptr<DataManager> appDataManager, shared_ptr<Customer> pCustomer)
{
	auto CustomerEstimates = appDataManager->GetCustomerEstimates(pCustomer);
	cout << pCustomer->GetNameCommaFull() << " Family: "
		<< pCustomer->GetNumAdults() << " Adults "
		<< pCustomer->GetNumChildren() << " Children" << endl;
	if (CustomerEstimates.size() > 0)
	{
		for (auto pEstimateView : CustomerEstimates)
		{
			cout << pEstimateView.RenderView();
		}
	}
	else
	{
		cout << "This user has not created any estimates." << endl << endl;
	}
}
