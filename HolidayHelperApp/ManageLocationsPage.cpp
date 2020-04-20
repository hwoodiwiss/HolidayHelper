#include "ManageLocationsPage.h"

ManageLocationsPage::ManageLocationsPage()
{
}

string ManageLocationsPage::Execute(string prevPage, shared_ptr<DataManager> appDataManager, shared_ptr<User>& appUser)
{
	int userChoice = 0;
	bool userExit = false;

	while (!userExit)
	{
		cout << "Location Management" << endl << endl;
		cout << "1. Add Location" << endl;
		cout << "2. Update Location" << endl;
		cout << "3. Back" << endl;
		cout << "4. Exit" << endl;
		userChoice = Input::GetUserInt();

		switch (userChoice)
		{
		case 1:
			AddLocation(appDataManager);
			break;
		case 2:
			UpdateLocation(appDataManager);
			break;
		case 3:
			return prevPage;
		case 4:
			return "Exit";
		default:
			cout << "Invalid option selected, please try again." << endl;
		}
	}
}

void ManageLocationsPage::AddLocation(shared_ptr<DataManager> appDataManager)
{
	string LocationName = "";
	int MinTravellers = -1;
	float PricePerPerson = -1;
	cout << "Create Location" << endl << endl;

	while (LocationName == "")
	{
		cout << "Please enter the locations name:" << endl;
		LocationName = Input::Trim(Input::GetUserString());
	}

	while (MinTravellers < 0)
	{
		cout << "Please enter the locations minimum travellers:" << endl;
		MinTravellers = Input::GetUserInt();
	}

	while (PricePerPerson < 0)
	{
		cout << "Please enter the locations Price per Person:" << endl;
		PricePerPerson = Input::GetUserFloat();
	}

	auto pActivities = appDataManager->GetActivities().Where([](shared_ptr<Activity> w) { return w->IsUserCreated() == false; });

	DataSet<int> ActivitySelections;

	cout << endl << "Select Activities:" << endl << endl;
	while (ActivitySelections.size() == 0)
	{
		int NumActivities = pActivities.size();

		cout << "Here are the activities that are available at that location:" << endl;
		for (int index = 0; index < NumActivities; index++)
		{
			shared_ptr<Activity> ActivityObj = pActivities[index];
			cout << index + 1 << ". " << ActivityObj->GetName()	<< endl;
		}
		cout << "Please select any activities you wish to do (Separated with commas):" << endl;

		ActivitySelections = DataSet<int>(Input::GetUserIntArray());

		if (ActivitySelections.Where([NumActivities](int w) {return ((w < 1) || (w > NumActivities + 2)); }).size() > 0) //Check is in bounds
		{
			cout << "Some selections where out of bounds." << endl;
			cout << "Please try again." << endl;
			ActivitySelections.clear();
		}
	}

	DataSet<GUID> SelectedActivityIds;

	for (auto Choice : ActivitySelections)
	{
		shared_ptr<Activity> SelectedActivity = pActivities[Choice - 1];
		SelectedActivityIds.push_back(SelectedActivity->GetId().AsGuid());
	}

	auto newLocation = Location::Create(LocationName, PricePerPerson, MinTravellers);

	appDataManager->AddLocation(newLocation);
	appDataManager->AddLocationActivities(newLocation->GetId().AsGuid(), SelectedActivityIds);

	appDataManager->Update();

	cout << endl << "Location added successfully!" << endl << endl;
}

void ManageLocationsPage::UpdateLocation(shared_ptr<DataManager> appDataManager)
{
	auto Locations = appDataManager->GetLocations();
	int NumLocations = Locations.size();
	int UserSelection = 0;

	cout << "Locations To Manage" << endl;
	while (UserSelection < 1 || UserSelection > NumLocations + 1)
	{
		for (int index = 0; index < NumLocations; index++)
		{
			shared_ptr<Location> pLocation = Locations[index];
			cout << index + 1 << ". " << pLocation->GetName() << endl;
		}
		cout << NumLocations + 1 << ". Cancel" << endl << endl;

		cout << "Please select a location:" << endl;

		UserSelection = Input::GetUserInt();

		if (UserSelection < 1 || UserSelection > NumLocations + 1)
		{
			cout << "Invalid selection. Please try again." << endl;
		}
	}

	auto pSelLocation = Locations[UserSelection - 1];

	cout << "Leaving any field blank will retain its old value, which will be shown in brackets." << endl;

	cout << "Enter the location name: (" << pSelLocation->GetName() << ")";
	string NewName = Input::GetUserString();
	NewName = Input::Trim(NewName); //Make sure to avoid visually blank names
	if (NewName != "")
		pSelLocation->SetName(NewName);

	cout << "Enter the location minimum travellers: (" << pSelLocation->GetMinTravellers() << ")";
	string NewMin = Input::GetUserString();
	
	bool isValid = false;
	while (!isValid && NewMin != "")
	{
		if (Input::ValidateIntString(NewMin))
		{
			isValid = true;
		}

		if (!isValid)
		{
			cout << "Please enter a valid number!" << endl;
			NewMin = Input::GetUserString();
		}
	}
	if (NewMin != "")
	{
		int NewMinInt = std::stoi(NewMin);
		pSelLocation->SetMinTravellers(NewMinInt);
	}


	cout << "Enter the location price per person: (" << pSelLocation->GetPricePerPerson() << ")";
	string NewPrice = Input::GetUserString();

	isValid = false;
	while (!isValid && NewPrice != "")
	{
		if (Input::ValidateFloatString(NewPrice))
		{
			isValid = true;
		}

		if (!isValid)
		{
			cout << "Please enter a valid number!" << endl;
			NewPrice = Input::GetUserString();
		}
	}
	if (NewPrice != "")
	{
		float NewPriceFloat = std::stof(NewPrice);
		pSelLocation->SetPrice(NewPriceFloat);
	}

	cout << "Update complete: Location - " << pSelLocation->GetName() 
		<< " | MinTravelers - " << pSelLocation->GetMinTravellers() 
		<< " | Price per Person - " << pSelLocation->GetPricePerPerson() << endl;

	appDataManager->Update();

	cout << endl << "Location updated successfully!" << endl << endl;

}
