#pragma once

#include <string>
#include <iostream>
#include "Common.h"

using std::cin;
using std::cout;
using std::endl;
using std::string;

namespace HolidayHelper::Utils
{
	class DllExport Input
	{
	public:
		//Gets a string input from the user, allowing for the desired stream as a param, but with a defailt of std::cin
		static std::string GetUserString(std::istream& stream = cin);

		//Returns a whitespace trimed copy of trimStr
		static std::string Trim(std::string trimStr);

		//Gets an integer input from the user
		static int GetUserInt();

		//Gets a float input from the user
		static float GetUserFloat();

		//Converts a string to all lower case
		static std::string ToLower(std::string value);

		//Converts a string to all upper case
		static std::string ToUpper(std::string value);

		//Validates a string to ensure that it is a valid string representation of an integer
		static bool ValidateIntString(std::string intStr);

		//Validates a string to ensure that it is a valid string representation of a float
		static bool ValidateFloatString(std::string floatStr);
	};


}