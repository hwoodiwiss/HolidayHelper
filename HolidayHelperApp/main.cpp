#include <HolidayHelperLib/SerializableGuid.h>
#include <Windows.h>

using namespace HolidayHelper::Utils;

int main(int argC, char** argV)
{
	GUID guid;
	if (CoCreateGuid(&guid) != S_OK)
	{
		return 1;
	}

	Serialization::SerializableGuid sGuid = guid;
}