#include "TestsCommon.h"
#include <time.h>
#include <random>
#include <sstream>
#include <HolidayHelperLib/Input.h>

using std::stringstream;
using namespace HolidayHelper::Utils;

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

		TEST_METHOD(GetUserInt)
		{
			//Redirect cin
			stringstream cinSpoof;
			auto backupCinBuff = cin.rdbuf();
			cin.set_rdbuf(cinSpoof.rdbuf());

			//redirect cout
			stringstream coutSpoof;
			auto backupCoutBuff = cout.rdbuf();
			cout.set_rdbuf(coutSpoof.rdbuf());

			//Set up the buffer with an invalid integer followed by a valid input on the next line
			//This should trigger an invalid number response at least once
			cinSpoof << "thirty-four" << std::endl << 34;

			int Expected = 34;



			string coutExpected = "Please enter a valid number.\n";

			int Actual = Input::GetUserInt();

			Assert::AreEqual(Expected, Actual);
			Assert::AreEqual(coutExpected, coutSpoof.str());

			//Restore and cleanup stream buffers
			cin.set_rdbuf(backupCinBuff);
			cout.set_rdbuf(backupCoutBuff);
			cin.clear();
			cout.clear();
		}

		TEST_METHOD(GetUserIntArray)
		{
			//Redirect cin
			stringstream cinSpoof;
			auto backupCinBuff = cin.rdbuf();
			cin.set_rdbuf(cinSpoof.rdbuf());

			cinSpoof << "10, 20, 30, 40, 50\n";
			vector<int> Expected = { 10, 20, 30, 40, 50 };
			auto Actual = Input::GetUserIntArray();

			Assert::AreEqual(Expected, Actual);

			//Restore and cleanup stream buffers
			cin.set_rdbuf(backupCinBuff);
			cin.clear();
		}

		TEST_METHOD(Split)
		{
			vector<string> Expected = { "The", "quick", "brown", "fox", "jumped", "over", "the", "lazy", "dog" };
			string Input = "The quick brown fox jumped over the lazy dog";

			auto Actual = Input::Split(Input, ' ');

			Assert::AreEqual(Expected, Actual);
		}
	};
}
