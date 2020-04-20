#include "FinanceCalculations.h"

namespace HolidayHelper::Logic
{
	float FinancialCalculations::CalculateVAT(float Value, float percentageRate)
	{
		float retFloat = Value * (percentageRate / 100);

		return To2Dp(retFloat);
	}

	float FinancialCalculations::GetBasicCost(shared_ptr<Customer> CustomerObj, shared_ptr<Location> LocationObj, DataSet<shared_ptr<Activity>> Activities)
	{
		float TotalCost = 0.0f;
		int NumMembers = CustomerObj->GetNumMembers();

		TotalCost += LocationObj->GetPricePerPerson() * NumMembers;

		for (auto ActivityObj : Activities)
		{
			TotalCost += (ActivityObj->GetPricePerPerson() * NumMembers);
		}

		return To2Dp(TotalCost);
	}

	float FinancialCalculations::ApplyDiscount(float Value, float DiscountPercent)
	{
		float Remaining = (100.0f - DiscountPercent) / 100;
		Value *= Remaining;
		return To2Dp(Value);
	}

	float FinancialCalculations::To2Dp(float Value)
	{
		//Multiply by 100 and convert to int
		//This retains 2 decimal places, and discards anything further
		__int64 retInt = (Value * 100);

		//Cast to float, divide by 100 and return, giving a clean rounding-error resistant 2dp result
		return ((float)retInt / 100.0f);
	}
}