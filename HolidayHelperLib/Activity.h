#pragma once
#include "Common.h"
#include "SerializableGuid.h"

using HolidayHelper::Persistence::ISerializable;
using HolidayHelper::Persistence::SerializableGuid;

namespace HolidayHelper::Data
{

	class DllExport Activity : public ISerializable
	{
	public:
		Activity() { m_PricePerPerson = 0.0f, m_UserCreated = false; m_CustomerId = GUID_NULL; }
		Activity(GUID Id, string Name, float PricePerPerson, bool UserCreated, GUID CustomerId = GUID_NULL)
			: m_Id(Id), m_Name(Name), m_PricePerPerson(PricePerPerson), m_UserCreated(UserCreated), m_CustomerId(CustomerId){}

		static shared_ptr<Activity> Create(string Name, float PricePerPerson, bool UserCreated, GUID CustomerId = GUID_NULL);

		SerializableGuid GetId() { return m_Id; }
		string GetName() { return m_Name; }
		float GetPricePerPerson() { return m_PricePerPerson; }
		bool IsUserCreated() { return m_UserCreated; }
		GUID GetCustomerId() { return m_CustomerId.AsGuid(); }

		bool operator==(const Activity& rhs);

		std::ostream& Serialize(std::ostream& os);
		std::istream& Deserialize(std::istream& is);

	private:
		SerializableGuid m_Id;
		string m_Name;
		float m_PricePerPerson;
		bool m_UserCreated;
		SerializableGuid m_CustomerId;
	};

}