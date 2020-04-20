#pragma once
#include "Common.h"
#include "SerializableGuid.h"

using HolidayHelper::Persistence::ISerializable;
using HolidayHelper::Persistence::SerializableGuid;

namespace HolidayHelper::Data
{
	class DllExport Customer : public ISerializable
	{
	public:
		Customer() : m_Id(GUID_NULL), m_NumAdults(0), m_NumChildren(0) {}
		Customer(GUID Id, string FirstName, string LastName, int NumAdults, int NumChildren)
			: m_Id(Id), m_FirstName(FirstName), m_LastName(LastName), m_NumAdults(NumAdults), m_NumChildren(NumChildren) {}

		static shared_ptr<Customer> Create(string FirstName, string LastName, int NumAdults, int NumChildren);

		SerializableGuid GetId() { return m_Id; }
		string GetFirstName() { return m_FirstName; }
		string GetLastName() { return m_LastName; }
		string GetFullName() { return m_FirstName + " " + m_LastName; }
		string GetNameCommaFull() { return m_LastName + ", " + m_FirstName; }
		int GetNumAdults() { return m_NumAdults; }
		int GetNumChildren() { return m_NumChildren; }
		int GetNumMembers() { return m_NumAdults + m_NumChildren; }
		bool IsDiscountEligible();

		bool operator==(const Customer& rhs);

		std::ostream& Serialize(std::ostream& os);
		std::istream& Deserialize(std::istream& is);
	private:
		SerializableGuid m_Id;
		string m_FirstName;
		string m_LastName;
		int m_NumAdults;
		int m_NumChildren;
	};
}