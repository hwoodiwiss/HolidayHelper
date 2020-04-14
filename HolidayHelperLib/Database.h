#pragma once
#include <sql.h>
#include <sqlext.h>
#include <string>

using std::wstring;

#define SqlTry(f) { \
	RETCODE ret = f; \
	if(ret == SQL_ERROR) \
	{ \
	\
	} \
}


class Database
{
public:
	Database(wstring ConnectionString);

private:
	SQLHENV mh_SqlEnvironment;
	SQLHDBC mh_DbConnection;
	SQLHSTMT mh_Statement;
	wstring m_ConnectionString;
	wstring m_QueryString;
};
