#include "CppUnitTest.h"
#include <time.h>
#include <random>
#include <sstream>
#include <HolidayHelperLib/Input.h>

using namespace HolidayHelper::Utils;

namespace Microsoft::VisualStudio::CppUnitTestFramework
{
	
}

using namespace Microsoft::VisualStudio::CppUnitTestFramework;



namespace HolidayHelperTest::Utils
{
	TEST_CLASS(InputTests)
	{
	public:
		TEST_METHOD(Trim)
		{
			//Set up test data
			std::string testVal = "    Hello World\t    ";

			//Set up expected value
			std::string expected = "Hello World";


			auto actual = Input::Trim(testVal);
			Assert::AreEqual(expected, actual);
		}

		TEST_METHOD(ToLower)
		{
			std::string testValPascal = "Hello World";
			std::string testValMixed = "HeLlO WOrlD";
			std::string testValUpper = "HELLO WORLD";
			std::string testValLower = "hello world";

			std::string expected = "hello world";

			auto actual = Input::ToLower(testValPascal);
			Assert::AreEqual(expected, actual);

			actual = Input::ToLower(testValMixed);
			Assert::AreEqual(expected, actual);
			
			actual = Input::ToLower(testValUpper);
			Assert::AreEqual(expected, actual);
			
			actual = Input::ToLower(testValLower);
			Assert::AreEqual(expected, actual);

		}		
		
		TEST_METHOD(ToUpper)
		{
			std::string testValPascal = "Hello World";
			std::string testValMixed = "HeLlO WOrlD";
			std::string testValUpper = "HELLO WORLD";
			std::string testValLower = "hello world";

			std::string expected = "HELLO WORLD";

			auto actual = Input::ToUpper(testValPascal);
			Assert::AreEqual(expected, actual);

			actual = Input::ToUpper(testValMixed);
			Assert::AreEqual(expected, actual);
			
			actual = Input::ToUpper(testValUpper);
			Assert::AreEqual(expected, actual);
			
			actual = Input::ToUpper(testValLower);
			Assert::AreEqual(expected, actual);

		}

		TEST_METHOD(ValidateIntString)
		{
			//Empty string
			Assert::IsFalse(Input::ValidateIntString(""));

			Assert::IsTrue(Input::ValidateIntString("1"));
			Assert::IsTrue(Input::ValidateIntString("256"));
			Assert::IsTrue(Input::ValidateIntString("-556622"));
			Assert::IsTrue(Input::ValidateIntString("1235448"));

			Assert::IsFalse(Input::ValidateIntString("four-thousand"));
			Assert::IsFalse(Input::ValidateIntString("-ten"));
			Assert::IsFalse(Input::ValidateIntString("minus ten"));
		}

		TEST_METHOD(ValidateFloatString)
		{
			//Empty string
			Assert::IsFalse(Input::ValidateFloatString(""));

			//Valid floating point numbers, should be true
			Assert::IsTrue(Input::ValidateFloatString("1"));
			Assert::IsTrue(Input::ValidateFloatString("256"));
			Assert::IsTrue(Input::ValidateFloatString("-556622"));
			Assert::IsTrue(Input::ValidateFloatString("1235448"));
			Assert::IsTrue(Input::ValidateFloatString("1.025"));
			Assert::IsTrue(Input::ValidateFloatString("256.1293"));
			Assert::IsTrue(Input::ValidateFloatString("-556622.1231"));
			Assert::IsTrue(Input::ValidateFloatString("1235448.4322342"));

			//Invalid floating point numbers, should be false
			Assert::IsFalse(Input::ValidateFloatString("four-thousand"));
			Assert::IsFalse(Input::ValidateFloatString("-ten"));
			Assert::IsFalse(Input::ValidateFloatString("minus ten"));
			Assert::IsFalse(Input::ValidateFloatString("1235448.four"));
			Assert::IsFalse(Input::ValidateFloatString("-fifty.12749"));
			Assert::IsFalse(Input::ValidateFloatString("-134544point1224"));
		}

	};
}
