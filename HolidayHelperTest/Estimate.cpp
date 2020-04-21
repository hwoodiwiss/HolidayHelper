#include "TestsCommon.h"
#include <time.h>
#include <random>
#include <HolidayHelperLib/Estimate.h>
#include <HolidayHelperLib/SerializableGuid.h>

using namespace HolidayHelper::Data;

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace HolidayHelperTest::Data
{
	TEST_CLASS(EstimateTests)
	{
	public:
		EstimateTests()
		{

		}

		TEST_METHOD(Create)
		{
			GUID ExpectedCustomerId = { 0xb46492f5, 0xbe02, 0x4cc6, {0x92, 0xf0, 0x6c, 0x36, 0x83, 0x5b, 0x3b, 0x6e} };
			GUID ExpectedLocationId = { 0xb46492f6, 0xbe02, 0x4cc6, {0x92, 0xf0, 0x6c, 0x36, 0x83, 0x5b, 0x3b, 0x6e} };
			SerializableVector<SerializableGuid> ExpectedActivityIds;
			ExpectedActivityIds.push_back(shared_ptr<SerializableGuid>(new SerializableGuid({ 0xb46492f7, 0xbe02, 0x4cc6, {0x92, 0xf0, 0x6c, 0x36, 0x83, 0x5b, 0x3b, 0x6e} })));
			ExpectedActivityIds.push_back(shared_ptr<SerializableGuid>(new SerializableGuid({ 0xb46492f8, 0xbe02, 0x4cc6, {0x92, 0xf0, 0x6c, 0x36, 0x83, 0x5b, 0x3b, 0x6e} })));
			float ExpectedPrice = 2590.95;

			auto EstimateObj = Estimate::Create({ 0xb46492f5, 0xbe02, 0x4cc6, {0x92, 0xf0, 0x6c, 0x36, 0x83, 0x5b, 0x3b, 0x6e} }, { 0xb46492f6, 0xbe02, 0x4cc6, {0x92, 0xf0, 0x6c, 0x36, 0x83, 0x5b, 0x3b, 0x6e} }, ExpectedActivityIds, 2590.95);

			Assert::AreNotEqual(GUID_NULL, EstimateObj->GetId());
			Assert::AreEqual(ExpectedCustomerId, EstimateObj->GetCustomerId());
			Assert::AreEqual(ExpectedLocationId, EstimateObj->GetLocationId());
			Assert::AreEqual(ExpectedPrice, EstimateObj->GetPrice());

			auto ActualActivityIds = EstimateObj->GetActivityIds();
			size_t NumIds = ActualActivityIds.size();
			
			Assert::AreEqual(ExpectedActivityIds.size(), NumIds);

			for (size_t index = 0; index < NumIds; index++)
			{
				Assert::AreEqual(ExpectedActivityIds[index]->AsGuid(), ActualActivityIds[index]);
			}

		}

		TEST_METHOD(Serialize)
		{
			std::stringstream expectedStream;
			SerializableVector<SerializableGuid> SerActivityIds;
			for (GUID ActivityId : ActivityIds)
			{
				SerActivityIds.push_back(shared_ptr<SerializableGuid>(new SerializableGuid(ActivityId)));
			}
			expectedStream << SerializableGuid(Id) << SerializableGuid(CustomerId) << SerializableGuid(LocationId) << SerActivityIds;
			expectedStream.write(reinterpret_cast<char*>(&Price), sizeof(float));

			std::stringstream actualStream;
			Estimate ActualObj = Estimate(Id, CustomerId, LocationId, SerActivityIds, Price);
			actualStream << ActualObj;


			Assert::AreEqual(expectedStream.str(), actualStream.str());
		}

		TEST_METHOD(Deserialize)
		{
			SerializableVector<SerializableGuid> SerActivityIds;
			for (GUID ActivityId : ActivityIds)
			{
				SerActivityIds.push_back(shared_ptr<SerializableGuid>(new SerializableGuid(ActivityId)));
			}

			Estimate ExpectedObj = Estimate(Id, CustomerId, LocationId, SerActivityIds, Price);

			std::stringstream ActualStream;
			ActualStream << SerializableGuid(Id) << SerializableGuid(CustomerId) << SerializableGuid(LocationId) << SerActivityIds;
			ActualStream.write(reinterpret_cast<char*>(&Price), sizeof(float));

			Estimate ActualObj;

			ActualStream >> ActualObj;

			Assert::AreEqual(ExpectedObj.GetId(), ActualObj.GetId());
			Assert::AreEqual(ExpectedObj.GetCustomerId(), ActualObj.GetCustomerId());
			Assert::AreEqual(ExpectedObj.GetLocationId(), ActualObj.GetLocationId());
			Assert::AreEqual(ExpectedObj.GetPrice(), ActualObj.GetPrice());;
			
			auto ExpectedActivityIds = ExpectedObj.GetActivityIds();
			auto ActualActivityIds = ActualObj.GetActivityIds();
			size_t NumIds = ActualActivityIds.size();

			Assert::AreEqual(ExpectedObj.GetActivityIds().size(), NumIds);

			for (size_t index = 0; index < NumIds; index++)
			{
				Assert::AreEqual(ExpectedActivityIds[index], ActualActivityIds[index]);
			}

		}

		TEST_METHOD(Serialization)
		{
			SerializableVector<SerializableGuid> SerActivityIds;
			for (GUID ActivityId : ActivityIds)
			{
				SerActivityIds.push_back(shared_ptr<SerializableGuid>(new SerializableGuid(ActivityId)));
			}

			Estimate Expected = Estimate(Id, CustomerId, LocationId, SerActivityIds, Price);

			std::stringstream ss;
			ss << Expected;

			Estimate Actual;
			ss >> Actual;

			Assert::IsTrue(Expected == Actual);
		}

	private:
		GUID Id = { 0xb46492f1, 0xbe02, 0x4cc6, {0x92, 0xf0, 0x6c, 0x36, 0x83, 0x5b, 0x3b, 0x6e} };
		GUID CustomerId = { 0xb46492f2, 0xbe02, 0x4cc6, {0x92, 0xf0, 0x6c, 0x36, 0x83, 0x5b, 0x3b, 0x6e} };
		GUID LocationId = { 0xb46492f3, 0xbe02, 0x4cc6, {0x92, 0xf0, 0x6c, 0x36, 0x83, 0x5b, 0x3b, 0x6e} };
		vector<GUID> ActivityIds = { { 0xb46492f4, 0xbe02, 0x4cc6, {0x92, 0xf0, 0x6c, 0x36, 0x83, 0x5b, 0x3b, 0x6e} }, { 0xb46492f5, 0xbe02, 0x4cc6, {0x92, 0xf0, 0x6c, 0x36, 0x83, 0x5b, 0x3b, 0x6e} } };
		float Price = 4567.89;
	};
}