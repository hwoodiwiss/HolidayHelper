#pragma once
#include "Common.h"
#include "Estimate.h"
#include "Customer.h"
#include "Location.h"
#include "Activity.h"

namespace HolidayHelper::Data
{
	class DllExport EstimateView
	{
	public:
		EstimateView() {};
		EstimateView(shared_ptr<Customer> Customer, shared_ptr<Location> Location, DataSet<shared_ptr<Activity>> Activities) : m_Customer(Customer), m_Location(Location), m_Activities(Activities) {}

	private:
		const shared_ptr<Customer> m_Customer;
		const shared_ptr<Location> m_Location;
		const DataSet<shared_ptr<Activity>> m_Activities;
	};
}
