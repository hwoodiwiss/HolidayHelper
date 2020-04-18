#include "Estimate.h"

namespace HolidayHelper::Data
{
	shared_ptr<Estimate> Estimate::Create(GUID CustomerId, GUID LocationId, SerializableVector<SerializableGuid> ActivityIds)
	{
		GUID EstimateId;
		if (CoCreateGuid(&EstimateId) != S_OK)
		{
			return nullptr;
		}
		return shared_ptr<Estimate>(new Estimate(EstimateId, CustomerId, LocationId, ActivityIds));
	}
	std::ostream& Estimate::Serialize(std::ostream& os)
	{
		os << m_Id << m_Customer << m_Location << m_Activities;
		return os;
	}

	std::istream& Estimate::Deserialize(std::istream& is)
	{
		is >> m_Id >> m_Customer >> m_Location >> m_Activities;
		return is;
	}
}