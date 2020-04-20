#include "DataManager.h"
#include <fstream>

using ifstream = std::ifstream;
using ofstream = std::ofstream;

namespace HolidayHelper::Data
{

	shared_ptr<User> DataManager::FindUser(string UserName)
	{
		User* FoundUser = nullptr;
		auto UserIterator = std::find_if(m_Users.begin(), m_Users.end(), [UserName](shared_ptr<User> pUser)->bool { return pUser->GetUsername() == UserName; });
		if (UserIterator == m_Users.end())
			return nullptr;

		return *UserIterator;
	}

	shared_ptr<Location> DataManager::GetLocation(GUID LocationId)
	{
		auto findIter = std::find_if(m_Locations.begin(), m_Locations.end(), [LocationId](shared_ptr<Location> pLocation)->bool { return pLocation->GetId() == LocationId; });
		if (findIter != m_Locations.end())
		{
			return *findIter;
		}

		return nullptr;
	}

	shared_ptr<Activity> DataManager::GetActivity(GUID ActivityId)
	{
		auto findIter = std::find_if(m_Activities.begin(), m_Activities.end(), [ActivityId](shared_ptr<Activity> pActivity)->bool { return pActivity->GetId() == ActivityId; });
		if (findIter != m_Activities.end())
		{
			return *findIter;
		}

		return nullptr;
	}	
	
	shared_ptr<User> DataManager::GetUser(GUID UserId)
	{
		auto findIter = std::find_if(m_Users.begin(), m_Users.end(), [UserId](shared_ptr<User> pUser)->bool { return pUser->GetId() == UserId; });
		if (findIter != m_Users.end())
		{
			return *findIter;
		}

		return nullptr;
	}

	shared_ptr<Estimate> DataManager::GetEstimate(GUID EstimateId)
	{
		auto findIter = std::find_if(m_Estimates.begin(), m_Estimates.end(), [EstimateId](shared_ptr<Estimate> pEstimate)->bool { return pEstimate->GetId() == EstimateId; });
		if (findIter != m_Estimates.end())
		{
			return *findIter;
		}

		return nullptr;
	}

	DataSet<shared_ptr<Customer>> DataManager::SearchCustomers(string FirstName, string LastName)
	{
		//Transform the names to lowercase for easier comparison
		std::transform(FirstName.begin(), FirstName.end(), FirstName.begin(), ::tolower);
		std::transform(LastName.begin(), LastName.end(), LastName.begin(), ::tolower);

		DataSet<shared_ptr<Customer>> matchedCustomers;

		for (auto pCustomer : m_Customers)
		{
			string CustFName = pCustomer->GetFirstName();
			string CustLName = pCustomer->GetLastName();
			std::transform(CustFName.begin(), CustFName.end(), CustFName.begin(), ::tolower);
			std::transform(CustLName.begin(), CustLName.end(), CustLName.begin(), ::tolower);
			if (CustFName == FirstName || CustLName == LastName)
			{
				matchedCustomers.push_back(pCustomer);
			}
		}

		return matchedCustomers;
	}

	EstimateView DataManager::GetEstimateView(GUID EstimateId)
	{
		auto EstimateObj = GetEstimate(EstimateId);

		if (EstimateObj == nullptr)
			return EstimateView();

		DataSet<shared_ptr<Activity>> EstimateActivities;

		for (auto ActivityId : EstimateObj->GetActivityIds())
		{
			shared_ptr<Activity> EstimateActivity = nullptr;
			EstimateActivity = GetActivity(ActivityId);
			if (EstimateActivity != nullptr)
				EstimateActivities.push_back(EstimateActivity);
		}

		EstimateView View = EstimateView(
			EstimateObj,
			GetCustomer(EstimateObj->GetCustomerId()),
			GetLocation(EstimateObj->GetLocationId()),
			EstimateActivities
		);

		return View;
	}

	shared_ptr<Customer> DataManager::GetCustomer(GUID CustomerId)
	{
		auto findIter = std::find_if(m_Customers.begin(), m_Customers.end(), [CustomerId](shared_ptr<Customer> pCustomer)->bool { return pCustomer->GetId() == CustomerId; });
		if (findIter != m_Customers.end())
		{
			return *findIter;
		}

		return nullptr;
	}

