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
}