#include "Customer.h"

namespace HolidayHelper::Data
{
	shared_ptr<Customer> Customer::Create(string FirstName, string LastName, int NumAdults, int NumChildren)
	{
		GUID CustId;
		if (CoCreateGuid(&CustId) != S_OK)
		{
			return nullptr;
		}

		return shared_ptr<Customer>(new Customer(CustId, FirstName, LastName, NumAdults, NumChildren));
	}

	bool Customer::IsDiscountEligible()
	{
		return (m_NumAdults >= 2) && (m_NumChildren >= 2);
	}

	bool Customer::operator==(const Customer& rhs)
	{
		return (m_Id == rhs.m_Id
			&& m_FirstName == rhs.m_FirstName
			&& m_LastName == rhs.m_LastName
			&& m_NumAdults == rhs.m_NumAdults
			&& m_NumChildren == rhs.m_NumChildren
			);
	}

	std::ostream& Customer::Serialize(std::ostream& os)
	{
		os << m_Id;
		os.write(m_FirstName.data(), sizeof(char) * m_FirstName.length() + 1);
		os.write(m_LastName.data(), sizeof(char) * m_LastName.length() + 1);
		os.write(reinterpret_cast<char*>(&m_NumAdults), sizeof(int));
		os.write(reinterpret_cast<char*>(&m_NumChildren), sizeof(int));
		return os;
	}

	std::istream& Customer::Deserialize(std::istream& is)
	{
		is >> m_Id;
		m_FirstName = InStreamToString(is);
		m_LastName = InStreamToString(is);
		is.read(reinterpret_cast<char*>(&m_NumAdults), sizeof(int));
		is.read(reinterpret_cast<char*>(&m_NumChildren), sizeof(int));
		return is;
	}
}
