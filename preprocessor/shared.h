/*===================================================================================================
  File:                    shared.h
  Author:                  Jonathan Livingstone
  Email:                   seagull127@ymail.com
  Licence:                 Public Domain
                           No Warranty is offered or implied about the reliability,
                           suitability, or usability
                           The use of this code is at your own risk
                           Anyone can use this code, modify it, sell it to terrorists, etc.
  ===================================================================================================*/

#if !defined(_SHARED_H)

#include <stdint.h>
#include <stdarg.h>

typedef uint64_t Uint64;
typedef uint32_t Uint32;
typedef uint16_t Uint16;
typedef uint8_t Uint8;

typedef int64_t Int64;
typedef int32_t Int32;
typedef int16_t Int16;
typedef int8_t Int8;

typedef bool Bool;
typedef void Void;
typedef char Char;

typedef Int32 Int; // Int guaranteed to be 4 bytes.

typedef Uint8 Byte;
typedef intptr_t PtrSize;

typedef float Float;
typedef double Float64;

#define cast(type) (type)
#define array_count(arr) (sizeof(arr) / (sizeof(*(arr))))
#define preprocessor_concat(a, b) a##b

#define internal static

//
// Detect compiler/platform.
//
#define COMPILER_WIN32 0
#define COMPILER_CLANG 0
#define COMPILER_GCC 0

#define ENVIRONMENT64 0
#define ENVIRONMENT32 0

#define OS_WIN32 0
#define OS_LINUX 0

#if defined(__clang__)
    #undef COMPILER_CLANG
    #define COMPILER_CLANG 1
#elif defined(_MSC_VER)
    #undef COMPILER_WIN32
    #define COMPILER_WIN32 1
#elif (defined(__GNUC__) || defined(__GNUG__)) // This has to be after __clang__, because Clang also defines this.
    #undef COMPILER_GCC
    #define COMPILER_GCC 1
#else
    #error "Could not detect compiler."
#endif

#if defined(__linux__)
    #undef OS_LINUX
    #define OS_LINUX 1
#elif defined(_WIN32)
    #undef OS_WIN32
    #define OS_WIN32 1
#else
    #error "Could not detect OS"
#endif

#if OS_LINUX
    #if (__x86_64__ || __ppc64__)
        #undef ENVIRONMENT64
        #define ENVIRONMENT64 1
    #else
        #undef ENVIRONMENT32
        #define ENVIRONMENT32 1
    #endif
#elif OS_WIN32
    #if defined(_WIN64)
        #undef ENVIRONMENT64
        #define ENVIRONMENT64 1
    #else
        #undef ENVIRONMENT32
        #define ENVIRONMENT32 1
    #endif
#endif

#define _SHARED_H
#endif