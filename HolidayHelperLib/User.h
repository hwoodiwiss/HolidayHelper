#pragma once
#include "Common.h"
#include "SerializableGuid.h"

using HolidayHelper::Persistence::ISerializable;
using HolidayHelper::Persistence::SerializableGuid;

enum UserType
{
	UT_NONE = 0,
	UT_CUSTOMER = 1,
	UT_ADMIN = 2
};

namespace HolidayHelper::Data
{
	class DllExport User : public ISerializable
	{
	public:
		User() : m_FirstLogin(true), m_Type(UT_NONE), m_CustomerId(GUID_NULL) {}
		User(GUID Id, string Username, string Password, bool FirstLogin, UserType Type, GUID CustomerId = GUID_NULL)
			: m_Id(Id), m_Username(Username), m_Password(Password), m_FirstLogin(FirstLogin), m_Type(Type), m_CustomerId(CustomerId) {}

		static shared_ptr<User> Create(string Username, string Password, bool FirstLogin, UserType Type, GUID CustomerId = GUID_NULL);

		GUID GetId() { return m_Id.AsGuid(); }
		string GetUsername() { return m_Username; }
		string GetPassword() { return m_Password; }
		bool IsFirstLogin() { return m_FirstLogin; }
		UserType GetUserType() { return m_Type; }
		GUID GetCustomerId() { return m_CustomerId.AsGuid(); }

		void ChangePassword(string NewPassword, bool FirstLogin = true);
		
		string GetUserTypeString();

		std::ostream& Serialize(std::ostream& os);
		std::istream& Deserialize(std::istream& is);

	private:
		UserType UTFromStream(std::istream& is);

		SerializableGuid m_Id;
		string m_Username;
		string m_Password;
		bool m_FirstLogin;
		UserType m_Type;
		SerializableGuid m_CustomerId;
	};


}