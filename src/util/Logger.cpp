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
#include "Logger.h"

namespace Logger {
	namespace {
		std::stringstream m_Log;

		std::chrono::time_point<std::chrono::system_clock> m_StartTime;

		std::chrono::time_point<std::chrono::system_clock> CurrentTime() {
			return std::chrono::system_clock::now();
		}

		std::string DateString() {
			std::time_t time = std::chrono::system_clock::to_time_t(CurrentTime());
			char *dateString = std::ctime(&time);
			dateString[(strlen(dateString) - 1)] = '\0';

			return dateString;
		}
	}

	void StartLog() {
		m_StartTime = std::chrono::system_clock::now();
	}

	void Log(LogType type, std::string message, std::string component) {
		switch (type) {
		case LT_DEBUG:
			DebugLog(message, component);
			break;

		case LT_ERROR:
			ErrorLog(message, component);
			break;

		case LT_INFO:
			InfoLog(message, component);
			break;

		default:
			ErrorLog("", "Logger.Log()");
			break;
		}
	}

	void DebugLog(std::string message, std::string component) {
		m_Log << "[" << DateString() << "] " << "[DEBUG]" << " - " << component << " - " << message << std::endl;
	}

	void ErrorLog(std::string message, std::string component) {

		m_Log << "[" << DateString() << "] " << "[ERROR]" << " - " << component << " - " << message << std::endl;
	}

	void InfoLog(std::string message, std::string component) {
		m_Log << "[" << DateString() << "] " << "[INFO]" << " - " << component << " - " << message << std::endl;
	}

	void SaveLog(std::string path) {
		std::chrono::duration<double> elapsedTime = CurrentTime() - m_StartTime;
		m_Log << std::endl << "Approximated runtime: " << elapsedTime.count() << std::endl;

		std::stringstream ss;
		ss << path << "/log.txt";
		std::string result_path = ss.str();

		std::ofstream output_stream;
		output_stream.open(result_path, std::ofstream::out);
		output_stream << m_Log.str();
		output_stream.close();
	}
}