// Pilot.cpp: implementation of the CPilot class.
//
//////////////////////////////////////////////////////////////////////

#include "Pilot.h"


extern SQLHENV			 g_hEnv;				// Handle ODBC environment
extern long				 g_lResult;			// result of functions
extern SQLHDBC			 g_hDbc;				// Handle connection
extern unsigned char	 g_strStatus[10];	// Status SQL

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CPilot::CPilot()
{
	m_strPilotName = new char[16];
	m_strPassword  = new char[16];
}

CPilot::~CPilot()
{
	delete m_strPilotName;
	delete m_strPassword;
}


char * CPilot::getPassword()
{
	return m_strPassword;
}

bool CPilot::findByPrimaryKey(int iPrimaryKey)
{
	unsigned char	 strStatus[10];		// Status SQL
	SQLINTEGER		 iErr, iPilotID;
	SQLSMALLINT		 iMlen;
	SQLHSTMT			 sqlhStmt;
	unsigned char   strMsg[200], strlPilotName[16], strlPassword[16];
	unsigned char	 strSql[200]; 
	char				 strPilotID[16];
	
	sprintf(strPilotID, "%d", iPrimaryKey);

												//////////////////////////////////////////////
												//Connect to the datasource Alienation      //
												//////////////////////////////////////////////

	g_lResult = SQLConnect(g_hDbc, (SQLCHAR*) "Alienation", SQL_NTS,
                                     (SQLCHAR*) "", SQL_NTS,
                                     (SQLCHAR*) "", SQL_NTS);
	if ((g_lResult != SQL_SUCCESS) && (g_lResult != SQL_SUCCESS_WITH_INFO))
	{
		printf("Error SQLConnect %d\n",g_lResult);
		SQLGetDiagRec(SQL_HANDLE_DBC, g_hDbc,1, 
		              strStatus, &iErr,strMsg,100,&iMlen);
		printf("%s (%d)\n",strMsg,iErr);
		SQLFreeHandle(SQL_HANDLE_ENV, g_hEnv);
		exit(0);
	}

												//////////////////////////////////////////////
												//Allocate the statement handle and bind    //
												//the columns to variables                  //
												//////////////////////////////////////////////

	g_lResult = SQLAllocHandle(SQL_HANDLE_STMT, g_hDbc, &sqlhStmt);
	if ((g_lResult != SQL_SUCCESS) && (g_lResult != SQL_SUCCESS_WITH_INFO))
	{
		printf("Error in AllocStatement %d\n",g_lResult);
		SQLGetDiagRec(SQL_HANDLE_DBC, g_hDbc,1, strStatus,&iErr,strMsg,100,&iMlen);
		printf("%s (%d)\n",strMsg,iErr);
		SQLDisconnect(g_hDbc);
		SQLFreeHandle(SQL_HANDLE_DBC,g_hDbc);
		SQLFreeHandle(SQL_HANDLE_ENV, g_hEnv);
		return false;
	}
   SQLBindCol(sqlhStmt,1,SQL_C_SLONG , &iPilotID,sizeof(iPilotID),&iErr);
   SQLBindCol(sqlhStmt,2,SQL_C_CHAR , &strlPilotName,16,&iErr);
   SQLBindCol(sqlhStmt,3,SQL_C_CHAR , &strlPassword ,16,&iErr);

												//////////////////////////////////////////////
												//Create the SQL command                    //
												//////////////////////////////////////////////

	strcpy((char *)strSql, (const char *)"SELECT PilotName, Password FROM plt_Pilot ");
	strcat((char *)strSql, (const char *)"WHERE PilotID = ");
	strcat((char *)strSql, (const char *)strPilotID);

	
												//////////////////////////////////////////////
												//Execute the SQL command                   //
												//////////////////////////////////////////////

	g_lResult = SQLExecDirect(sqlhStmt,strSql,SQL_NTS);   
	if ((g_lResult != SQL_SUCCESS) && (g_lResult != SQL_SUCCESS_WITH_INFO))
	{
		printf("Error in SQLExecStatement %d\n",g_lResult);
		SQLGetDiagRec(SQL_HANDLE_DBC, g_hDbc,1, strStatus,&iErr,strMsg,100,&iMlen);
		printf("%s (%d)\n",strMsg,iErr);
		SQLFreeHandle(SQL_HANDLE_STMT,sqlhStmt);
		SQLDisconnect(g_hDbc);
		SQLFreeHandle(SQL_HANDLE_DBC,g_hDbc);
		SQLFreeHandle(SQL_HANDLE_ENV, g_hEnv);
		return false;
	}

												//////////////////////////////////////////////
												//Fetch the row (should opnly be one in     //
												//this case, needs a check to make sure,    //
												//but access dosnt seem to send back the    //
												//number of rows retrieved                  //
												//////////////////////////////////////////////

	g_lResult = SQLFetch(sqlhStmt);

	if (g_lResult == SQL_NO_DATA)
		return false;

												//////////////////////////////////////////////
												//Set the member variables                  //
												//////////////////////////////////////////////

	m_iPilotID = iPilotID;
	strcpy(m_strPilotName, (const char *)strlPilotName);
	strcpy(m_strPassword,  (const char *)strlPassword);
	
	return true;
}

