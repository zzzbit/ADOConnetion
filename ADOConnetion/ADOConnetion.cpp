// ADOConnetion.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "db_Operator.h"



int _tmain(int argc, _TCHAR* argv[])
{	string dbName="student";
    string userName="root";
	string pwd="root";
	_bstr_t sql="insert into student values('不是吧')";
	_bstr_t featureTypeId = 2;
	_bstr_t biImageId = 126;
	_bstr_t sql2="SELECT * FROM student";
	_variant_t name;
	char x[20];
	int y;
	char tmp[400];
	char tablename[50]="info";

	printf("input x y\n");
	scanf("%s %d",&x,&y);
	fflush(stdin);
	printf("input over\n");
	db_Operator *dbo=new db_Operator("mysql",dbName,userName,pwd);

	sprintf(tmp,"insert into %s(name,age) values('%s',%d)",tablename,x,y);
	dbo->db_Execute(tmp);

	sprintf(tmp,"select * from %s",tablename);
	_RecordsetPtr rsp = dbo->db_Query(tmp);
	try{
		while(!rsp->adoEOF){
			name=rsp->GetCollect("name");
			printf("%s %d\n",(char *)(_bstr_t)name,(int)rsp->GetCollect("age"));
			rsp->MoveNext();
		}
	}
	catch(_com_error &e){
		printf("no");

	}
	dbo->db_close();
	system("pause");
	return 0;
}