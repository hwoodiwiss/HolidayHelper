#include "Activity.h"

namespace HolidayHelper::Data
{



	std::ostream& Activity::Serialize(std::ostream& os)
	{
		os << m_Id;
		os.write(m_Name.data(), sizeof(char) * m_Name.length() + 1);
		os.write(reinterpret_cast<char*>(&m_PricePerPerson), sizeof(int));
		return os;
	}

	std::istream& Activity::Deserialize(std::istream& is)
	{
		is >> m_Id;
		m_Name = InStreamToString(is);
		is.read(reinterpret_cast<char*>(&m_PricePerPerson), sizeof(int));
		return is;
	}

}