#ifndef __LIB_UC_H__
#define __LIB_UC_H__

#ifdef LIB_UC_EXPORTS
#define LIB_UC_API __declspec(dllexport)
#else
#define LIB_UC_API __declspec(dllimport)
#endif

#define LIB_UC_VERSION "0.0.1"
#if defined(_WIN64)
	#define _UC_PLATFORM "x64"
#else
	#define _UC_PLATFORM ""
#endif

#endif