#include "SerializationException.h"

namespace HolidayHelper::Persistence
{
	SerializationException::SerializationException(string ErrorKey, string ErrorVal, map<string, string> ErrorDict, const char* Message) : m_ErrorKey(ErrorKey), m_ErrorVal(ErrorVal), m_ErrorDict(ErrorDict), exception(Message)
	{

	}
}
