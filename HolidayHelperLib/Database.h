#pragma once
#include <Windows.h>
#include <sql.h>
#include <sqlext.h>
#include <string>
#include "Common.h"

using std::wstring;

namespace HolidayHelper::Persistence
{

	struct ConnectionInfo
	{
		wstring Driver;
		wstring Server;
		wstring Port;
		wstring Database;
	};

	class DllExport Database
	{
		class ConnectionInfo
		{

		};

	public:
		//Initial setup done in init rather than constructor, so that errors can be handled more gracefully
		bool Initialise();

	private:
		SQLHENV mh_SqlEnvironment;
		SQLHDBC mh_DbConnection;
		SQLHSTMT mh_Statement;
		wstring m_ConnectionString;
		wstring m_QueryString;
	};

}
