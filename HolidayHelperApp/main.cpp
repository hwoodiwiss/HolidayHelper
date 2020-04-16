#include <HolidayHelperLib/SerializableGuid.h>
#include <HolidayHelperLib/Database.h>
#include <Windows.h>


int main(int argC, char** argV)
{
	GUID guid;
	if (CoCreateGuid(&guid) != S_OK)
	{
		return 1;
	}




	
}