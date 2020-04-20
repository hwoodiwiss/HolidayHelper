#pragma once
#include "CppUnitTest.h"
#include <Windows.h>
#include <HolidayHelperLib/SerializableGuid.h>
#include <HolidayHelperLib/Dataset.h>


namespace Microsoft::VisualStudio::CppUnitTestFramework
{
	//Add a tostring helper for GUID for the unit test framework
	template<> static std::wstring ToString<GUID>(const GUID& t)
	{
		return HolidayHelper::Persistence::GuidToWString(t, true);
	}

	//Add a tostring helper for DataSet<int> for the unit test framework
	template<> static std::wstring ToString <HolidayHelper::Data::DataSet<int>>(const class HolidayHelper::Data::DataSet<int>& t)
	{
		std::wstringstream wss;
		for (auto val : t)
		{
			wss << val << ", ";
		}

		return wss.str();
	}

	//Add a tostring helper for vector<int> for the unit test framework
	template<> static std::wstring ToString <vector<int>>(const vector<int>& t)
	{
		std::wstringstream wss;
		for (auto val : t)
		{
			wss << val << ", ";
		}

		return wss.str();
	}

	//Add a tostring helper for vector<string> for the unit test framework
	template<> static std::wstring ToString<vector<string>>(const vector<string>& strParts)
	{
		std::wstringstream wss;
		for (auto Part : strParts)
		{
			std::wstring WidePart = std::wstring(Part.length(), ' ');
			MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, Part.data(), -1, WidePart.data(), Part.length());
			wss << WidePart << ", ";
		}

		return wss.str();
	}
}