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

#ifndef NDDLGEN_CONTROLLER_H_
#define NDDLGEN_CONTROLLER_H_

#include <string>

#include <sdf/sdf.hh>

#include <nddlgen/core/SdfParser.h>
#include <nddlgen/core/NddlGenerator.h>
#include <nddlgen/exceptions/CheckFileFirstException.hpp>
#include <nddlgen/exceptions/FileAlreadyCheckedException.hpp>
#include <nddlgen/exceptions/FileAlreadyParsedException.hpp>
#include <nddlgen/exceptions/FileDoesNotExistException.hpp>
#include <nddlgen/exceptions/FileIdAlreadySetException.hpp>
#include <nddlgen/exceptions/FileMustBeSdfException.hpp>
#include <nddlgen/exceptions/GeneratingInitialStateException.hpp>
#include <nddlgen/exceptions/GeneratingModelsException.hpp>
#include <nddlgen/exceptions/InitializingSdfException.hpp>
#include <nddlgen/exceptions/NddlAlreadyGeneratedException.hpp>
#include <nddlgen/exceptions/ParseDataStructureException.hpp>
#include <nddlgen/exceptions/ParseFileFirstException.hpp>
#include <nddlgen/exceptions/ReadingSdfFileException.hpp>
#include <nddlgen/exceptions/SetFileIdFirstException.hpp>
#include <nddlgen/models/Arm.h>
#include <nddlgen/utilities/ControllerMeta.hpp>

/**
 * Base components for the nddl generator.
 *
 * @author Christian Dreher
 */
namespace nddlgen
{

	/**
	 * An object of this class controls the workflow to successfully generate domain
	 * files (nddl) out of an sdf file.
	 *
	 * @author Christian Dreher
	 */
	class Controller
	{

		private:

			/**
			 * Stringstream to override the default cerr buffer.
			 */
			std::stringstream _cerrOvRdBuf;

			/**
			 * Default cerr buffer.
			 */
			std::streambuf* _cerrStdRdBuf;


			/**
			 * Path to output files.
			 */
			std::string _outputFilesPath;

			/**
			 * Identifier for the sdf file to generate nddl files from. Must contain file name and extension
			 * (.sdf) and can be a relative or absolute path.
			 */
			std::string _fileIdentifier;

			/**
			 * Root element of the sdf file.
			 */
			sdf::ElementPtr _sdfRoot;


			/**
			 * Flag to control the workflow and check if a file identifier has been set.
			 */
			bool _isFileIdentifierSet;

			/**
			 * Flag to control the workflow and check if the file has been checked.
			 */
			bool _isFileChecked;

			/**
			 * Flag to control the workflow and check if the SDF has been parsed.
			 */
			bool _isSdfParsed;

			/**
			 * Flag to control the workflow and check if the .nddl files has been generated.
			 */
			bool _isNddlGenerated;

			/**
			 * Arm model to generate nddl files from.
			 */
			nddlgen::models::Arm* _armModel;

			/**
			 * Object holding controller meta data to make it accessible for other classes
			 */
			nddlgen::utilities::ControllerMeta* _controllerMeta;

			/**
			 * Checks if a file is checkable. This means, that a file identifier has already
			 * been set.
			 */
			void isCheckable();

			/**
			 * Checks if a file is parsable. This means, that a file identifier has already
			 * been set, and the file has been checked.
			 */
			void isParsable();

			/**
			 * Checks if nddl files are generatable. This means, that a file identifier has already
			 * been set, the file has been checked and parsed.
			 */
			void isGeneratable();


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
			 * Constructor to initialize a Controller object.
			 */
			Controller();

			/**
			 * Constructor to initialize a Controller object with given fileIdentifier.
			 *
			 * @param fileIdentifier Identifier to locate file. Can be a relative or absolute
			 * 		and must contain a file name and the .sdf file extension.
			 */
			Controller(std::string fileIdentifier);

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
			 */
			void setFileIdentifier(std::string fileIdentifier);


			/**
			 * Checks if the given file is a .sdf file, if it exists, if it is readable, if it
			 * complies with the SDF standard.
			 */
			void checkFile();

			/**
			 * Parses the SDF into a data structure where possible collisions and
			 * blocks can be computed.
			 */
			void parseSdf();

			/**
			 * Uses the data structures to generate NDDL model and initial state files.
			 */
			void generateNddl();


			/**
			 * Sets adapter name and version to indicate it in the generated files.
			 *
			 * @param adapter name and version of the adapter. E.g "nddlgen-cli v0.0.0".
			 */
			void setAdapter(std::string adapter);

			/**
			 * Sets output files path.
			 *
			 * @param outputFilesPath Path to output files.
			 */
			void setOutputFilesPath(std::string outputFilesPath);


			/**
			 * Returns the input file path.
			 *
			 * @return Path of the input file.
			 */
			std::string getInputFilePath();

			/**
			 * Returns the input file name.
			 *
			 * @return Input file name.
			 */
			std::string getInputFileName();

			/**
			 * Returns the path where the output files are saved.
			 *
			 * @return Path of the output files.
			 */
			std::string getOutputFilesPath();

			/**
			 * Returns the file name of the domain models output file.
			 *
			 * @return Name of the domain models output file.
			 */
			std::string getModelsOutputFileName();

			/**
			 * Returns the file name of the domain initial state output file.
			 *
			 * @return Name of the domain initial state output file.
			 */
			std::string getInitialStateOutputFileName();

	};

}

#endif
