#include "CppUnitTest.h"
#include <time.h>
#include <random>
#include <HolidayHelperLib/Dataset.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace HolidayHelperTest
{
	TEST_CLASS(DataSetTests)
	{
	public:

		TEST_METHOD(TestWhere)
		{
			
			DataSet<int> intData({ 1, 3, 5, 7, 9 });
			auto retVal = intData.Where([](int x){ return x <= 5; });
			
			for (auto val : retVal)
			{
				if (val > 5) Assert::Fail(L"Incorrect data returned from where");
			}

		}

		TEST_METHOD(TestSelect)
		{
			DataSet<vector<int>> vecIntData({ {1,2}, {1,2,3,4}, {1} });
			DataSet<int> expected({ 2, 4, 1 });
			auto retVal = vecIntData.Select<int>([](vector<int> x){ return (int)x.size(); });

			Assert::IsTrue(retVal == expected);
		}
	};
}
