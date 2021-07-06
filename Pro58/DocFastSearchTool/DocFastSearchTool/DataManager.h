#pragma once

#include"Common.h"

//封装sqlite
class SqliteManager
{
public:
	SqliteManager();
	~SqliteManager();
public:
	void Open(const string &path);     //打开/创建数据库
	void Close();                      //关闭数据库
	void ExecuteSql(const string &sql);//执行sql
	void GetResultTable(const string &sql, char **&ppRet, int &row, int &col);
private:
	sqlite3 *m_db;
};



//封装数据管理类
class DataManager
{
public:
	DataManager();
	~DataManager();
public:
	void InitSqlite();
public:
	void Search(const string &key, vector<pair<string,string>> &doc_path);
public:
	void InsertDoc(const string &path, const string &doc);
	void DeleteDoc(const string &path, const string &doc);
	void GetDocs(const string &path, multiset<string> &docs);
	
private:
	SqliteManager m_dbmgr;
};