#pragma once
#include "Common.h"
#include "SerializableGuid.h"

using HolidayHelper::Persistence::ISerializable;
using HolidayHelper::Persistence::SerializableGuid;


namespace HolidayHelper::Data
{

	class DllExport Location : public ISerializable
	{
	public:
		Location() { m_PricePerPerson = 0; m_MinTravellers = 0; };
		Location(GUID Id, string Name, float PricePerPerson, int MinTravellers)
			: m_Id(Id), m_Name(Name), m_PricePerPerson(PricePerPerson), m_MinTravellers(MinTravellers){}

		static shared_ptr<Location> Create(string Name, float PricePerPerson, int MinTravellers);

		SerializableGuid GetId() { return m_Id; }
		string GetName() { return m_Name; }
		int GetPricePerPerson() { return m_PricePerPerson; }
		int GetMinTravellers() { return m_MinTravellers; }

		std::ostream& Serialize(std::ostream& os);
		std::istream& Deserialize(std::istream& is);

	private:
		SerializableGuid m_Id;
		string m_Name;
		float m_PricePerPerson;
		int m_MinTravellers;
	};

}