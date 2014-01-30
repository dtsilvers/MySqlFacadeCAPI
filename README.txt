 ============================================================================
 Name        : MySqlFacadeCAPI
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
Project developed in Eclipse-Kepler-CPP with MinGW32 on Windows 8.
-----------------------------------------------------------------------------

libMySqlFacadeCAPI.a is built from MinGW32 using MySqlFacadeCAPI.c which 
includes mysql-connector-c-6.1.3-win32\include\mysql.h.

Example:

gcc "-IC:\\Dev\\C\\mysql-connector-c-6.1.3-win32\\include" -O3 -Wall -c 
-fmessage-length=0 -o "src\\MySqlFacadeCAPI.o" "..\\src\\MySqlFacadeCAPI.c" 

ar -r libMySqlFacadeCAPI.a "src\\MySqlFacadeCAPI.o" 

-----------------------------------------------------------------------------

To link with your code, include MySqlFacadeCAPI.h and link MySqlFacadeCAPI.a  
and libmysql.lib, then run with mysql-connector-c-6.1.3-win32\lib\libmysql.dll 

Example:

gcc -O3 -Wall -c -fmessage-length=0 -o "src\\TestMSFCAPI.o" "..\\src\\TestMSFCAPI.c" 

gcc -L../lib -o TestMSFCAPI.exe "src\\TestMSFCAPI.o" -lMySqlFacadeCAPI -llibmysql
 
-----------------------------------------------------------------------------

If using Unix or Linux, follow a similar procedure outlined in the above steps.
