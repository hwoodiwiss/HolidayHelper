#include "FinanceCalculations.h"

namespace HolidayHelper::Logic
{
	float FinancialCalculations::CalculateVAT(float Value, float percentageRate)
	{
		float retFloat = Value * (percentageRate / 100);

		//Multiply by 100 and convert to int
		//This retains 2 decimal places, and discards anything further
		int retInt = (retFloat * 100);

		//Cast to float, divide by 100 and return, giving a clean rounding-error resistant 2dp result
		return ((float)retInt / 100.0f);
	}
}