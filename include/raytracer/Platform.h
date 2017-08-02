/*
-----------------------------------------------------------------------------
The MIT License (MIT)

Copyright (c) 2016-2017 Jean Michel Catanho

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
-----------------------------------------------------------------------------
*/
#ifndef PLATFORM_H
#define PLATFORM_H

// CPU configuration.
#define RT_CPU_X86     0
#define RT_CPU_ARM     1
#define RT_CPU_MIPS    3
#define RT_CPU_UNKNOWN 4

// Architecture configuration.
#define RT_ARCHITECTURE_32 0
#define RT_ARCHITECTURE_64 1

// Endianness configuration.
#define RT_LITTLE_ENDIAN 0
#define RT_BIG_ENDIAN    1

// Operating system configuration.
#define RT_PLATFORM_WIN32   0
#define RT_PLATFORM_LINUX   1
#define RT_PLATFORM_ANDROID 2

// Compiler configuration.
#define RT_COMPILER_MSVC 0
#define RT_COMPILER_GNUC 1

// C++ version configuration.
#define RT_CPP_VER_UNDEFINED      0L
#define RT_CPP_VER_98        199711L
#define RT_CPP_VER_11        201103L
#define RT_CPP_VER_14        201402L

// Sets RT_CPU to the current CPU type.
#if (defined(_MSC_VER) && (defined(_M_IX86) || defined(_M_X64))) || (defined(__GNUC__) && (defined(__i386) || defined(__x86_64__)))
#define RT_CPU RT_CPU_X86
#elif defined(__arm__) || defined(_M_ARM) || defined(__arm64__) || defined(__aarch64__)
#define RT_CPU RT_CPU_ARM
#elif defined(__mips64) || defined(__mips64_)
#define RT_CPU RT_CPU_MIPS
#else
#define RT_CPU RT_CPU_UNKNOWN
#endif

// Sets RT_ARCH_TYPE to the current architecture type.
#if defined(__x86_64__) || defined(_M_X64)
#define RT_ARCHITECTURE_TYPE RT_ARCHITECTURE_64
#else
#define RT_ARCHITECTURE_TYPE RT_ARCHITECTURE_32
#endif

// Sets RT_ENDIANNES to little-endian configuration by default unless RT_CONFIG_BIG_ENDIAN is defined.
#ifdef RT_CONFIG_BIG_ENDIAN
#define RT_ENDIANNES RT_BIG_ENDIAN
#else
#define RT_ENDIANNES RT_LITTLE_ENDIAN
#endif

// Sets RT_PLATFORM to the current operational system.
#if defined(_WIN32)
#define RT_PLATFORM RT_PLATFORM_WIN32
#elif defined(__ANDROID__)
#define RT_PLATFORM RT_PLATFORM_ANDROID
#else
#define RT_PLATFORM RT_PLATFORM_LINUX
#endif

// Sets RT_COMPILER to the current compiler.
#if defined(_MSC_VER)
#define RT_COMPILER RT_COMPILER_MSVC
#define RT_COMPILER_VER _MSC_VER
#elif defined(__GNUC__) || defined(__GNUG__)
#define RT_COMPILER RT_COMPILER_GNUC
#define RT_COMPILER_VER (__GNUC__ * 100) + (__GNUC_MINOR__ * 10) + __GNUC_PATCHLEVEL__
#else
#pragma error "Unknown compiler!"
#endif

// Sets RT_CPP_VER to the current C++ version.
#if defined(__cplusplus)
#if __cplusplus >= RT_CPP_VER_14
#define RT_CPP_VER RT_CPP_VER14
#elif __cplusplus >= RT_CPP_VER_11
#define RT_CPP_VER RT_CPP_VER_11
#elif __cplusplus >= RT_CPP_VER_98
#define RT_CPP_VER RT_CPP_VER_98
#else
#define RT_CPP_VER RT_CPP_VER_UNDEFINED
#endif
#endif

// ----------------------------------------------------------------------------------------------------
// Windows settings.
#if RT_PLATFORM == RT_PLATFORM_WIN32
// windows.h is not included here because it conflicts with many STL libraries.
#if defined(_DEBUG) || defined(DEBUG)
#define RT_DEBUG 1
#else
#define RT_DEBUG 0
#endif
#endif

// Linux/Android settings.
#if RT_PLATFORM == RT_PLATFORM_LINUX || RT_PLATFORM == RT_PLATFORM_ANDROID
#if defined(DEBUG)
#define RT_DEBUG 1
#else
#define RT_DEBUG 0
#endif
#endif

#endif