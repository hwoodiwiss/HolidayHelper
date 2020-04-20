#include "TestsCommon.h"
#include <time.h>
#include <random>
#include <HolidayHelperLib/SerializableGuid.h>

using  HolidayHelper::Persistence::SerializableGuid;

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace HolidayHelperTest::Persistence
{
	TEST_CLASS(SerializableGuidTests)
	{
	public:

		TEST_METHOD(AssignmentNativeTest)
		{
			GUID TestGuid;
			if (CoCreateGuid(&TestGuid) != S_OK)
			{
				Assert::Fail(L"Something has gone awry with the Windows API");
			}

			SerializableGuid Value = TestGuid;
			
			Assert::AreEqual(TestGuid, Value.AsGuid());
		}

		TEST_METHOD(EqualityNativeTest)
		{
			GUID TestGuid;
			if (CoCreateGuid(&TestGuid) != S_OK)
			{
				Assert::Fail(L"Something has gone awry with the Windows API");
			}

			SerializableGuid Value(TestGuid);

			//Test freind == overload
			Assert::IsTrue(TestGuid == Value);

			//Test == operator overload
			Assert::IsTrue(Value == TestGuid);
		}
	};
}
