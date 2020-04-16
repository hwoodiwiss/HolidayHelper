#include "User.h"

namespace HolidayHelper::Data
{
	std::ostream& User::Serialize(std::ostream& os)
	{
		os << m_Id;
		os.write(m_Username.data(), sizeof(char) * m_Username.length() + 1);
		os.write(m_Password.data(), sizeof(char) * m_Password.length() + 1);
		os.write(reinterpret_cast<char*>(&m_FirstLogin), sizeof(bool));
		os.write(reinterpret_cast<char*>(&m_Type), sizeof(UserType));
		os << m_CustomerId;
		return os;
	}
	std::istream& User::Deserialize(std::istream& is)
	{
		is >> m_Id;
		m_Username = InStreamToString(is);
		m_Password = InStreamToString(is);
		is.read(reinterpret_cast<char*>(&m_FirstLogin), sizeof(bool));
		m_Type = UTFromStream(is);
		is >> m_CustomerId;
		return is;
	}
	UserType User::UTFromStream(std::istream& is)
	{
		UserType eType;
		int inVal = 0;
		is.read(reinterpret_cast<char*>(&inVal), sizeof(UserType));
		if (inVal > 0 && inVal <= 2)
		{
			eType = static_cast<UserType>(inVal);
		}
		else
		{
			eType = UT_NONE;
		}
		return eType;
	}
}