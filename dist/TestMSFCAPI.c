/*
 ============================================================================
 Name        : TestMSFCAPI.c
 Author      : dtsilvers@aol.com
 Date        : 2014-01-30
 Version     : 1.00
 License     : MIT - SEE: http://opensource.org/licenses/MIT
 Copyright   : Copyright (c) 2014 by David T. Silvers Sr.
 Description : Tester for MySqlFacadeCAPI
               Include MySqlFacadeCAPI.h, link this library and libmysql.lib,
               then place the dynamic link library libmysql in your path.
 ============================================================================
 */
#include <stdio.h>
#include <stdlib.h>
#include "MySqlFacadeCAPI.h"

int main(void) {
	void *pvConn;
	if((pvConn = connectDB("localhost", 3306, "mysql", "root", "")) != NULL) { /* host/port/db/usr/pwd*/
		DataMSF *pDataMSF;
		if((pDataMSF = executeSqlDB(pvConn, "select * from user")) != NULL) {
			unsigned long r, f;
			printf("rows: %lu, fields: %u\n", pDataMSF->ulRows, pDataMSF->uiFields);
			puts("-----------------------------------------------------------------------------");
			for(r = 0; r < pDataMSF->ulRows; r++) {
				for(f = 0; f < pDataMSF->uiFields; f++)
					if(pDataMSF->pppData[r][f] != NULL)
						printf("%.*s\t", (int)pDataMSF->ppulFieldLengths[r][f], pDataMSF->pppData[r][f]);
				puts("\n-----------------------------------------------------------------------------");
			}
			freeResultDB(pDataMSF);
		} else
			fprintf(stderr, "ERROR: Executing SQL statement!\n");
		closeDB(pvConn);
	} else
		fprintf(stderr, "ERROR: Connecting to Database!\n");
	puts("Finished!");
	return EXIT_SUCCESS;
}
