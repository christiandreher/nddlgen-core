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
#include <sys/stat.h>

#include <sdf/sdf.hh>

#include <nddlgen/core/SdfParser.h>
#include <nddlgen/core/NddlGenerator.h>
#include <nddlgen/models/Arm.h>
#include <nddlgen/utilities/ControllerConfig.h>
#include <nddlgen/utilities/Exceptions.hpp>

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
			 * Root element of the sdf file.
			 */
			sdf::ElementPtr _sdfRoot;


			bool _isSdfChecked;

			bool _isSdfParsed;

			bool _isNddlModelGenerated;

			bool _isIsdChecked;

			bool _isIsdParsed;

			bool _isNddlInitialStateGenerated;

			/**
			 * Arm model to generate nddl files from.
			 */
			nddlgen::models::Arm* _armModel;

			/**
			 * Object holding controller meta data to make it accessible for other classes
			 */
			nddlgen::utilities::ControllerConfig* _config;


			/**
			 * Checks if a file is parsable. This means, that a file identifier has already
			 * been set, and the file has been checked.
			 */
			void isSdfParsable();

			/**
			 * Checks if nddl files are generatable. This means, that a file identifier has already
			 * been set, the file has been checked and parsed.
			 */
			void isNddlModelGeneratable();

			void isIsdParsable();

			void isNddlInitialStateGeneratable();

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
			 * Constructor to initialize a Controller object with given config object.
			 *
			 * @param config Controller configuration
			 */
			Controller(nddlgen::utilities::ControllerConfig* config);

			/**
			 * Destructor to destroy the object and free resources.
			 */
			virtual ~Controller();


			/**
			 * Checks if the given file is a .sdf file, if it exists, if it is readable, if it
			 * complies with the SDF standard.
			 */
			void checkSdfInput();

			/**
			 * Parses the SDF into a data structure where possible collisions and
			 * blocks can be computed.
			 */
			void parseSdf();

			/**
			 * Uses the data structures to generate NDDL model and initial state files.
			 */
			void generateNddlModel();

			void generateNddlModel(bool forceOverwrite);


			void checkIsdInput();

			void parseIsd();

			void generateNddlInitialState();

			void generateNddlInitialState(bool forceOverwrite);

	};

}

#endif
