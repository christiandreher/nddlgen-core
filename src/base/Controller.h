/*
 * Controller.h
 *
 *  Created on: Jun 24, 2015
 *      Author: chris
 */

#ifndef CONTROLLER_H_
#define CONTROLLER_H_

namespace base
{

	class Controller
	{
		private:
			std::string* errorText;
			std::string fileIdentifier;
			bool isFileIdentifierSet;
			bool isFileChecked;
			bool isFileParsed;
			bool isNddlGenerated;
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
