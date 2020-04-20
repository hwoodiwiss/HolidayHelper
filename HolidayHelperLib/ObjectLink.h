#pragma once
#include "Common.h"
#include "ISerializable.h"
#include "SerializableGuid.h"

using HolidayHelper::Persistence::ISerializable;
using HolidayHelper::Persistence::SerializableGuid;

namespace HolidayHelper::Data
{
	class DllExport ObjectLink : public ISerializable
	{
	public:
		ObjectLink() {};
		ObjectLink(SerializableGuid FirstId, SerializableGuid SecondId) : m_FirstId(FirstId), m_SecondId(SecondId) {};

		SerializableGuid GetFirstId() { return m_FirstId; }
		SerializableGuid GetSecondId() { return m_SecondId; }

		bool operator==(const ObjectLink& rhs);

		std::ostream& Serialize(std::ostream& os);
		std::istream& Deserialize(std::istream& is);

	private:
		SerializableGuid m_FirstId;
		SerializableGuid m_SecondId;
	};
}
