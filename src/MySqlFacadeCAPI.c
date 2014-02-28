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
#include <stdio.h>
#include <stdlib.h>
#include <mysql.h>
#include "MySqlFacadeCAPI.h"

void* connectDB(const char *pHost, const int iPort, const char *pDB, const char *pUsr, const char *pPwd) {
	MYSQL *conn;
	void *pvConn = NULL;
	if(((conn = mysql_init(NULL)) != NULL) /* conn/host/usr/pwd/db/port/socket/flags */
	&& (mysql_real_connect(conn, pHost, pUsr, pPwd, pDB, iPort, NULL, 0) != NULL))
		pvConn = conn;
return(pvConn);
}

DataMSF* executeSqlDB(void *pvConn, const char *pSql) {
	DataMSF *pDataMSF = NULL;
	if((pvConn == NULL) || (pSql == NULL))
		return(NULL);
	if(mysql_query(pvConn, pSql) == 0) {
		MYSQL_RES *result;
		pDataMSF = malloc(sizeof(DataMSF));
		pDataMSF->ulRows = 0;
		pDataMSF->uiFields = 0;
		pDataMSF->ppulFieldLengths = NULL;
		pDataMSF->pppData = NULL;
		if((result = mysql_store_result(pvConn)) != NULL)	{
			unsigned long *lengths, f, r = 0;
			MYSQL_ROW row; /* defined as char** row */
			pDataMSF->ulRows = mysql_num_rows(result);
			pDataMSF->uiFields = mysql_num_fields(result);
			pDataMSF->pppData = malloc(pDataMSF->ulRows * sizeof(char*));
			memset(pDataMSF->pppData, 0, pDataMSF->ulRows * sizeof(char*));
			pDataMSF->ppulFieldLengths = malloc(pDataMSF->ulRows * sizeof(unsigned long*));
			memset(pDataMSF->ppulFieldLengths, 0, pDataMSF->ulRows * sizeof(unsigned long*));
			while((row = mysql_fetch_row(result)) != NULL) {
				lengths = mysql_fetch_lengths(result);
				pDataMSF->pppData[r] = malloc(pDataMSF->uiFields * sizeof(char*));
				memset(pDataMSF->pppData[r], 0, pDataMSF->uiFields * sizeof(char*));
				pDataMSF->ppulFieldLengths[r] = malloc(pDataMSF->uiFields * sizeof(unsigned long));
				memset(pDataMSF->ppulFieldLengths[r], 0, pDataMSF->uiFields * sizeof(unsigned long));
				for(f = 0; f < pDataMSF->uiFields; f++) {
					pDataMSF->ppulFieldLengths[r][f] = lengths[f];
					if(row[f] != NULL) { /* If field in DB is not NULL, process both binary and string */
						pDataMSF->pppData[r][f] = malloc(pDataMSF->ppulFieldLengths[r][f] + 1);
						memcpy(pDataMSF->pppData[r][f],  row[f], pDataMSF->ppulFieldLengths[r][f]);
						pDataMSF->pppData[r][f][pDataMSF->ppulFieldLengths[r][f]] = '\0';
					}
				}
				r++;
			}
			mysql_free_result(result);
		} else if((pDataMSF->uiFields = mysql_field_count(pvConn)) == 0) /* select failed if column data but no row data */
			pDataMSF->ulRows = mysql_affected_rows(pvConn); /* could be update/insert/delete */
	}
return(pDataMSF);
}

void freeResultDB(DataMSF *pDataMSF) {
	int r, f;
	if(pDataMSF != NULL) {
		if(pDataMSF->pppData != NULL) {
			for(r = 0; r < pDataMSF->ulRows; r++) {
				for(f = 0; f < pDataMSF->uiFields; f++) {
					if(pDataMSF->pppData[r][f] != NULL)
						free(pDataMSF->pppData[r][f]);
				}
				free(pDataMSF->pppData[r]);
				free(pDataMSF->ppulFieldLengths[r]);
			}
			free(pDataMSF->pppData);
			free(pDataMSF->ppulFieldLengths);
		}
		free(pDataMSF);
	}
return;
}

void closeDB(void *pvConn) {
	mysql_close(pvConn);
}
