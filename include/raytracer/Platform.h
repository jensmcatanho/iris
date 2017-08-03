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

/**
 * CPU configuration.
 */
#define IRIS_CPU_X86     0
#define IRIS_CPU_ARM     1
#define IRIS_CPU_MIPS    3
#define IRIS_CPU_UNKNOWN 4

/**
 * Architecture configuration.
 */
#define IRIS_ARCHITECTURE_32 0
#define IRIS_ARCHITECTURE_64 1

/**
* Operating system configuration.
*/
#define IRIS_PLATFORM_WIN32   0
#define IRIS_PLATFORM_LINUX   1
#define IRIS_PLATFORM_ANDROID 2

/**
 * Compiler configuration.
 */
#define IRIS_COMPILER_MSVC 0
#define IRIS_COMPILER_GNUC 1

/**
 * C++ version configuration.
 */
#define IRIS_CPP_VER_UNDEFINED      0L
#define IRIS_CPP_VER_98        199711L
#define IRIS_CPP_VER_11        201103L
#define IRIS_CPP_VER_14        201402L

/**
 * Sets IRIS_CPU to the current CPU type.
 */
#if (defined(_MSC_VER) && (defined(_M_IX86) || defined(_M_X64))) || (defined(__GNUC__) && (defined(__i386) || defined(__x86_64__)))
	#define IRIS_CPU IRIS_CPU_X86
#elif defined(__arm__) || defined(_M_ARM) || defined(__arm64__) || defined(__aarch64__)
	#define IRIS_CPU IRIS_CPU_ARM
#elif defined(__mips64) || defined(__mips64_)
	#define IRIS_CPU IRIS_CPU_MIPS
#else
	#define IRIS_CPU IRIS_CPU_UNKNOWN
#endif

/**
 * Sets IRIS_ARCHTECTURE_TYPE to the current architecture type.
 */
#if defined(__x86_64__) || defined(_M_X64)
	#define IRIS_ARCHITECTURE_TYPE IRIS_ARCHITECTURE_64
#else
	#define IRIS_ARCHITECTURE_TYPE IRIS_ARCHITECTURE_32
#endif

/**
 * Sets IRIS_PLATFORM to the current operating system.
 */
#if defined(_WIN32)
	#define IRIS_PLATFORM IRIS_PLATFORM_WIN32
#elif defined(__ANDROID__)
	#define IRIS_PLATFORM IRIS_PLATFORM_ANDROID
#else
	#define IRIS_PLATFORM IRIS_PLATFORM_LINUX
#endif

/**
 * Sets IRIS_COMPILER to the current compiler.
 */
#if defined(_MSC_VER)
	#define IRIS_COMPILER IRIS_COMPILER_MSVC
	#define IRIS_COMPILER_VER _MSC_VER
#elif defined(__GNUC__) || defined(__GNUG__)
	#define IRIS_COMPILER IRIS_COMPILER_GNUC
	#define IRIS_COMPILER_VER (__GNUC__ * 100) + (__GNUC_MINOR__ * 10) + __GNUC_PATCHLEVEL__
#else
	#pragma error "Unknown compiler!"
#endif

/**
 * Sets IRIS_CPP_VER to the current C++ version.
 */
#if defined(__cplusplus)
#if __cplusplus >= IRIS_CPP_VER_14
	#define IRIS_CPP_VER IRIS_CPP_VER14
#elif __cplusplus >= IRIS_CPP_VER_11
	#define IRIS_CPP_VER IRIS_CPP_VER_11
#elif __cplusplus >= IRIS_CPP_VER_98
	#define IRIS_CPP_VER IRIS_CPP_VER_98
#else
	#define IRIS_CPP_VER IRIS_CPP_VER_UNDEFINED
#endif
#endif

/**
 * Operating system settings.
 */

/**
 * Windows settings.
 */
#if IRIS_PLATFORM == IRIS_PLATFORM_WIN32
	#if defined(_DEBUG) || defined(DEBUG)
		#define IRIS_DEBUG 1
	#else
		#define IRIS_DEBUG 0
	#endif
#endif

/**
 * Linux/Android settings.
 */
#if IRIS_PLATFORM == IRIS_PLATFORM_LINUX || IRIS_PLATFORM == IRIS_PLATFORM_ANDROID
	#if defined(DEBUG)
		#define IRIS_DEBUG 1
	#else
		#define IRIS_DEBUG 0
	#endif
#endif

#endif