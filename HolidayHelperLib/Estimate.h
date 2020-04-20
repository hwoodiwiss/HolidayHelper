#pragma once
#include "Common.h"
#include "SerializableGuid.h"
#include "SerializableVector.h"

using HolidayHelper::Persistence::ISerializable;
using HolidayHelper::Persistence::SerializableGuid;
using HolidayHelper::Persistence::SerializableVector;

namespace HolidayHelper::Data
{
	class DllExport Estimate : public ISerializable
	{
	public:
		Estimate() : m_Id(GUID_NULL), m_Customer(GUID_NULL), m_Location(GUID_NULL) {}
		Estimate(GUID Id, GUID CustomerId, GUID LocationId, SerializableVector<SerializableGuid> ActivityIds, float Price)
			: m_Id(Id), m_Customer(CustomerId), m_Location(LocationId), m_Activities(ActivityIds), m_Price(Price) {}

		static shared_ptr<Estimate> Create(GUID CustomerId, GUID LocationId, SerializableVector<SerializableGuid> ActivityIds, float Price);

		GUID GetId() { return m_Id.AsGuid(); }
		GUID GetCustomerId() { return m_Customer.AsGuid(); }
		GUID GetLocationId() { return m_Location.AsGuid(); }
		DataSet<GUID> GetActivityIds() { return m_Activities.Select<GUID>([](shared_ptr<SerializableGuid> s)->GUID { return s->AsGuid(); }); }
		float GetPrice() { return m_Price; }

		bool operator==(const Estimate& rhs);

		std::ostream& Serialize(std::ostream& os);
		std::istream& Deserialize(std::istream& is);

	private:
		SerializableGuid m_Id;
		SerializableGuid m_Customer;
		SerializableGuid m_Location;
		SerializableVector<SerializableGuid> m_Activities;
		//Store the price in the estimate, so that changes in price don't later affect the estimate price
		float m_Price;
	};
}