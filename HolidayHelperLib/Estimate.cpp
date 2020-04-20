#include "Estimate.h"

namespace HolidayHelper::Data
{
	shared_ptr<Estimate> Estimate::Create(GUID CustomerId, GUID LocationId, SerializableVector<SerializableGuid> ActivityIds, float Price)
	{
		GUID EstimateId;
		if (CoCreateGuid(&EstimateId) != S_OK)
		{
			return nullptr;
		}
		return shared_ptr<Estimate>(new Estimate(EstimateId, CustomerId, LocationId, ActivityIds, Price));
	}

	bool Estimate::operator==(const Estimate& rhs)
	{
		return (m_Id == rhs.m_Id
			&& m_Customer == rhs.m_Customer
			&& m_Location == rhs.m_Location
			&& m_Price == rhs.m_Price
			&& m_Activities == rhs.m_Activities);
	}

	std::ostream& Estimate::Serialize(std::ostream& os)
	{
		os << m_Id << m_Customer << m_Location << m_Activities;
		os.write(reinterpret_cast<char*>(&m_Price), sizeof(float));
		return os;
	}

	std::istream& Estimate::Deserialize(std::istream& is)
	{
		is >> m_Id >> m_Customer >> m_Location >> m_Activities;
		is.read(reinterpret_cast<char*>(&m_Price), sizeof(float));
		return is;
	}
}