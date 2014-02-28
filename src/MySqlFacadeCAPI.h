/*
 ============================================================================
 Name        : MySqlFacadeCAPI.c
 Author      : dtsilvers@aol.com
 Created     : 2014-01-30
 Updated     : 2014-02-28
 Version     : 1.001
 License     : MIT - SEE: http://opensource.org/licenses/MIT
 Copyright   : Copyright (c) 2014 by David T. Silvers Sr.
 Description : MySQL Facade C API reducing a dozen MySQL calls down to four.
               Include MySqlFacadeCAPI.h, link this library and libmysql.lib,
               then place the dynamic link library libmysql in your path.
               SEE ALSO: TestMSFCAPI.c
 ============================================================================
 */
#ifndef _DBLIB_H_
#define	_DBLIB_H_
#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
	unsigned long ulRows;
	unsigned int uiFields;
	unsigned long **ppulFieldLengths; /* in case a binary field contains multiple '\0' */
	char ***pppData;
} DataMSF;

void* connectDB(const char *pHost, const int iPort, const char *pDB, const char *pUsr, const char *pPwd);
DataMSF* executeSqlDB(void *pvConn, const char *pSql);
void freeResultDB(DataMSF *pDataMSF);
void closeDB(void *pvConn);

#ifdef __cplusplus
}
#endif
#endif
