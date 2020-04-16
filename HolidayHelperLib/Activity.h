#pragma once
#include "Common.h"
#include "SerializableGuid.h"

using namespace HolidayHelper::Persistence;

namespace HolidayHelper::Data
{

	class DllExport Activity : public ISerializable
	{
	public:
		Activity() {}
		Activity(GUID Id, string Name, float PricePerPerson)
			: m_Id(Id), m_Name(Name), m_PricePerPerson(PricePerPerson){}

		SerializableGuid GetId() { return m_Id; }
		string GetName() { return m_Name; }
		float GetPricePerPerson() { return m_PricePerPerson; }

		std::ostream& Serialize(std::ostream& os);
		std::istream& Deserialize(std::istream& is);

	private:
		SerializableGuid m_Id;
		string m_Name;
		float m_PricePerPerson;
	};

}