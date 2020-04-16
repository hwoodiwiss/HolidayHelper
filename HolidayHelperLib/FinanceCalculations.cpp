#include "FinanceCalculations.h"

namespace HolidayHelper::Logic
{
	float DllExport CalculateVAT(float Value, float percentageRate)
	{
		float decimalRate = percentageRate / 100.0f;
		return Value * decimalRate;
	}
}