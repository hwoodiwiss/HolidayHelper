#pragma once
#include "Common.h"
#include "SerializableVector.h"
#include "Location.h"
#include "Activity.h"
#include "User.h"
#include "ObjectLink.h"
#include <map>

using std::map;

using namespace HolidayHelper::Persistence;

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

		//Data serch functions
		shared_ptr<User> FindUser(string UserName);
		shared_ptr<Location> GetLocation(GUID LocationId);
		shared_ptr<Activity> GetActivity(GUID ActivityId);
		shared_ptr<User> GetUser(GUID UserId);

		//Data add functions
		void AddUser(shared_ptr<User> pNewUser);
		void AddLocation(shared_ptr<Location> pNewLocation);
		void AddActivity(shared_ptr<Activity> pNewActivity, vector<GUID> ActivityLocations);

		std::ostream& Serialize(std::ostream& os);
		std::istream& Deserialize(std::istream& is);

	private:
		void Update();

		//Dynamic data loaded from disk
		SerializableVector<Location> m_Locations;
		SerializableVector<Activity> m_Activities;
		SerializableVector<User> m_Users;

		//Link data
		SerializableVector<ObjectLink> m_LocationActivities;
		SerializableVector<ObjectLink> m_UserLocations;


		//Static data 

		fs::path m_UpdatePath;
	};
}