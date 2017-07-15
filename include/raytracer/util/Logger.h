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

/**
 * @addtogroup Utilities
 * @{
 */

/**
 * Handles the creation of log messages.
 * @remarks TODO
 */
namespace Logger {
	/**
	 * Describes the type of the log message.
	 */
	enum LogType {
		LT_DEBUG, /*!< Debug message. */
		LT_ERROR, /*!< Error message. */
		LT_INFO   /*!< Informative message. */
	};
	
	/**
	 * Describes how detailed the log message is.
	 */
	enum LogDetail {
		LD_LITTLE, /*!< Little detailed message. */
		LD_NORMAL, /*!< Normal detailed message. */
		LD_HIGH    /*!< High detailes message. */
	};
	
	/**
	 * Describes how important the log message is.
	 */
	enum LogRelevance {
		LR_TRIVIAL,  /*!< Trivial message. */
		LR_NORMAL,   /*!< Normal message. */
		LR_IMPORTANT /*!< Important message */
	};
	
	/**
	 * Initializes the logging system.
	 */
	void StartLog();

	/**
	 * Creates a log message of the specified type.
	 * @param type    Type of the log message.
	 * @param message Log message.
	 * @param component Name of the function where the log message is being created.
	 */
	void Log(LogType type, std::string message, std::string component);

	/**
	 * Creates a debug log message.
	 * @param message   Log message.
	 * @param component Name of the function where the log message is being created.
	 */
	void DebugLog(std::string message, std::string component);

	/**
	 * Creates an error log message.
	 * @param message   Log message.
	 * @param component Name of the function where the log message is being created.
	 */
	void ErrorLog(std::string message, std::string component);

	/**
	 * Creates an information log message.
	 * @param message   Log message.
	 * @param component Name of the function where the log message is being created.
	 */
	void InfoLog(std::string message, std::string component);

	/**
	 * Saves all the log messages in a file.
	 * @remarks Since the whole API is very efficiency-dependent, the log messages are
	 * only written to a file when the program finishs it's execution. File reading and
	 * writing has a very expensive and unnecessary cost to deal with during bottlenecks
	 * of exectuion.
	 */
	void SaveLog();
}

/**
 * @}
 */

#endif