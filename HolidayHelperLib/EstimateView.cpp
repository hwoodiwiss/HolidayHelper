#include "EstimateView.h"
#include <sstream>
#include "FinanceCalculations.h"

using std::endl;
using HolidayHelper::Logic::FinancialCalculations;

string HolidayHelper::Data::EstimateView::RenderView()
{
	std::stringstream ss;
	ss << string(118, '_') << std::endl;
	ss << m_Location->GetName();
	if (m_Activities.size() > 0)
	{
		ss << " (Chosen Activities: ";
		int index = 0;

		for (auto ActivityObj : m_Activities)
		{
			ss << ActivityObj->GetName() << (index != m_Activities.size() - 1 ? ", " : "");
			index++;
		}
		ss << ") ";
	}
	ss << endl << "Price (ex VAT): " << char(156) << std::setprecision(2) << std::fixed << m_Estimate->GetPrice()
		<< " VAT: " << char(156) << std::setprecision(2) << std::fixed << FinancialCalculations::CalculateVAT(m_Estimate->GetPrice(), 20.0f)
		<< " Total: " << char(156) << std::setprecision(2) << std::fixed << m_Estimate->GetPrice() + FinancialCalculations::CalculateVAT(m_Estimate->GetPrice(), 20.0f) << endl;
	ss << string(118, '_') << endl << endl;
	return ss.str();
}
