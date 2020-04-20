#pragma once
#include "Common.h"
#include "Dataset.h"
#include "Customer.h"
#include "Location.h"
#include "Activity.h"

using HolidayHelper::Data::DataSet;
using HolidayHelper::Data::Customer;
using HolidayHelper::Data::Location;
using HolidayHelper::Data::Activity;

namespace HolidayHelper::Logic
{
	//Encapsulated static functions in a class for easier exporting from the DLL
	class DllExport FinancialCalculations
	{
	public:
		//returns values to 2 decimal places, any more is excessive, and this avoids floating-point rounding errors
		static float CalculateVAT(float Value, float percentageRate);

		static float GetBasicCost(shared_ptr<Customer> CustomerObj, shared_ptr<Location> LocationObj, DataSet<shared_ptr<Activity>> Activities);

		static float ApplyDiscount(float Value, float DiscountPercent);

		//Truncates float data to 2 decimal places
		static float To2Dp(float Value);
	};

}