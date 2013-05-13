
/* windows defines */
#ifndef __MPEG4_WIN32_H__
#define __MPEG4_WIN32_H__
#define HAVE_IN_PORT_T
#define HAVE_SOCKLEN_T
#define NEED_SDL_VIDEO_IN_MAIN_THREAD
#define _WIN32_WINNT 0x0400
#define _WINSOCKAPI_
#define _INTEGRAL_MAX_BITS 64
#include <windows.h>
#include <winsock2.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>

typedef unsigned __int64 uint64_t;
typedef unsigned __int32 uint32_t;
typedef unsigned __int16 uint16_t;
typedef unsigned __int8 uint8_t;
typedef unsigned __int64 u_int64_t;
typedef unsigned __int32 u_int32_t;
typedef unsigned __int16 u_int16_t;
typedef unsigned __int8 u_int8_t;
typedef __int64 int64_t;
typedef __int32 int32_t;
typedef __int16 int16_t;
typedef __int8  int8_t;
typedef unsigned short in_port_t;
typedef int socklen_t;
typedef int ssize_t;
typedef unsigned int uint;
#define snprintf _snprintf
#define strncasecmp _strnicmp
#define strcasecmp _stricmp

#include <io.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#define write _write
#define lseek _lseek
#define close _close
#define open _open
#define access _access
#define vsnprintf _vsnprintf
#define stat _stati64
#define fstat _fstati64
#define F_OK 0
#define OPEN_RDWR (_O_RDWR | _O_BINARY)
#define OPEN_CREAT (_O_CREAT | _O_BINARY)
#define OPEN_RDONLY (_O_RDONLY | _O_BINARY)
#define srandom srand
#define random rand

#define IOSBINARY ios::binary


#define PATH_MAX MAX_PATH
#define MAX_UINT64 -1
#define D64F "I64d"
#define U64F  "I64u"
#define X64F "I64x"
#define U64  "%"U64F

#define TO_D64(a) (a##I64)
#define TO_U64(a) (a##UI64)


#define __STRING(expr) #expr

#define FOPEN_READ_BINARY  "rb"
#define FOPEN_WRITE_BINARY "wb"

#define UINT64_TO_DOUBLE(a) ((double)((int64_t)(a)))

#define SIZEOF_BOOL 1

#endif
