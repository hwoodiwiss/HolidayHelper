#include "Database.h"
#include <filesystem>

namespace fs = std::filesystem;

namespace HolidayHelper::Persistence
{

	bool Database::Initialise()
	{
		if (SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &mh_SqlEnvironment) != SQL_SUCCESS)
		{
			return false;
		}

		if (SQLSetEnvAttr(mh_SqlEnvironment, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, 0) != SQL_SUCCESS)
		{
			return false;
		}

		if (SQLAllocHandle(SQL_HANDLE_DBC, mh_SqlEnvironment, &mh_DbConnection) != SQL_SUCCESS)
		{
			return false;
		}
		

		fs::path path = fs::absolute(fs::path(L".\\Data.mdb"));
		wstring conStr = L"Provider=Microsoft.ACE.OLEDB.12.0;Data Source=" + path.wstring() + L";Persist Security Info=False";
		auto ret = SQLDriverConnect(mh_DbConnection, NULL, (SQLWCHAR*)conStr.c_str(), SQL_NTS, NULL, NULL, NULL, NULL);
		if (ret != SQL_SUCCESS)
		{
			wchar_t sqlState[5];
			SQLINTEGER* sqlN = 0;
			wchar_t err[1000];
			SQLSMALLINT* len = 0;

			SQLGetDiagRec(SQL_HANDLE_DBC, mh_DbConnection, 1, sqlState, sqlN, err, 1000, len);
			return false;
		}

		return true;
	}

}
