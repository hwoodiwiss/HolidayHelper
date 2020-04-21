#include "TestsCommon.h"
#include <time.h>
#include <random>
#include <HolidayHelperLib/Customer.h>
#include <HolidayHelperLib/SerializableGuid.h>

using namespace HolidayHelper::Data;

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace HolidayHelperTest::Data
{
	TEST_CLASS(CustomerTests)
	{
	public:
		CustomerTests()
		{

		}

		TEST_METHOD(Create)
		{
			string ExpectedFirstName = "Hugo";
			string ExpectedLastName = "Woodiwiss";
			int ExpectedNumAdults = 2;
			int ExpectedNumChildren = 2;

			auto CustomerObj = Customer::Create("Hugo", "Woodiwiss", 2, 2);

			Assert::AreNotEqual(GUID_NULL, CustomerObj->GetId().AsGuid());
			Assert::AreEqual(ExpectedFirstName, CustomerObj->GetFirstName());
			Assert::AreEqual(ExpectedLastName, CustomerObj->GetLastName());
			Assert::AreEqual(ExpectedNumAdults, CustomerObj->GetNumAdults());
			Assert::AreEqual(ExpectedNumChildren, CustomerObj->GetNumChildren());

		}

		TEST_METHOD(GetFullName)
		{
			Customer CustomerObj = Customer(Id, NameFirst, NameLast, NumAdults, NumChildren);
			string Expected = NameFirst + " " + NameLast;

			Assert::AreEqual(Expected, CustomerObj.GetFullName());
		}

		TEST_METHOD(GetNameCommaFull)
		{
			Customer CustomerObj = Customer(Id, NameFirst, NameLast, NumAdults, NumChildren);
			string Expected = NameLast + ", " + NameFirst;

			Assert::AreEqual(Expected, CustomerObj.GetNameCommaFull());
		}

		TEST_METHOD(GetNumMembers)
		{
			Customer CustomerObj = Customer(Id, NameFirst, NameLast, NumAdults, NumChildren);
			int Expected = NumChildren + NumAdults;

			Assert::AreEqual(Expected, CustomerObj.GetNumMembers());
		}

		TEST_METHOD(IsDiscountEligible)
		{
			Customer Eligible22 = Customer(Id, NameFirst, NameLast, 2, 2);
			bool Expected = true;

			Assert::AreEqual(Expected, Eligible22.IsDiscountEligible());

			Customer NotEligible21 = Customer(Id, NameFirst, NameLast, 2, 1);
			Expected = false;

			Assert::AreEqual(Expected, NotEligible21.IsDiscountEligible());	
			
			Customer Eligible32 = Customer(Id, NameFirst, NameLast, 3, 2);
			Expected = true;

			Assert::AreEqual(Expected, Eligible32.IsDiscountEligible());
		}

		TEST_METHOD(Serialize)
		{
			std::stringstream expectedStream;
			expectedStream << SerializableGuid(Id);
			expectedStream.write(NameFirst.data(), sizeof(char) * NameFirst.length() + 1);
			expectedStream.write(NameLast.data(), sizeof(char) * NameLast.length() + 1);
			expectedStream.write(reinterpret_cast<char*>(&NumAdults), sizeof(int));
			expectedStream.write(reinterpret_cast<char*>(&NumChildren), sizeof(int));

			std::stringstream actualStream;
			Customer ActualObj = Customer(Id, NameFirst, NameLast, NumAdults, NumChildren);
			actualStream << ActualObj;


			Assert::AreEqual(expectedStream.str(), actualStream.str());
		}

		TEST_METHOD(Deserialize)
		{
			Customer ExpectedObj = Customer(Id, NameFirst, NameLast, NumAdults, NumChildren); //The same

			std::stringstream ActualStream;
			ActualStream << SerializableGuid(Id);
			ActualStream.write(NameFirst.data(), sizeof(char) * NameFirst.length() + 1);
			ActualStream.write(NameLast.data(), sizeof(char) * NameLast.length() + 1);
			ActualStream.write(reinterpret_cast<char*>(&NumAdults), sizeof(int));
			ActualStream.write(reinterpret_cast<char*>(&NumChildren), sizeof(int));

			Customer ActualObj;

			ActualStream >> ActualObj;

			Assert::AreEqual(ExpectedObj.GetId().ToString(), ActualObj.GetId().ToString());
			Assert::AreEqual(ExpectedObj.GetFirstName(), ActualObj.GetFirstName());
			Assert::AreEqual(ExpectedObj.GetLastName(), ActualObj.GetLastName());
			Assert::AreEqual(ExpectedObj.GetNumAdults(), ActualObj.GetNumAdults());;
			Assert::AreEqual(ExpectedObj.GetNumChildren(), ActualObj.GetNumChildren());
		}

		TEST_METHOD(Equality)
		{
			Customer Obj1 = Customer(Id, NameFirst, NameLast, NumAdults, NumChildren); //The same
			Customer Obj2 = Customer(Id, NameFirst, NameLast, NumAdults, NumChildren); //The same
			Customer Obj3 = Customer(Id, NameFirst, NameLast, 1, NumChildren); //Different
			Customer Obj4 = Customer(Id, NameFirst, NameLast, NumAdults, 1); //Different
			Customer Obj5 = Customer(Id, "Nope", NameLast, NumAdults, NumChildren); //Different
			Customer Obj6 = Customer(Id, NameFirst, "Incorrect", NumAdults, NumChildren); //Different

			Assert::IsTrue(Obj1 == Obj2);

			Assert::IsFalse(Obj1 == Obj3);
			Assert::IsFalse(Obj1 == Obj4);
			Assert::IsFalse(Obj1 == Obj5);
			Assert::IsFalse(Obj1 == Obj6);
		}

		TEST_METHOD(Serialization)
		{
			Customer Expected = Customer(Id, NameFirst, NameLast, NumAdults, NumChildren);

			std::stringstream ss;
			ss << Expected;

			Customer Actual;
			ss >> Actual;

			Assert::IsTrue(Expected == Actual);
		}

	private:
		GUID Id = { 0xb46492cc, 0xbe02, 0x4cc6, {0x92, 0xf0, 0x6c, 0x36, 0x83, 0x5b, 0x3b, 0x6e} };
		string NameFirst = "Test";
		string NameLast = "Customer";
		int NumAdults = 2;
		int NumChildren = 2;
	};
}