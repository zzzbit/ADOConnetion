#pragma once
#import "C:\\Program Files\\Common Files\\System\\ADO\\msado15.dll" \
no_namespace rename("EOF", "adoEOF")
#include <string>
#include <iostream>
using namespace std;
class db_Operator
{
public:
	db_Operator(string dbType,string dbName,string userName,string pwd);
	~db_Operator(void);
	_RecordsetPtr db_Query(_bstr_t sql);
	bool db_Execute(_bstr_t sql);
	bool db_close();
public:
	_ConnectionPtr m_pConn;
	_RecordsetPtr rps;
};

