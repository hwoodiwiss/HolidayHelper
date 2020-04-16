#pragma once
#include "Common.h"
#include "SerializableGuid.h"

using namespace HolidayHelper::Persistence;

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
		User() {}

		SerializableGuid GetId() { return m_Id; }
		string GetUsername() { return m_Username; }
		UserType GetUserType() { return m_Type; }

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