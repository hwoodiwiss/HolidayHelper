#include "NewEstimatePage.h"

#ifdef min
#undef min
#endif

NewEstimatePage::NewEstimatePage()
{
}

string NewEstimatePage::Execute(string prevPage, shared_ptr<DataManager> appDataManager, shared_ptr<User>& appUser)
{

	if (!appUser->GetUserType() == UT_CUSTOMER)
	{
		cout << "Invalid user type!" << endl
			<< "Press enter to go back..." << endl;
		system("PAUSE");
		return prevPage;
	}

	auto CustomerObj = appDataManager->GetCustomer(appUser->GetCustomerId());

	if (CustomerObj == nullptr)
	{
		cout << "Invalid user type!" << endl
			<< "Press enter to go back..." << endl;
		system("PAUSE");
		return prevPage;
	}

	auto EligibleLocations = appDataManager->GetLocations().Where(
		[CustomerObj](shared_ptr<Location> w)
		{
			return w->IsCustomerEligible(CustomerObj);
		}
	);

	int NumEligible = EligibleLocations.size();

	if (NumEligible == 0)
	{
		cout << "Unfortunately, you do not meet the minimum required number" << endl
			<< "of travellers for any of our holiday locations." << endl << endl;

		cout << "Press any key to return to the previous menu." << endl;
		system("pause");
		return prevPage;
	}

	shared_ptr<Location> SelectedLocation;
	DataSet<shared_ptr<Activity>> SelectedActivities;
	int UserSelection = 0;
	bool UserCancelled = false;

	cout << endl << "New Estimate" << endl << endl;
	while (UserSelection < 1 || UserSelection > NumEligible + 1)
	{
		cout << "Here are the locations that are available to your family:" << endl;
		for (int index = 0; index < NumEligible; index++)
		{
			shared_ptr<Location> EligibleLocation = EligibleLocations[index];
			cout << index + 1 << ". " << EligibleLocation->GetName() << " ("
				<< char(156) << std::setprecision(2) << std::fixed 
				<< EligibleLocation->GetPricePerPerson() << "/person)" << endl;
		}
		cout << NumEligible + 1 << ". Cancel" << endl << endl;
		cout << "Please select a location:" << endl;

		UserSelection = Input::GetUserInt();

		if (UserSelection < 1 || UserSelection > NumEligible + 1)
		{
			cout << "Invalid selection. Please try again." << endl;
		}
	}

	if (UserSelection < NumEligible + 1)
	{
		SelectedLocation = EligibleLocations[UserSelection - 1];
	}
	else
	{
		return prevPage;
	}

	//Reset UserSelection to 0 for re-use
	UserSelection = 0;

	auto LocationActivities = appDataManager->GetLocationActivities(SelectedLocation->GetId().AsGuid(), CustomerObj->GetId().AsGuid());
	DataSet<int> ActivitySelections;

	cout << endl << "Select Activities:" << endl << endl;
	while (ActivitySelections.size() == 0)
	{
		int NumActivities = LocationActivities.size();

		cout << "Here are the activities that are available at that location:" << endl;
		for (int index = 0; index < NumActivities; index++)
		{
			shared_ptr<Activity> ActivityObj = LocationActivities[index];
			cout << index + 1 << ". " << ActivityObj->GetName() 
				<< " ("
				<< char(156) << std::setprecision(2) << std::fixed
				<< ActivityObj->GetPricePerPerson() << "/person)"
				<< endl;
		}
		cout << NumActivities + 1 << ". New" << endl;
		cout << NumActivities + 2 << ". Cancel" << endl << endl;
		cout << "Please note, [New] and [Cancel] will override any other choice" << endl;
		cout << "Please select any activities you wish to do (Separated with commas):" << endl;

		ActivitySelections = DataSet<int>(Input::GetUserIntArray());

		if (ActivitySelections.Contains(NumActivities + 2)) //Cancel
		{
			return prevPage;
		}
		else if (ActivitySelections.Contains(NumActivities + 1)) //Add new
		{
			AddNewActivity(LocationActivities, SelectedLocation, appDataManager, appUser);
			ActivitySelections.clear();
		}
		else if(ActivitySelections.Where([NumActivities](int w) {return ((w < 1) || (w > NumActivities + 2)); }).size() > 0) //Check is in bounds
		{
			cout << "Some selections where out of bounds." << endl;
			cout << "Please try again." << endl;
			ActivitySelections.clear();
		}
	}

	SerializableVector<SerializableGuid> SelectedActivityIds;
	DataSet<shared_ptr<Activity>> SelectedActivityObjs;

	for (int Choice : ActivitySelections)
	{
		shared_ptr<Activity> SelectedActivity = LocationActivities[Choice - 1];
		shared_ptr<SerializableGuid> ActId = shared_ptr<SerializableGuid>(new SerializableGuid(SelectedActivity->GetId().AsGuid()));
		SelectedActivityObjs.push_back(SelectedActivity);
		SelectedActivityIds.push_back(ActId);
	}

	float BasicCost = FinancialCalculations::GetBasicCost(CustomerObj, SelectedLocation, SelectedActivityObjs);
	
	//If Eligible, apply 10% discount
	if (CustomerObj->IsDiscountEligible())
	{
		BasicCost = FinancialCalculations::ApplyDiscount(BasicCost, 10);
	}

	auto NewEstimate = Estimate::Create(CustomerObj->GetId().AsGuid(), SelectedLocation->GetId().AsGuid(), SelectedActivityIds, BasicCost);

	appDataManager->AddEstimate(NewEstimate);
	appDataManager->Update();
	
	cout << string(118, '_') << endl;
	EstimateView EstimateViewObj = appDataManager->GetEstimateView(NewEstimate->GetId());
	cout << CustomerObj->GetLastName() << " Family: "
		<< CustomerObj->GetNumAdults() << " Adults "
		<< CustomerObj->GetNumChildren() << " Children" << endl;
	cout << EstimateViewObj.RenderView();

	cout << "Estimate created and stored!" << endl;
	cout << "Press any key to return to the previous menu!" << endl;
	system("pause");

	return prevPage;
}

void NewEstimatePage::AddNewActivity(DataSet<shared_ptr<Activity>>& ActivityList, shared_ptr<Location> Location, shared_ptr<DataManager> appDataManager, shared_ptr<User> appUser)
{
	cout << endl << "New Activity" << endl << endl;

	auto CustomerObj = appDataManager->GetCustomer(appUser->GetCustomerId());

	string ActivityName = "";
	float ActivityPrice = std::numeric_limits<float>::lowest();

	while (ActivityName == "")
	{
		cout << "What is the name of the activity you would like to add?" << endl;
		ActivityName = Input::GetUserString();
	}

	while (ActivityPrice < 0.0f)
	{
		cout << "How much do you estimate this to cost (per person)?" << endl;
		ActivityPrice = Input::GetUserFloat();
	}

	auto newActivity = Activity::Create(ActivityName, ActivityPrice, true, (CustomerObj != nullptr ? CustomerObj->GetId().AsGuid() : GUID_NULL));
	appDataManager->AddActivity(newActivity, { Location });

	appDataManager->Update(); //Persist the new activity to disk

	ActivityList.push_back(newActivity);
}

