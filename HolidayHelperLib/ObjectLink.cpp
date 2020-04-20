#include "ObjectLink.h"

namespace HolidayHelper::Data
{
	bool ObjectLink::operator==(const ObjectLink& rhs)
	{
		return (m_FirstId == rhs.m_FirstId
			&& m_SecondId == rhs.m_SecondId);
	}
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