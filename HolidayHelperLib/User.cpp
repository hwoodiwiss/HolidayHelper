#include "User.h"

namespace HolidayHelper::Data
{
	shared_ptr<User> User::Create(string Username, string Password, bool FirstLogin, UserType Type, GUID CustomerId)
	{
		GUID UserId;
		if (CoCreateGuid(&UserId) != S_OK)
		{
			return nullptr;
		}
		return shared_ptr<User>(new User(UserId, Username, Password, FirstLogin, Type, CustomerId));
	}

	void User::ChangePassword(string NewPassword, bool FirstLogin)
	{
		m_Password = NewPassword;
		m_FirstLogin = FirstLogin;
	}

	string User::GetUserTypeString()
	{
		switch (m_Type)
		{
		case UT_NONE:
			return "None";
		case UT_CUSTOMER:
			return "Customer";
		case UT_ADMIN:
			return "Admin";
		default:
			return "None";
		}
	}

	bool User::operator==(const User& rhs)
	{
		return (m_Id == rhs.m_Id
			&& m_Username == rhs.m_Username
			&& m_Password == rhs.m_Password
			&& m_FirstLogin == rhs.m_FirstLogin
			&& m_Type == rhs.m_Type
			&& m_CustomerId == rhs.m_CustomerId);
	}

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