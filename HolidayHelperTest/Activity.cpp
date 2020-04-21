#include "TestsCommon.h"
#include <time.h>
#include <random>
#include <HolidayHelperLib/Activity.h>
#include <HolidayHelperLib/SerializableGuid.h>

using namespace HolidayHelper::Data;

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace HolidayHelperTest::Data
{
	TEST_CLASS(ActivityTests)
	{
	public:
		ActivityTests()
		{
			
		}

		TEST_METHOD(Create)
		{
			string ExpectedName = "Test Activity";
			float ExpectedPpP = 25.5;
			bool ExpectedUserCreated = false;

			auto Activity = Activity::Create("Test Activity", 25.5, false);

			Assert::AreNotEqual(Activity->GetId().AsGuid(), GUID_NULL);
			Assert::AreEqual(ExpectedName, Activity->GetName());
			Assert::AreEqual(ExpectedPpP, Activity->GetPricePerPerson());
			Assert::AreEqual(ExpectedUserCreated, Activity->IsUserCreated());
		}

		TEST_METHOD(Serialize)
		{
			std::stringstream expectedStream;
			expectedStream << SerializableGuid(Id);
			expectedStream.write(Name.data(), sizeof(char) * Name.length() +1);
			expectedStream.write(reinterpret_cast<char*>(&PricePerPerson), sizeof(float));
			expectedStream.write(reinterpret_cast<char*>(&UserCreated), sizeof(bool));
			expectedStream << SerializableGuid(GUID_NULL);

			std::stringstream actualStream;
			Activity Actual = Activity(Id, Name, PricePerPerson, UserCreated);
			actualStream << Actual;


			Assert::AreEqual(expectedStream.str(), actualStream.str());
		}

		TEST_METHOD(Deserialize)
		{
			Activity ExpectedObj = Activity(Id, Name, PricePerPerson, UserCreated);

			std::stringstream ActualStream;
			ActualStream << SerializableGuid(Id);
			ActualStream.write(Name.data(), sizeof(char) * Name.length() + 1);
			ActualStream.write(reinterpret_cast<char*>(&PricePerPerson), sizeof(float));
			ActualStream.write(reinterpret_cast<char*>(&UserCreated), sizeof(bool));

			Activity ActualObj;

			ActualStream >> ActualObj;

			Assert::AreEqual(ExpectedObj.GetId().ToString(), ActualObj.GetId().ToString());
			Assert::AreEqual(ExpectedObj.GetName(), ActualObj.GetName());
			Assert::AreEqual(ExpectedObj.GetPricePerPerson(), ActualObj.GetPricePerPerson());
			Assert::AreEqual(ExpectedObj.IsUserCreated(), ActualObj.IsUserCreated());;
		}

		TEST_METHOD(Equality)
		{
			Activity Obj1 = Activity(Id, Name, PricePerPerson, UserCreated); //The same
			Activity Obj2 = Activity(Id, Name, PricePerPerson, UserCreated); //The same
			Activity Obj3 = Activity(Id, "A different test activity", PricePerPerson, UserCreated); //Different
			Activity Obj4 = Activity(Id, Name, PricePerPerson + 55, UserCreated); //Different
			Activity Obj5 = Activity(Id, Name, PricePerPerson, !UserCreated); //Different
			Activity Obj6 = Activity(Id, Name, PricePerPerson, UserCreated, Id); //Different
			
			Assert::IsTrue(Obj1 == Obj2);

			Assert::IsFalse(Obj1 == Obj3);
			Assert::IsFalse(Obj1 == Obj4);
			Assert::IsFalse(Obj1 == Obj5);
			Assert::IsFalse(Obj1 == Obj6);
		}

		TEST_METHOD(Serialization)
		{
			Activity Expected = Activity(Id, Name, PricePerPerson, UserCreated);

			std::stringstream ss;
			ss << Expected;

			Activity Actual;
			ss >> Actual;

			Assert::IsTrue(Expected == Actual);
		}

	private:
		GUID Id = { 0xf06e320c, 0xbe02, 0x4c98, {0x92, 0xf0, 0x6c, 0x36, 0x83, 0x5b, 0x3b, 0x6e} };
		string Name = "Test Activity";
		float PricePerPerson = 50.0f;
		bool UserCreated = false;
	};
}
