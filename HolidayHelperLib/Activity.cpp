#include "Activity.h"

namespace HolidayHelper::Data
{



	shared_ptr<Activity> Activity::Create(string Name, float PricePerPerson, bool UserCreated, GUID CustomerId)
	{
		GUID ActivityId;
		if (CoCreateGuid(&ActivityId) != S_OK)
		{
			return nullptr;
		}
		return shared_ptr<Activity>(new Activity(ActivityId, Name, PricePerPerson, UserCreated, CustomerId));
	}

	std::ostream& Activity::Serialize(std::ostream& os)
	{
		os << m_Id;
		os.write(m_Name.data(), sizeof(char) * m_Name.length() + 1);
		os.write(reinterpret_cast<char*>(&m_PricePerPerson), sizeof(int));
		os.write(reinterpret_cast<char*>(&m_UserCreated), sizeof(bool));
		os << m_CustomerId;
		return os;
	}

	std::istream& Activity::Deserialize(std::istream& is)
	{
		is >> m_Id;
		m_Name = InStreamToString(is);
		is.read(reinterpret_cast<char*>(&m_PricePerPerson), sizeof(int));
		is.read(reinterpret_cast<char*>(&m_UserCreated), sizeof(bool));
		is >> m_CustomerId;
		return is;
	}

}