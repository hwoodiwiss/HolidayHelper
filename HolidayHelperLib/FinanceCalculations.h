#pragma once
#include "Common.h"

namespace HolidayHelper::Logic
{
	//Encapsulated static functions in a class for easier exporting from the DLL
	class DllExport FinancialCalculations
	{
	public:
		//returns values to 2 decimal places, any more is excessive, and this avoids floating-point rounding errors
		static float CalculateVAT(float Value, float percentageRate);
	};

}