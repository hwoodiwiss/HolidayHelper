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
			for (string ValidInt : ValidInts)
			{
				Assert::IsTrue(Input::ValidateIntString(ValidInt));
			}

			for (string InvalidInt : InvalidInts)
			{
				Assert::IsFalse(Input::ValidateIntString(InvalidInt));
			}
		}

		TEST_METHOD(ValidateFloatString)
		{

			//Valid floating point numbers, should be true
			for (string Valid : ValidFloats)
			{
				Assert::IsTrue(Input::ValidateFloatString(Valid));
			}


			//Invalid floating point numbers, should be false
			for (string Invalid : InvalidFloats)
			{
				Assert::IsFalse(Input::ValidateFloatString(Invalid));
			}

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


			for (string ValidInt : ValidInts)
			{
				cinSpoof << ValidInt << endl;
				int Expected = stoi(ValidInt);
				int Actual = Input::GetUserInt();

				Assert::AreEqual(Expected, Actual);
				Assert::AreEqual(string(""), coutSpoof.str());

			}

			cin.clear();
			cout.clear();

			stringstream coutExpected;

			for (string InvalidInt : InvalidInts)
			{
				cinSpoof << InvalidInt << endl << 1 << endl; //Have to add a valid int, or GetUserInt will never return
				int Actual = Input::GetUserInt();

				Assert::AreEqual(1, Actual);
				coutExpected << "Please enter a valid number.\n";
			}

			Assert::AreEqual(coutExpected.str(), coutSpoof.str());

			//Restore and cleanup stream buffers
			cin.set_rdbuf(backupCinBuff);
			cout.set_rdbuf(backupCoutBuff);
			cin.clear();
			cout.clear();
		}

		TEST_METHOD(GetUserFloat)
		{
			//Redirect cin
			stringstream cinSpoof;
			auto backupCinBuff = cin.rdbuf();
			cin.set_rdbuf(cinSpoof.rdbuf());

			//redirect cout
			stringstream coutSpoof;
			auto backupCoutBuff = cout.rdbuf();
			cout.set_rdbuf(coutSpoof.rdbuf());


			for (string ValidFloat : ValidFloats)
			{
				cinSpoof << ValidFloat << endl;
				int Expected = stof(ValidFloat);
				int Actual = Input::GetUserFloat();

				Assert::AreEqual(Expected, Actual);
				Assert::AreEqual(string(""), coutSpoof.str());

			}

			cin.clear();
			cout.clear();

			stringstream coutExpected;

			for (string InvalidFloat : InvalidFloats)
			{
				cinSpoof << InvalidFloat << endl << 1 << endl; //Have to add a valid int, or GetUserInt will never return
				int Actual = Input::GetUserFloat();

				Assert::AreEqual(1, Actual);
				coutExpected << "Please enter a valid number.\n";
			}

			Assert::AreEqual(coutExpected.str(), coutSpoof.str());

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

			//Positive ints
			cinSpoof << "10, 20, 30, 40, 50\n";
			vector<int> Expected = { 10, 20, 30, 40, 50 };
			auto Actual = Input::GetUserIntArray();

			Assert::AreEqual(Expected, Actual);

			//Negative ints
			cinSpoof << "-10, -20, -30, -40, -50\n";
			Expected = { -10, -20, -30, -40, -50 };
			Actual = Input::GetUserIntArray();

			Assert::AreEqual(Expected, Actual);

			//Mixed
			cinSpoof << "-10, 20, -30, 40, -50\n";
			Expected = { -10, 20, -30, 40, -50 };
			Actual = Input::GetUserIntArray();

			Assert::AreEqual(Expected, Actual);

			//Single int
			cinSpoof << "10034\n";
			Expected = { 10034 };
			Actual = Input::GetUserIntArray();

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

		private:
			vector<string> ValidInts = { "1", "256", "-556622", "1235448" };
			vector<string> InvalidInts = { "four-thousand", "-ten", "minus ten", "" };

			vector<string> ValidFloats = { "1", "256", "-556622", "1235448", "1.025", "256.1293", "-556622.1231", "1235448.4322342" };
			vector<string> InvalidFloats = { "", "four-thousand", "-ten", "minus ten", "1235448.four", "-fifty.12749", "-134544point1224" };

	};
}
