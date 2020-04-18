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