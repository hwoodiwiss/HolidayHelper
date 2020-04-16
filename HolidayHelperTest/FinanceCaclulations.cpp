#include "CppUnitTest.h"
#include <HolidayHelperLib/FinanceCalculations.h>

using namespace HolidayHelper::Logic;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;


namespace HolidayHelperTest::Logic
{
	TEST_CLASS(FinanceCalculationsTests)
	{
		TEST_METHOD(CalculateVATTest)
		{
			//Simple test of 1.0 at 20%
			float Value = 1.0f;
			float PercentageRate = 20.0f;
			float Expected = (Value * (PercentageRate / 100));

			auto Actual = CalculateVAT(Value, PercentageRate);

			Assert::AreEqual(Expected, Actual);

			//More complex test
			Value = 256.554f;
			PercentageRate = 17.5f;
			Expected = (Value * (PercentageRate / 100));

			Actual = CalculateVAT(Value, PercentageRate);

			Assert::AreEqual(Expected, Actual);
		}
	};
}