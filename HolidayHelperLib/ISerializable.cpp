#include "ISerializable.h"

namespace HolidayHelper::Persistence
{
	inline std::string ISerializable::InStreamToString(std::istream& in)
	{
		std::streampos prevPos = in.tellg();
		char curr;
		int strCnt = 0;
		do
		{
			strCnt++;
			in.get(curr);
		} while (curr != '\0');
		in.seekg(prevPos);
		char* streamString = new char[strCnt];
		in.read(streamString, strCnt);
		return std::string(streamString);
	}
}
