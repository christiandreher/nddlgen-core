/**
 * Copyright 2015 Christian Dreher (christian.dreher@student.kit.edu)
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

#ifndef CONTROLLER_H_
#define CONTROLLER_H_

namespace base
{

	class Controller
	{
		private:
			std::stringstream cerrOvRdBuf;
			std::streambuf* cerrStdRdBuf;

			std::string* errorText;
			std::string fileIdentifier;

			bool isFileIdentifierSet;
			bool isFileChecked;
			bool isFileParsed;
			bool isNddlGenerated;

			void disableCerr();
			void enableCerr();
			std::string getBufferedCerrOutput();
		public:
			static const std::string ERR_FILE_ID_ALREADY_SET;
			static const std::string ERR_FILE_ALREADY_CHECKED;
			static const std::string ERR_FILE_ALREADY_PARSED;
			static const std::string ERR_NDDL_ALREADY_GENERATED;
			static const std::string ERR_SET_FILE_ID_FIRST;
			static const std::string ERR_CHECK_FILE_FIRST;
			static const std::string ERR_PARSE_FILE_FIRST;
			static const std::string ERR_FILE_MUST_BE_SDF;
			static const std::string ERR_FILE_NOT_EXISTING;

			Controller(std::string* errorText);
			virtual ~Controller();

			bool setFileIdentifier(std::string fileIdentifier);
			std::string getOutputFileName();
			bool checkFile();
			bool parseFile();
			bool generateNddl();
	};

}

#endif
