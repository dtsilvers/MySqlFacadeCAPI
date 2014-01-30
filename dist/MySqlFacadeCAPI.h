/*
 ============================================================================
 Name        : MySqlFacadeCAPI.c
 Author      : dtsilvers@aol.com
 Date        : 2014-01-30
 Version     : 1.00
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

extern void* connectDB(const char *pHost, const int iPort, const char *pDB, const char *pUsr, const char *pPwd);
extern DataMSF* executeSqlDB(void *pvConn, const char *pSql);
extern void freeResultDB(DataMSF *pDataMSF);
extern void closeDB(void *pvConn);

#ifdef __cplusplus
}
#endif
#endif
