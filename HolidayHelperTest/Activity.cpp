#include "CppUnitTest.h"
#include <time.h>
#include <random>
#include <HolidayHelperLib/Activity.h>

using namespace HolidayHelper::Data;

namespace Microsoft::VisualStudio::CppUnitTestFramework
{

}

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace HolidayHelperTest::Data
{
	TEST_CLASS(ActivityTests)
	{
	public:
		ActivityTests()
		{
			m_TestActivity = Activity();
		}

		TEST_METHOD(Serialize)
		{

		}

		TEST_METHOD(Deserialize)
		{

		}

	private:
		Activity m_TestActivity;
	};
}