	DataSet<shared_ptr<Activity>> DataManager::GetLocationActivities(GUID LocationId, GUID CustomerId)
	{
		DataSet<shared_ptr<Activity>> foundActivities;
		for (auto LocationActivity : m_LocationActivities)
		{
			if (LocationActivity->GetFirstId() == LocationId)
			{
				foundActivities.push_back(GetActivity(LocationActivity->GetSecondId().AsGuid()));
			}
		}

		if (CustomerId != GUID_NULL)
		{
			foundActivities = foundActivities.Where([CustomerId](shared_ptr<Activity> w) { return (!w->IsUserCreated() || w->GetCustomerId() == CustomerId); });
		}

		return foundActivities;
	}

	DataSet<EstimateView> DataManager::GetCustomerEstimates(shared_ptr<Customer> pCustomer)
	{
		DataSet<EstimateView> CustomerEstimates;

		for (auto EstimateObj : m_Estimates.Where([pCustomer](shared_ptr<Estimate> w) { return w->GetCustomerId() == pCustomer->GetId(); }))
		{
			EstimateView View = GetEstimateView(EstimateObj->GetId());

			CustomerEstimates.push_back(View);
		}

		return CustomerEstimates;
	}


	DataManager::~DataManager()
	{
		m_Activities.clear();
		m_Locations.clear();
		m_Users.clear();
		m_Customers.clear();
		m_Estimates.clear();
		m_LocationActivities.clear();
	}

	void DataManager::Save(fs::path filePath)
	{
		ofstream outStream(filePath.c_str(), std::ios::out | std::ios::trunc | std::ios::binary);
		outStream << *this;
		outStream.close();
	}

	void DataManager::Load(fs::path filePath)
	{
		m_UpdatePath = filePath;
		ifstream inStream(filePath.c_str(), std::ios::in | std::ios::binary);
		inStream >> *this;
		inStream.close();
	}


	void DataManager::AddUser(shared_ptr<User> pNewUser)
	{
		if (pNewUser != nullptr)
			m_Users.push_back(pNewUser);

	}

	void DataManager::AddEstimate(shared_ptr<Estimate> pNewEstimate)
	{
		if (pNewEstimate != nullptr)
			m_Estimates.push_back(pNewEstimate);
	}

	void DataManager::AddLocation(shared_ptr<Location> pNewLocation)
	{
		if (pNewLocation != nullptr)
			m_Locations.push_back(pNewLocation);

	}

	void DataManager::AddLocations(vector<shared_ptr<Location>> pNewLocations)
	{
		//Could just add the range to the vector, but would bypass the 
		//safety of the nullptr checking done by the AddLocation method
		for (auto location : pNewLocations)
		{
			AddLocation(location);
		}
	}

	void DataManager::AddLocationActivities(GUID LocationId, DataSet<GUID> ActivityIds)
	{
		for (auto ActivityId : ActivityIds)
		{
			m_LocationActivities.push_back(shared_ptr<ObjectLink>(new ObjectLink(LocationId, ActivityId)));
		}
	}

	void DataManager::AddActivity(shared_ptr<Activity> pNewActivity, vector<shared_ptr<Location>> ActivityLocations)
	{
		if (pNewActivity != nullptr)
		{
			m_Activities.push_back(pNewActivity);

			for (auto Location : ActivityLocations)
			{
				m_LocationActivities.push_back(shared_ptr<ObjectLink>(new ObjectLink(Location->GetId(), pNewActivity->GetId())));
			}

		}
	}

	void DataManager::AddCustomer(shared_ptr<Customer> pNewCustomer)
	{
		if (pNewCustomer != nullptr)
			m_Customers.push_back(pNewCustomer);
	}

	std::ostream& DataManager::Serialize(std::ostream& os)
	{
		os << m_Locations << m_Activities << m_Users << m_Customers << m_LocationActivities << m_Estimates;
		return os;
	}

	std::istream& DataManager::Deserialize(std::istream& is)
	{
		is >> m_Locations >> m_Activities >> m_Users >> m_Customers >> m_LocationActivities >> m_Estimates;
		return is;
	}

	void DataManager::Update()
	{
		Save(m_UpdatePath);
	}

	void DataManager::SetUpdatePath(fs::path filePath)
	{
		m_UpdatePath = filePath;
	}

	shared_ptr<Customer> DataManager::GetUserCustomer(shared_ptr<User> pUser)
	{
		if (pUser->GetUserType() != UT_CUSTOMER)
			return nullptr;
		
		auto findIter = std::find_if(m_Customers.begin(), m_Customers.end(), [pUser](shared_ptr<Customer> pCust)->bool { return pCust->GetId() == pUser->GetCustomerId(); });
		if (findIter != m_Customers.end())
		{
			return *findIter;
		}

		return nullptr;
	}

}