bool CPilot::findByPilotName(char *strPilotName)
{
	unsigned char	 strStatus[10];		// Status SQL
	SQLINTEGER		 iErr, iPilotID;
	SQLSMALLINT		 iMlen;
	SQLHSTMT			 sqlhStmt;
	unsigned char   strMsg[200], strlPilotName[16], strlPassword[16];
	unsigned char	 strSql[200]; 

												//////////////////////////////////////////////
												//Connect to the datasource Alienation      //
												//////////////////////////////////////////////

	g_lResult = SQLConnect(g_hDbc, (SQLCHAR*) "Alienation", SQL_NTS,
                                     (SQLCHAR*) "", SQL_NTS,
                                     (SQLCHAR*) "", SQL_NTS);
	if ((g_lResult != SQL_SUCCESS) && (g_lResult != SQL_SUCCESS_WITH_INFO))
	{
		printf("Error SQLConnect %d\n",g_lResult);
		SQLGetDiagRec(SQL_HANDLE_DBC, g_hDbc,1, 
		              strStatus, &iErr,strMsg,100,&iMlen);
		printf("%s (%d)\n",strMsg,iErr);
		SQLFreeHandle(SQL_HANDLE_ENV, g_hEnv);
		exit(0);
	}

												//////////////////////////////////////////////
												//Allocate the statement handle and bind    //
												//the columns to variables                  //
												//////////////////////////////////////////////

	g_lResult = SQLAllocHandle(SQL_HANDLE_STMT, g_hDbc, &sqlhStmt);
	if ((g_lResult != SQL_SUCCESS) && (g_lResult != SQL_SUCCESS_WITH_INFO))
	{
		printf("Error in AllocStatement %d\n",g_lResult);
		SQLGetDiagRec(SQL_HANDLE_DBC, g_hDbc,1, strStatus,&iErr,strMsg,100,&iMlen);
		printf("%s (%d)\n",strMsg,iErr);
		SQLDisconnect(g_hDbc);
		SQLFreeHandle(SQL_HANDLE_DBC,g_hDbc);
		SQLFreeHandle(SQL_HANDLE_ENV, g_hEnv);
		return false;
	}
   SQLBindCol(sqlhStmt,1,SQL_C_SLONG , &iPilotID,sizeof(iPilotID),&iErr);
   SQLBindCol(sqlhStmt,2,SQL_C_CHAR , &strlPilotName,16,&iErr);
   SQLBindCol(sqlhStmt,3,SQL_C_CHAR , &strlPassword ,16,&iErr);

												//////////////////////////////////////////////
												//Create the SQL command                    //
												//////////////////////////////////////////////

	strcpy((char *)strSql, (const char *)"SELECT PilotID, PilotName, Password FROM plt_Pilot ");
	strcat((char *)strSql, (const char *)"WHERE PilotName = '");
	strcat((char *)strSql, (const char *)strPilotName);
	strcat((char *)strSql, (const char *)"'");

	
												//////////////////////////////////////////////
												//Execute the SQL command                   //
												//////////////////////////////////////////////

	g_lResult = SQLExecDirect(sqlhStmt,strSql,SQL_NTS);   
	if ((g_lResult != SQL_SUCCESS) && (g_lResult != SQL_SUCCESS_WITH_INFO))
	{
		printf("Error in SQLExecStatement %d\n",g_lResult);
		SQLGetDiagRec(SQL_HANDLE_DBC, g_hDbc,1, strStatus,&iErr,strMsg,100,&iMlen);
		printf("%s (%d)\n",strMsg,iErr);
		SQLFreeHandle(SQL_HANDLE_STMT,sqlhStmt);
		SQLDisconnect(g_hDbc);
		SQLFreeHandle(SQL_HANDLE_DBC,g_hDbc);
		SQLFreeHandle(SQL_HANDLE_ENV, g_hEnv);
		return false;
	}

												//////////////////////////////////////////////
												//Fetch the row (should opnly be one in     //
												//this case, needs a check to make sure,    //
												//but access dosnt seem to send back the    //
												//number of rows retrieved                  //
												//////////////////////////////////////////////

	g_lResult = SQLFetch(sqlhStmt);

	if (g_lResult == SQL_NO_DATA)
		return false;

												//////////////////////////////////////////////
												//Set the member variables                  //
												//////////////////////////////////////////////

	m_iPilotID = iPilotID;
	strcpy(m_strPilotName, (const char *)strlPilotName);
	strcpy(m_strPassword,  (const char *)strlPassword);
	
	return true;
}
