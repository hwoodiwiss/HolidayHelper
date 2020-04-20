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
		EstimateView(shared_ptr<Estimate> Estimate, shared_ptr<Customer> Customer, shared_ptr<Location> Location, DataSet<shared_ptr<Activity>> Activities) : m_Estimate(Estimate), m_Customer(Customer), m_Location(Location), m_Activities(Activities) {}

		const float GetPrice() { return m_Estimate->GetPrice(); }
		const shared_ptr<Customer> GetCustomer() { return m_Customer; }
		const shared_ptr<Location> GetLocation() { return m_Location; }
		const DataSet<shared_ptr<Activity>> GetActivities() { return m_Activities; }

		string RenderView();

	private:
		const shared_ptr<Estimate> m_Estimate;
		const shared_ptr<Customer> m_Customer;
		const shared_ptr<Location> m_Location;
		const DataSet<shared_ptr<Activity>> m_Activities;
	};
}
