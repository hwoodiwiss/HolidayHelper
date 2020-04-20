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

		TEST_METHOD(AssignmentNative)
		{
			GUID TestGuid;
			if (CoCreateGuid(&TestGuid) != S_OK)
			{
				Assert::Fail(L"Something has gone awry with the Windows API");
			}

			SerializableGuid Value = TestGuid;
			
			Assert::AreEqual(TestGuid, Value.AsGuid());
		}

		TEST_METHOD(EqualityNative)
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

		TEST_METHOD(AsGuid)
		{
			GUID ExpectedGuid = { 0xf06e320c, 0xbe02, 0x4c98, {0x92, 0xf0, 0x6c, 0x36, 0x83, 0x5b, 0x3b, 0x64} };
			GUID ActualGuid = SerializableGuid(ExpectedGuid).AsGuid();
			

			Assert::AreEqual(ExpectedGuid, ActualGuid);
		}

		TEST_METHOD(ToString)
		{
			GUID TestGuid = { 0xf06e320c, 0xbe02, 0x4c98, {0x92, 0xf0, 0x6c, 0x36, 0x83, 0x5b, 0x3b, 0x6e} };
			string Expected = "{F06E320C-BE02-4C98-92F0-6C36835B3B6E}";
			SerializableGuid SerTestGuid = TestGuid;
			string Actual = SerTestGuid.ToString();

			Assert::AreEqual(Expected, Actual);

			Expected = "F06E320C-BE02-4C98-92F0-6C36835B3B6E";
			Actual = SerTestGuid.ToString(false);

			Assert::AreEqual(Expected, Actual);

		}

		TEST_METHOD(Serialization)
		{
			GUID TestGuid;
			if (CoCreateGuid(&TestGuid) != S_OK)
			{
				Assert::Fail(L"Something has gone awry with the Windows API");
			}
			SerializableGuid ExpectedSerializable(TestGuid);
			std::stringstream ss;
			ss << ExpectedSerializable;

			SerializableGuid ActualSerializable;
			ss >> ActualSerializable;

			Assert::AreEqual(ExpectedSerializable.AsGuid(), ActualSerializable.AsGuid());
		}
	};
}
