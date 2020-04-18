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
	class DllExport DataManager : public ISerializable
	{
	public:
		DataManager() {};
		//Destructor to clear all loaded data
		~DataManager();

		//Persistence methods
		void Save(fs::path filePath);
		void Load(fs::path filePath);

		//Simple Data Getters
		shared_ptr<User> FindUser(string UserName);
		shared_ptr<Location> GetLocation(GUID LocationId);
		shared_ptr<Activity> GetActivity(GUID ActivityId);
		shared_ptr<User> GetUser(GUID UserId);
		shared_ptr<Estimate> GetEstimate(GUID EstimateId);
		shared_ptr<Customer> GetCustomer(GUID CustomerId);

		//Data serch functions
		DataSet<shared_ptr<Activity>> GetLocationActivities(GUID LocationId);
		DataSet<EstimateView> GetCustomerEstimates(shared_ptr<Customer> pCustomer);
		shared_ptr<Customer> GetUserCustomer(shared_ptr<User> pUser);

		//Data add functions
		void AddUser(shared_ptr<User> pNewUser);

		void AddLocation(shared_ptr<Location> pNewLocation);
		void AddLocations(vector<shared_ptr<Location>> pNewLocations);

		void AddActivity(shared_ptr<Activity> pNewActivity, vector<shared_ptr<Location>> ActivityLocations = vector<shared_ptr<Location>>());

		void AddCustomer(shared_ptr<Customer> pNewCustomer);

		std::ostream& Serialize(std::ostream& os);
		std::istream& Deserialize(std::istream& is);

	private:
		void Update();

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