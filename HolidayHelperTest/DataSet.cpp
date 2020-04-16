#include "CppUnitTest.h"
#include <time.h>
#include <random>
#include <HolidayHelperLib/Dataset.h>

using namespace HolidayHelper::Data;

namespace Microsoft::VisualStudio::CppUnitTestFramework
{
	//Add a tostring helper for the unit test framework
	template<> static std::wstring ToString<DataSet<int>>(const class DataSet<int>& t)
	{
		std::wstringstream wss;
		for (auto val : t)
		{
			wss << val << ", ";
		}

		return wss.str();
	}
}

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
	};
}
