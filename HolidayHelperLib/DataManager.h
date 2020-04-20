#pragma once
#include "Common.h"
#include "SerializableVector.h"
#include "Location.h"
#include "Activity.h"
#include "User.h"
#include "Customer.h"
#include "Estimate.h"
#include "EstimateView.h"
#include "ObjectLink.h"
#include "Dataset.h"
#include <map>

using std::map;

using HolidayHelper::Persistence::ISerializable;
using HolidayHelper::Persistence::SerializableGuid;
using HolidayHelper::Persistence::SerializableVector;


namespace fs = std::filesystem;

namespace HolidayHelper::Data
{
	//I regret this way of managing the data. Next time I'll do persistence via a homemade JSON lib
	//And this madness will no longer be necesary
	class DllExport DataManager : public ISerializable
	{
	public:
		DataManager() {};
		//Destructor to clear all loaded data
		~DataManager();

		//Persistence methods
		void Save(fs::path filePath);
		void Load(fs::path filePath);
		//Use the same path from the most recent load and update the stored dataset
		void Update();

		void SetUpdatePath(fs::path filePath);

		//Simple Data Getters
		shared_ptr<User> FindUser(string UserName);
		shared_ptr<Location> GetLocation(GUID LocationId);
		shared_ptr<Activity> GetActivity(GUID ActivityId);
		shared_ptr<User> GetUser(GUID UserId);
		shared_ptr<Estimate> GetEstimate(GUID EstimateId);
		EstimateView GetEstimateView(GUID EstimateId);
		shared_ptr<Customer> GetCustomer(GUID CustomerId);
		DataSet<shared_ptr<Location>> GetLocations() { return static_cast<DataSet<shared_ptr<Location>>>(m_Locations); }
		DataSet<shared_ptr<Activity>> GetActivities() { return static_cast<DataSet<shared_ptr<Activity>>>(m_Activities); }

		//Data serch functions
		DataSet<shared_ptr<Activity>> GetLocationActivities(GUID LocationId, GUID CustomerId = GUID_NULL);
		DataSet<EstimateView> GetCustomerEstimates(shared_ptr<Customer> pCustomer);
		shared_ptr<Customer> GetUserCustomer(shared_ptr<User> pUser);
		DataSet<shared_ptr<Customer>> SearchCustomers(string FirstName, string LastName);

		//Data add functions
		void AddUser(shared_ptr<User> pNewUser);
		void AddEstimate(shared_ptr<Estimate> pNewEstimate);
		void AddLocation(shared_ptr<Location> pNewLocation);
		void AddLocations(vector<shared_ptr<Location>> pNewLocations);
		void AddLocationActivities(GUID LocationId, DataSet<GUID> ActivityIds);

		void AddActivity(shared_ptr<Activity> pNewActivity, vector<shared_ptr<Location>> ActivityLocations = vector<shared_ptr<Location>>());

		void AddCustomer(shared_ptr<Customer> pNewCustomer);

		std::ostream& Serialize(std::ostream& os);
		std::istream& Deserialize(std::istream& is);


	private:
		//Dynamic data loaded from disk
		SerializableVector<Location> m_Locations;
		SerializableVector<Activity> m_Activities;
		SerializableVector<User> m_Users;
		SerializableVector<Customer> m_Customers;
		SerializableVector<Estimate> m_Estimates;

		//Link data
		SerializableVector<ObjectLink> m_LocationActivities;
		SerializableVector<ObjectLink> m_CustomerEstimates;


		//Static data 

		fs::path m_UpdatePath;
	};
}