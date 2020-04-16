#pragma once
#include <exception>
#include "Common.h"

using std::exception;

namespace HolidayHelper::Persistence
{


	class SerializationException : public exception
	{
	public:
		SerializationException(string ErrorKey, string ErrorVal, map<string, string> ErrorDict, const char* Message);

	private:
		map<string, string> m_ErrorDict;
		string m_ErrorKey;
		string m_ErrorVal;
	};

}