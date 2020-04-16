#include "ObjectLink.h"

namespace HolidayHelper::Data
{
	std::ostream& ObjectLink::Serialize(std::ostream& os)
	{
		os << m_FirstId << m_SecondId;
		return os;
	}
	std::istream& ObjectLink::Deserialize(std::istream& is)
	{
		is >> m_FirstId >> m_SecondId;
		return is;
	}
}