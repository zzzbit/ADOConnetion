#include "StdAfx.h"
#include "db_Operator.h"


db_Operator::db_Operator(string dbType,string dbName,string userName,string pwd)
{
	CoInitialize(NULL);
	m_pConn.CreateInstance(_uuidof(Connection));
	string strCon;
		//strCon = "Provider=SQLOLEDB.1;Persist Security Info=False;User ID="+userName+ ";Password=" +pwd+ ";Initial Catalog="+dbName+";Data Source=(local);Integrated Security=SSPI;";
		strCon = "DSN="+dbType+";server=localhost;database="+dbName;
	try
	{
	    m_pConn->Open(strCon.c_str(),userName.c_str(),pwd.c_str(),adModeUnknown);
	}
	catch(_com_error &e)
	{
		MessageBox(NULL, e.Description(), _T("ERROR"), MB_OK); 
	}
}

_RecordsetPtr db_Operator::db_Query(_bstr_t sql)
{   rps=NULL;
	try
	{
		rps.CreateInstance("ADODB.Recordset");
        rps->Open(sql,
           _variant_t((IDispatch*)m_pConn,true),
           adOpenStatic,
           adLockOptimistic,
           adCmdText);
	}
	catch(_com_error &ce)
	{	printf("wrong:sql");
		_bstr_t error;
		error = ce.Description();
	}
	return rps;
}
bool db_Operator::db_Execute(_bstr_t sql)
{
	try
	{
		m_pConn->Execute(sql,NULL,adCmdText);
		return true;
	}
	catch(_com_error &ce)
	{
		_bstr_t error;
		error = ce.Description();
		return false;
	}
}
bool db_Operator::db_close()
{	  
	if(rps != NULL)
		rps->Close();
	m_pConn->Close();
	CoUninitialize();
	return true;
}

db_Operator::~db_Operator(void)
{
	CoUninitialize(); 
}
