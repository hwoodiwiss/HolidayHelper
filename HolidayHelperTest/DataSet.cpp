#include "TestsCommon.h"
#include <time.h>
#include <random>
#include <HolidayHelperLib/Dataset.h>

using namespace HolidayHelper::Data;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace HolidayHelperTest::Data
{
	TEST_CLASS(DataSetTests)
	{
	public:

		TEST_METHOD(Where)
		{
			
			DataSet<int> intData({ 1, 3, 5, 7, 9 });
			auto retVal = intData.Where([](int x){ return x <= 5; });
			
			for (auto val : retVal)
			{
				if (val > 5) Assert::Fail(L"Incorrect data returned from where");
			}

		}

		TEST_METHOD(Select)
		{
			//Set up a DataSet of vectors with 2, 4 and 1 elements
			DataSet<vector<int>> vecIntData({ {1,2}, {1,2,3,4}, {1} });

			//Create a dataset of expected values
			DataSet<int> expected({ 2, 4, 1 });

			//Select the size from the dataset of arrays
			auto retVal = vecIntData.Select<int>([](vector<int> x){ return (int)x.size(); });

			Assert::AreEqual(expected, retVal);
		}

		TEST_METHOD(First)
		{
			DataSet<int> intData({ 501, 503, 505, 507, 509 });
			int Expected = 501;

			auto Actual = intData.First();

			Assert::AreEqual(Expected, Actual);
		}

		TEST_METHOD(Contains)
		{
			DataSet<int> intData({ 200, 201, 301, 400, 401, 404, 500, 501, 504 });
			bool Expected = true;
			bool Actual = intData.Contains(201);

			Assert::AreEqual(Expected, Actual);

			Expected = false;
			Actual = intData.Contains(514);

			Assert::AreEqual(Expected, Actual);

		}
	};
}
