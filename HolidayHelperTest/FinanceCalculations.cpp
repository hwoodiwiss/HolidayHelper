#include "CppUnitTest.h"
#include <HolidayHelperLib/FinanceCalculations.h>

using HolidayHelper::Logic::FinancialCalculations;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;


namespace HolidayHelperTest::Logic
{
	TEST_CLASS(FinanceCalculationsTests)
	{
		TEST_METHOD(CalculateVATTest)
		{
			//Simple test of 1.0 at 20%
			float Value = 1;
			float PercentageRate = 20;
			float Expected = 0.2;

			auto Actual = FinancialCalculations::CalculateVAT(Value, PercentageRate);

			Assert::AreEqual(Expected, Actual);

			//More complex test
			Value = 256.0f;
			PercentageRate = 17.5f;
			Expected = 44.8f;

			Actual = FinancialCalculations::CalculateVAT(Value, PercentageRate);

			Assert::AreEqual(Expected, Actual);
			
			//Another complex test
			Value = 256.75f;
			PercentageRate = 25.6f;
			Expected = 65.72f;

			Actual = FinancialCalculations::CalculateVAT(Value, PercentageRate);

			Assert::AreEqual(Expected, Actual);

			//Input value 0
			Value = 0.0f;
			PercentageRate = 20.0f;
			Expected = 0.0f;

			Actual = FinancialCalculations::CalculateVAT(Value, PercentageRate);

			Assert::AreEqual(Expected, Actual);


			//Percentage value 0
			Value = 1.0f;
			PercentageRate = 0.0f;
			Expected = 0.0f;

			Actual = FinancialCalculations::CalculateVAT(Value, PercentageRate);

			Assert::AreEqual(Expected, Actual);
		}
	};
}