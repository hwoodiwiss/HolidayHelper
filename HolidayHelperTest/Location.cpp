#include "TestsCommon.h"
#include <time.h>
#include <random>
#include <HolidayHelperLib/Location.h>
#include <HolidayHelperLib/SerializableGuid.h>

using namespace HolidayHelper::Data;

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace HolidayHelperTest::Data
{
	TEST_CLASS(LocationTests)
	{
	public:
		LocationTests()
		{

		}

		TEST_METHOD(Create)
		{
			string ExpectedName = "Test Activity";
			float ExpectedPpP = 25.5;
			int ExpectedMinTravellers = 25;

			auto LocationObj = Location::Create("Test Activity", 25.5, 25);

			Assert::AreNotEqual(LocationObj->GetId().AsGuid(), GUID_NULL);
			Assert::AreEqual(ExpectedName, LocationObj->GetName());
			Assert::AreEqual(ExpectedPpP, LocationObj->GetPricePerPerson());
			Assert::AreEqual(ExpectedMinTravellers, LocationObj->GetMinTravellers());
		}

		TEST_METHOD(Serialize)
		{
			std::stringstream expectedStream;
			expectedStream << SerializableGuid(Id);
			expectedStream.write(Name.data(), sizeof(char) * Name.length() + 1);
			expectedStream.write(reinterpret_cast<char*>(&PricePerPerson), sizeof(float));
			expectedStream.write(reinterpret_cast<char*>(&MinTravellers), sizeof(int));

			std::stringstream actualStream;
			Location ActualObj = Location(Id, Name, PricePerPerson, MinTravellers);
			actualStream << ActualObj;


			Assert::AreEqual(expectedStream.str(), actualStream.str());
		}

		TEST_METHOD(Deserialize)
		{
			Location ExpectedObj = Location(Id, Name, PricePerPerson, MinTravellers);

			std::stringstream ActualStream;
			ActualStream << SerializableGuid(Id);
			ActualStream.write(Name.data(), sizeof(char) * Name.length() + 1);
			ActualStream.write(reinterpret_cast<char*>(&PricePerPerson), sizeof(float));
			ActualStream.write(reinterpret_cast<char*>(&MinTravellers), sizeof(int));

			Location ActualObj;

			ActualStream >> ActualObj;

			Assert::AreEqual(ExpectedObj.GetId().ToString(), ActualObj.GetId().ToString());
			Assert::AreEqual(ExpectedObj.GetName(), ActualObj.GetName());
			Assert::AreEqual(ExpectedObj.GetPricePerPerson(), ActualObj.GetPricePerPerson());
			Assert::AreEqual(ExpectedObj.GetMinTravellers(), ActualObj.GetMinTravellers());;
		}

		TEST_METHOD(Equality)
		{
			Location Obj1 = Location(Id, Name, PricePerPerson, MinTravellers); //The same
			Location Obj2 = Location(Id, Name, PricePerPerson, MinTravellers); //The same
			Location Obj3 = Location(Id, "A different test Location", PricePerPerson, MinTravellers); //Different
			Location Obj4 = Location(Id, Name, PricePerPerson + 55, MinTravellers); //Different
			Location Obj5 = Location(Id, Name, PricePerPerson, MinTravellers - 1); //Different
			Location Obj6 = Location(Id, Name, PricePerPerson, MinTravellers + 10); //Different

			Assert::IsTrue(Obj1 == Obj2);

			Assert::IsFalse(Obj1 == Obj3);
			Assert::IsFalse(Obj1 == Obj4);
			Assert::IsFalse(Obj1 == Obj5);
			Assert::IsFalse(Obj1 == Obj6);
		}

		TEST_METHOD(Serialization)
		{
			Location Expected = Location(Id, Name, PricePerPerson, MinTravellers);

			std::stringstream ss;
			ss << Expected;

			Location Actual;
			ss >> Actual;

			Assert::IsTrue(Expected == Actual);
		}

		TEST_METHOD(NameGetSet)
		{
			Location TestLocation;

			string Expected = "Expected Location Name";

			TestLocation.SetName(Expected);

			Assert::AreEqual(Expected, TestLocation.GetName());
		}
		
		TEST_METHOD(MinTravellersGetSet)
		{
			Location TestLocation;

			int Expected = 6;

			TestLocation.SetMinTravellers(Expected);

			Assert::AreEqual(Expected, TestLocation.GetMinTravellers());
		}
		
		TEST_METHOD(PricePerPersonGetSet)
		{
			Location TestLocation;

			float Expected = 210.55f;

			TestLocation.SetPrice(Expected);

			Assert::AreEqual(Expected, TestLocation.GetPricePerPerson());
		}

	private:
		GUID Id = { 0xb46492cc, 0xbe02, 0x4c98, {0x92, 0xf0, 0x6c, 0x36, 0x83, 0x5b, 0x3b, 0x6e} };
		string Name = "Test Location";
		float PricePerPerson = 64.0f;
		int MinTravellers = 5;
	};
}