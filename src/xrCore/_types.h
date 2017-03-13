#pragma once
#ifndef TYPES_H
#define TYPES_H
#include <stdlib.h> // _MAX_PATH

// Type defs
#ifdef WINDOWS
typedef signed char s8;
typedef unsigned char u8;

typedef signed short s16;
typedef unsigned short u16;

typedef signed int s32;
typedef unsigned int u32;

typedef signed __int64 s64;
typedef unsigned __int64 u64;

typedef float f32;
typedef double f64;

typedef char* pstr;
typedef const char* pcstr;

typedef u32 threadId_t;
#ifdef defined(WINDOWS) && defined(_MSC_VER)
typedef signed __int64 s64;
typedef unsigned __int64 u64;
#elif defined(WINDOWS) && defined(__GNUC__)
typedef long long s64;
typedef unsigned long long u64;
#endif // WINDOWS && _MSC_VER

#else // POSIX
#include <stdint.h>
typedef int8_t s8;
typedef uint8_t u8;

typedef int16_t s16;
typedef uint16_t u16;

typedef int32_t s32;
typedef uint32_t u32;

typedef pthread_t threadId_t;

typedef int64_t s64;
typedef uint64_t u64;

typedef float f32;
typedef double f64;

typedef char* pstr;
typedef const char* pcstr;
#endif // WINDOWS

// Type limits
#define type_max(T) (std::numeric_limits<T>::max())
#define type_min(T) (-std::numeric_limits<T>::max())
#define type_zero(T) (std::numeric_limits<T>::min())
#define type_epsilon(T) (std::numeric_limits<T>::epsilon())

#define int_max type_max(int)
#define int_min type_min(int)
#define int_zero type_zero(int)

#define flt_max type_max(float)
#define flt_min type_min(float)

#define flt_zero type_zero(float)
#define flt_eps type_epsilon(float)

#define dbl_max type_max(double)
#define dbl_min type_min(double)
#define dbl_zero type_zero(double)
#define dbl_eps type_epsilon(double)

typedef char string16[16];
typedef char string32[32];
typedef char string64[64];
typedef char string128[128];
typedef char string256[256];
typedef char string512[512];
typedef char string1024[1024];
typedef char string2048[2048];
typedef char string4096[4096];

typedef char string_path[2 * _MAX_PATH];

// XXX: Replace __interface with either struct or class. MS defines it as struct for COM, but this project is C++.
#ifdef WINDOWS
#define xr_pure_interface __interface
#else // POSIX
#define xr_pure_interface struct
#endif // WINDOWS

#endif
