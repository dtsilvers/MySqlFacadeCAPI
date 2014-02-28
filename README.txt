 ==============================================================================
 Name        : MySqlFacadeCAPI
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
 ==============================================================================
  Revision system: M.mfb
  
    M = major feature enhancement
    m = minor feature enhancement
    f = fix
    b = compiler/build/aesthetics
  
  =============================================================================
  Revison: 1.001                                               Date: 2014-02-28
     
    This is not a bug fix or feature enhancement as much as it is a compiler
    specific change, meaning that all files in dist remain unchanged.
  	
  Summary: 
  	
    Alleviate C compiler configuration issues by removing C++ comments.
  	
  Details: 
  	
    Previously MySqlFacadeCAPI.h would compile with a C/C++ compiler config,
    however, it could cause errors when compiled with a C compiler config.
  	 
  Code changes: MySqlFacadeCAPI.c, MySqlFacadeCAPI.h 
  
    Remove commented extern function declarations from MySqlFacadeCAPI.h,
    then move declarations from MySqlFacadeCAPI.c to MySqlFacadeCAPI.h.    
    Also remove one line of inessential code in MySqlFacadeCAPI.c.
   
  -----------------------------------------------------------------------------
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
  and libmysql.lib. Run with mysql-connector-c-6.1.3-win32\lib\libmysql.dll 

  Example:

    gcc -O3 -Wall -c -fmessage-length=0 -o "src\\TestMSFCAPI.o" 
    "..\\src\\TestMSFCAPI.c" 

    gcc -L../lib -o TestMSFCAPI.exe "src\\TestMSFCAPI.o" -lMySqlFacadeCAPI 
    -llibmysql
 
  -----------------------------------------------------------------------------

  If using Unix or Linux, follow a similar procedure outlined above
