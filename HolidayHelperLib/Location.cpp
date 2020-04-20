#include "Location.h"

namespace HolidayHelper::Data
{
	shared_ptr<Location> Location::Create(string Name, float PricePerPerson, int MinTravellers)
	{
		GUID LocationId = GUID_NULL;
		if (CoCreateGuid(&LocationId) != S_OK)
		{
			return nullptr;
		}
		return shared_ptr<Location>(new Location(LocationId, Name, PricePerPerson, MinTravellers));
	}

	bool Location::IsCustomerEligible(shared_ptr<Customer> CustomerObj)
	{
		return CustomerObj->GetNumMembers() >= m_MinTravellers;
	}

	bool Location::operator==(const Location& rhs)
	{
		return (m_Id == rhs.m_Id
			&& m_Name == rhs.m_Name
			&& m_PricePerPerson == rhs.m_PricePerPerson
			&& m_MinTravellers == rhs.m_MinTravellers);
	}

	std::ostream& Location::Serialize(std::ostream& os)
	{
		os << m_Id;
		os.write(m_Name.data(), sizeof(char) * m_Name.length() + 1);
		os.write(reinterpret_cast<char*>(&m_PricePerPerson), sizeof(float));
		os.write(reinterpret_cast<char*>(&m_MinTravellers), sizeof(int));
		return os;
	}

	std::istream& Location::Deserialize(std::istream& is)
	{
		is >> m_Id;
		m_Name = InStreamToString(is);
		is.read(reinterpret_cast<char*>(&m_PricePerPerson), sizeof(float));
		is.read(reinterpret_cast<char*>(&m_MinTravellers), sizeof(int));
		return is;
	}
}