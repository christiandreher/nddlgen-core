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

#include <string>
#include <sdf/sdf.hh>

/**
 * Base components for the nddl generator.
 *
 * @author Christian Dreher
 * @version v1.0.0
 */
namespace base
{

	/**
	 * An object of this class controls the workflow to successfully generate domain
	 * files (nddl) out of an sdf file.
	 *
	 * @author Christian Dreher
	 * @version v1.0.0
	 */
	class Controller
	{

		private:

			/**
			 * Stringstream to override the default cerr buffer.
			 */
			std::stringstream cerrOvRdBuf;

			/**
			 * Default cerr buffer.
			 */
			std::streambuf* cerrStdRdBuf;


			/**
			 * Pointer to a string to write error messages to. Must be supplied through the constructor.
			 */
			std::string* errorText;

			/**
			 * Identifier for the sdf file to generate nddl files from. Must contain file name and extension
			 * (.sdf) and can be a relative or absolute path.
			 */
			std::string fileIdentifier;

			/**
			 * Root element of the sdf file.
			 */
			sdf::ElementPtr sdfRoot;


			/**
			 * Flag to control the workflow and check if a file identifier has been set.
			 */
			bool isFileIdentifierSet;

			/**
			 * Flag to control the workflow and check if the file has been checked.
			 */
			bool isFileChecked;

			/**
			 * Flag to control the workflow and check if the SDF has been parsed.
			 */
			bool isSdfParsed;

			/**
			 * Flag to control the workflow and check if the nddl files has been generated.
			 */
			bool isNddlGenerated;


			/**
			 * Checks if a file is checkable. This means, that a file identifier has already
			 * been set.
			 *
			 * @return true, if the file is checkable, false if not
			 */
			bool isCheckable();

			/**
			 * Checks if a file is parsable. This means, that a file identifier has already
			 * been set, and the file has been checked.
			 *
			 * @return true, if the file is parsable, false if not
			 */
			bool isParsable();

			/**
			 * Checks if nddl files are generatable. This means, that a file identifier has already
			 * been set, the file has been checked and parsed.
			 *
			 * @return true, if the nddl files are generatable, false if not
			 */
			bool isGeneratable();


			/**
			 * Helper to disable the cerr output to the console.
			 */
			void disableCerr();

			/**
			 * Helper to enable the standard cerr output to the console.
			 */
			void enableCerr();

			/**
			 * Helper to get the cerr output which has been buffered while the
			 * standard cerr output was disabled.
			 *
			 * @return Buffered cerr output
			 */
			std::string getBufferedCerrOutput();

		public:

			/**
			 * Error message when a file identifier has already been set.
			 */
			static const std::string ERR_FILE_ID_ALREADY_SET;

			/**
			 * Error message when a file has already been checked.
			 */
			static const std::string ERR_FILE_ALREADY_CHECKED;

			/**
			 * Error message when a file has already been parsed.
			 */
			static const std::string ERR_FILE_ALREADY_PARSED;

			/**
			 * Error message when nddl files have already been generated.
			 */
			static const std::string ERR_NDDL_ALREADY_GENERATED;

			/**
			 * Error message when a called function needs a set file identifier,
			 * but none was set.
			 */
			static const std::string ERR_SET_FILE_ID_FIRST;

			/**
			 * Error message when a called function needs a file check, but
			 * none was executed.
			 */
			static const std::string ERR_CHECK_FILE_FIRST;

			/**
			 * Error message when a called function needs the file to have been
			 * parsed, but it was not.
			 */
			static const std::string ERR_PARSE_FILE_FIRST;

			/**
			 * Error message when a given file identifier is not a .sdf file.
			 */
			static const std::string ERR_FILE_MUST_BE_SDF;

			/**
			 * Error message when given file identifier points to a non existent file.
			 */
			static const std::string ERR_FILE_NOT_EXISTING;

			/**
			 * Error message when the default .sdf file could not have been initialized
			 * by the installed sdf_format.xml.
			 */
			static const std::string ERR_INITIALIZING_SDF;

			/**
			 * Error message when the .sdf file could not have been read.
			 */
			static const std::string ERR_READING_SDF_FILE;


			/**
			 * Constructor to initialize a Controller object with given errorText pointer.
			 *
			 * @param errorText Pointer to the string where error texts should be written to.
			 */
			Controller(std::string* errorText);

			/**
			 * Constructor to initialize a Controller object with given fileIdentifier and
			 * errorText pointer.
			 *
			 * @param fileIdentifier Identifier to locate file. Can be a relative or absolute
			 * 		and must contain a file name and the .sdf file extension.
			 * @param errorText Pointer to the string where error texts should be written to.
			 */
			Controller(std::string fileIdentifier, std::string* errorText);

			/**
			 * Destructor to destroy the object and free resources.
			 */
			virtual ~Controller();


			/**
			 * Sets the file identifier. A file identifier locates the .sdf file. It must
			 * contain the file name and the .sdf file extension. Can be a relative or
			 * absolute path.
			 *
			 * @param fileIdentifier Identifier to locate file. Can be a relative or absolute
			 * 		and must contain a file name and the .sdf file extension.
			 * @return false, if errors where produced, true if not.
			 */
			bool setFileIdentifier(std::string fileIdentifier);

			/**
			 * Syntax yet to be defined.
			 *
			 * @todo
			 * @return false, if errors where produced, true if not.
			 */
			std::string getOutputFileName();

			/**
			 * Checks if the given file is a .sdf file, if it exists, if it is readable, if it
			 * complies with the SDF standard.
			 *
			 * @return false, if errors where produced, true if not.
			 */
			bool checkFile();

			/**
			 * Parses the SDF into a data structure where possible collisions and
			 * blocks can be computed.
			 *
			 * @return false, if errors where produced, true if not.
			 */
			bool parseSdf();

			/**
			 * Uses the data structures
			 *
			 * @return false, if errors where produced, true if not.
			 */
			bool generateNddl();

	};

}

#endif
