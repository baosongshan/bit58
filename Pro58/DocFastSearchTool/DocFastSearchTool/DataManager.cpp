#include"DataManager.h"
#include"Config.h"

#pragma comment(lib, "./sqlite/sqlite3.lib")

SqliteManager::SqliteManager():m_db(nullptr)
{}
SqliteManager::~SqliteManager()
{
	Close();
}
void SqliteManager::Open(const string &path)
{
	int rc = sqlite3_open(path.c_str(), &m_db);
	if (rc != SQLITE_OK)
	{
		fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(m_db));
		exit(0);
	}
	else
		fprintf(stderr, "Opened database successfully\n");
}
void SqliteManager::Close()
{
	if(m_db)
	{
		int rc = sqlite3_close(m_db);
		if (rc != SQLITE_OK)
		{
			fprintf(stderr, "Can't close database: %s\n", sqlite3_errmsg(m_db));
			exit(0);
		}
		else
			fprintf(stderr, "Closeed database successfully\n");
	}
}
void SqliteManager::ExecuteSql(const string &sql)
{

	char *zErrMsg = 0;
	int rc = sqlite3_exec(m_db, sql.c_str(), 0, 0, &zErrMsg);
	if (rc != SQLITE_OK)
	{
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
	}
	else
	{
		fprintf(stdout, "Operation done successfully\n");
	}
}

void SqliteManager::GetResultTable(const string &sql, char **&ppRet, int &row, int &col)
{
	char *zErrMsg = 0;
	int rc = sqlite3_get_table(m_db, sql.c_str(), &ppRet, &row, &col, &zErrMsg);
	if(rc != SQLITE_OK)
	{
		 fprintf(stderr, "get result table error: %s\n", sqlite3_errmsg(m_db));
		 exit(0);
	}
	else
		fprintf(stderr, "Get result table successfully\n");
}

///////////////////////////////////////////////////////////////////////
DataManager::DataManager()
{
	//创建数据库
	m_dbmgr.Open(DOC_DB);
	//创建表
	InitSqlite();
}
DataManager::~DataManager()
{}

void DataManager::InitSqlite()
{
	char sql[SQL_BUFFER_SIZE] = {0};
	sprintf(sql, "create table if not exists %s (id INTEGER PRIMARY KEY autoincrement, doc_name text, doc_path text)",
			DOC_TABLE);
	m_dbmgr.ExecuteSql(sql);
}

void DataManager::InsertDoc(const string &path, const string &doc)
{
	char sql[SQL_BUFFER_SIZE] = {0};
	sprintf(sql, "insert into %s values('%s', '%s')", DOC_TABLE, doc.c_str(), path.c_str());
	m_dbmgr.ExecuteSql(sql);
}
void DataManager::DeleteDoc(const string &path, const string &doc)
{
	char sql[SQL_BUFFER_SIZE] = {0};
	sprintf(sql, "delete from %s where doc_path='%s' and doc_name='%s'",
			DOC_TABLE, path.c_str(), doc.c_str());
	m_dbmgr.ExecuteSql(sql);
}
void DataManager::GetDocs(const string &path, multiset<string> &docs)
{
	char sql[SQL_BUFFER_SIZE] = {0};
	sprintf(sql, "select * from %s where doc_path='%s'",
			DOC_TABLE, path.c_str());

	int row=0, col=0;
	char **ppRet = 0;
	m_dbmgr.GetResultTable(sql, ppRet, row, col);

	for(int i=1; i<=row; ++i)
		docs.insert(ppRet[i]);

	//释放结果表
	sqlite3_free_table(ppRet);
}