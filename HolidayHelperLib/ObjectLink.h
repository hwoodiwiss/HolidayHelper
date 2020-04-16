#pragma once
#include "Common.h"
#include "ISerializable.h"
#include "SerializableGuid.h"

using namespace HolidayHelper::Persistence;

namespace HolidayHelper::Data
{
	class DllExport ObjectLink : public ISerializable
	{
	public:
		ObjectLink() {};
		ObjectLink(SerializableGuid FirstId, SerializableGuid SecondId) : m_FirstId(FirstId), m_SecondId(SecondId) {};

		SerializableGuid GetFirstId() { return m_FirstId; }
		SerializableGuid GetSecondId() { return m_SecondId; }

		std::ostream& Serialize(std::ostream& os);
		std::istream& Deserialize(std::istream& is);

	private:
		SerializableGuid m_FirstId;
		SerializableGuid m_SecondId;
	};
}
