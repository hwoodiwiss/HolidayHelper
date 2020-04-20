#include "TestsCommon.h"
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

		TEST_METHOD(ApplyDiscountTest)
		{
			//Very basic, easy to convert to percentage
			float Value = 100;
			float DiscountPercent = 10;
			float Expected = 90;

			float Actual = FinancialCalculations::ApplyDiscount(Value, DiscountPercent);

			Assert::AreEqual(Expected, Actual);
			

			//Decent example within normal usage
			Value = 29.99;
			DiscountPercent = 45;
			Expected = 16.49;

			Actual = FinancialCalculations::ApplyDiscount(Value, DiscountPercent);
			
			Assert::AreEqual(Expected, Actual);

			//Large numbers
			Value = 41354435;
			DiscountPercent = 37.5;
			Expected = 25846521.87;

			Actual = FinancialCalculations::ApplyDiscount(Value, DiscountPercent);

			Assert::AreEqual(Expected, Actual);

		}

		TEST_METHOD(To2DpTest)
		{
			float Value = 10.1594;
			float Expected = 10.15;
			float Actual = FinancialCalculations::To2Dp(Value);

			Assert::AreEqual(Expected, Actual);
			
			Value = 1.3333333333;
			Expected = 1.33;
			Actual = FinancialCalculations::To2Dp(Value);

			Assert::AreEqual(Expected, Actual);
			
			Value = 5555555.21213;
			Expected = 5555555.21;
			Actual = FinancialCalculations::To2Dp(Value);

			Assert::AreEqual(Expected, Actual);
		}
	};
}