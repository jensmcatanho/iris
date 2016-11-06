/*
-----------------------------------------------------------------------------
The MIT License (MIT)

Copyright (c) 2016 Jean Michel Catanho

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
#ifndef LOGGER_H
#define LOGGER_H

#include "Prerequisites.h"

// enum LogDetail { LD_LOW, LD_NORMAL, LD_HIGH };  // Check the need for this in the future.
// enum LogRelevance { LR_TRIVIAL, LR_NORMAL, LR_IMPORTANT };  // Different highlights.
enum LogType { LT_DEBUG, LT_ERROR, LT_INFO };  // Different prefixes.

namespace Logger {
	void StartLog();

	void Log(LogType, std::string, std::string);

	void DebugLog(std::string message, std::string component);

	void ErrorLog(std::string message, std::string component);

	void InfoLog(std::string message, std::string component);

	void SaveLog();
}

#endif