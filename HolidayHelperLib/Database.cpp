#include "Database.h"

Database::Database(wstring ConnectionString)
{
	SQLSetEnvAttr(mh_SqlEnvironment, SQL_ATTR_ODBC_VERSION, SQL_OV_ODBC3_80);

	SQLAllocHandle(SQL_HANDLE_DBC, mh_SqlEnvironment, &mh_DbConnection);
}
