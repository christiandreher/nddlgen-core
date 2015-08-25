/**
 * Copyright 2015 Christian Dreher (dreher@charlydelta.org)
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef NDDLGEN_UTILITIES_STDCERRHANDLER_H_
#define NDDLGEN_UTILITIES_STDCERRHANDLER_H_

#include <string>
#include <sys/stat.h>
#include <iostream>
#include <sstream>

namespace nddlgen { namespace utilities { class StdCerrHandler; }}

class nddlgen::utilities::StdCerrHandler
{

	private:

		StdCerrHandler();
		virtual ~StdCerrHandler();

		/**
		 * Stringstream to override the default cerr buffer.
		 */
		static std::stringstream _cerrOvRdBuf;

		/**
		 * Default cerr buffer.
		 */
		static std::streambuf* _cerrStdRdBuf;

	public:

		static void disableCerr();

		static void enableCerr();

		static std::string getBufferedCerrOutput();

};

#endif
