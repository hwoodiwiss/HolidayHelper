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


	DataManager::~DataManager()
	{
		m_Activities.clear();
		m_Locations.clear();
		m_Users.clear();
		m_LocationActivities.clear();
		m_UserLocations.clear();
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

	void DataManager::AddLocation(shared_ptr<Location> pNewLocation)
	{
		if (pNewLocation != nullptr)
			m_Locations.push_back(pNewLocation);

	}

	void DataManager::AddActivity(shared_ptr<Activity> pNewActivity, vector<GUID> ActivityLocations)
	{
		if (pNewActivity != nullptr)
		{
			m_Activities.push_back(pNewActivity);

			for (auto LocationId : ActivityLocations)
			{
				m_LocationActivities.push_back(shared_ptr<ObjectLink>(new ObjectLink(LocationId, pNewActivity->GetId())));
			}

		}
	}

	std::ostream& DataManager::Serialize(std::ostream& os)
	{
		os << m_Locations << m_Activities << m_Users << m_LocationActivities << m_UserLocations;
		return os;
	}

	std::istream& DataManager::Deserialize(std::istream& is)
	{
		is >> m_Locations >> m_Activities >> m_Users >> m_LocationActivities >> m_UserLocations;
		return is;
	}

	void DataManager::Update()
	{
		Save(m_UpdatePath);
	}

}