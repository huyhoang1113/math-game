// base.h - mini C header i use everywhere
// public domain'd
// https://tryh4rd.dev/

#pragma once
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

/* os stuff */
#if defined(_WIN32) || defined(_WIN64)
#    define BASE_OS_WINDOWS 1
#elif defined(__linux__) || defined(__gnu_linux__)
#    define BASE_OS_LINUX 1
#elif defined(__APPLE__) || defined(__MACH__)
#    define BASE_OS_APPLE 1
#elif defined(__FreeBSD__)
#    define BASE_OS_FREEBSD 1
#else
#    define BASE_OS_GENERIC 1
#endif

/* arch stuff */
#if defined(__amd64__) || defined(__amd64) || defined(__x86_64) || \
    defined(__x86_64__) || defined(_M_AMD64)
#    define BASE_ARCH_X86_64 1
#elif defined(__i386__) || defined(_M_IX86)
#    define BASE_ARCH_X86 1
#elif defined(__arm64__) || defined(__aarch64__) || defined(_M_ARM64)
#    define BASE_ARCH_ARM64 1
#elif defined(__arm__) || defined(_M_ARM)
#    define BASE_ARCH_ARM32 1
#elif defined(__riscv)
#    define BASE_ARCH_RISCV 1
#    if __riscv_xlen == 64
#        define BASE_ARCH_RISCV64 1
#    else
#        define BASE_ARCH_RISCV32 1
#    endif
#elif defined(__mips__) || defined(mips) || defined(__MIPS__)
#    define BASE_ARCH_MIPS 1
#elif defined(__powerpc__) || defined(__ppc__) || defined(_ARCH_PPC)
#    define BASE_ARCH_PPC 1
#endif

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;
typedef int8_t i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;
typedef float f32;
typedef double f64;
typedef size_t Size;

#define BASE_MAJOR_VERSION 0
#define BASE_MINOR_VERSION 0
#define BASE_PATCH_VERSION 1

typedef struct Bytes {
    u8* data;
    u64 length;
} Bytes;

#ifndef BASE_DEFAULT_ERROR_STRUCT
#    define BASE_DEFAULT_ERROR_STRUCT

typedef struct Error {
    const char* msg;
} Error;
#endif

#ifndef BASE_DEFAULT_RESULT_STRUCT
#    define BASE_DEFAULT_RESULT_STRUCT

typedef struct Result {
    bool ok;
    u64 code;
    Error err;
} Result;
#endif

#define ERROR_INIT(m) \
    (Error) {         \
        .msg = m      \
    }
#define RESULT_INIT(o, c, e)         \
    (Result) {                       \
        .ok = o, .code = c, .err = e \
    }

/* gcc/clang extension macros (fun!) */
#ifndef BASE_DISABLE_COMPILER_EXTENSION_MACROS
#    define likely(x)         __builtin_expect(!!(x), 1)
#    define unlikely(x)       __builtin_expect(!!(x), 0)
#    define cleanup(function) __attribute__((cleanup(function)))
#    define packed(name)      name __attribute__((packed))
#    define unreachable       __builtin_unreachable()
#    define panick            __builtin_trap()

#    ifndef BASE_NO_DEBUG
#        define assert(x)                                                    \
            ({                                                               \
                if (unlikely(!(x))) {                                        \
                    printf("assert: %s at %s:%d\n", #x, __FILE__, __LINE__); \
                    panick;                                                  \
                }                                                            \
            })
#    else
#        define assert(x) ((void)0)
#    endif
#endif

#ifndef BASE_NO_HANDY_MACROS
#    define max(x, y)           \
        ({                      \
            typeof(x) _x = (x); \
            typeof(y) _y = (y); \
            _x > _y ? _x : _y;  \
        })
#    define min(x, y)           \
        ({                      \
            typeof(x) _x = (x); \
            typeof(y) _y = (y); \
            _x < _y ? _x : _y;  \
        })
#    define base_abs(x)         \
        ({                      \
            typeof(x) _x = (x); \
            _x < 0 ? -_x : _x;  \
        })
#    define clamp(x, lo, hi)   (min(max((x), (lo)), (hi)))
#    define lerp(x, y, t)      ((x) + ((y) - (x)) * (t))
#    define between(x, lo, hi) ((x) >= (lo) && (x) <= (hi))
#    define array_len(array)   (sizeof(array) / sizeof((array)[0]))
#    define swap(x, y)            \
        ({                        \
            typeof(x) _tmp = (x); \
            x = (y);              \
            y = _tmp;             \
        })
#endif
