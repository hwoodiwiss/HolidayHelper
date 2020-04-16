#include "Location.h"

namespace HolidayHelper::Data
{
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