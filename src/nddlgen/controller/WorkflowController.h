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

#ifndef NDDLGEN_CONTROLLER_WORKFLOWCONTROLLER_H_
#define NDDLGEN_CONTROLLER_WORKFLOWCONTROLLER_H_

#include <cstdlib>
#include <string>
#include <sys/stat.h>

#include <sdf/sdf.hh>

#include <nddlgen/controller/DomainDescriptionFactory.h>
#include <nddlgen/controller/IsdParser.h>
#include <nddlgen/controller/NddlGenerationController.h>
#include <nddlgen/utilities/WorkflowControllerConfig.h>
#include <nddlgen/utilities/Exceptions.hpp>
#include <nddlgen/utilities/Types.hpp>

namespace nddlgen { namespace controller
{

	/**
	 * An object of this class controls the workflow to successfully generate NDDL model
	 * files out of a Gazebo SDF file, and/or NDDL initial state files out of SDF and ISD files.
	 *
	 * @author Christian Dreher
	 */
	class WorkflowController
	{

		private:

			/**
			 * Workflow control flag to keep track if the SDF input file was parsed.
			 */
			bool _isSdfInputFileParsed;

			/**
			 * Workflow control flag to keep track if the ISD input file was parsed.
			 */
			bool _isIsdInputFileParsed;

			/**
			 * Workflow control flag to keep track if the domain description was built.
			 */
			bool _isDomainDescriptionBuilt;

			/**
			 * Workflow control flag to keep track if the NDDL model file was written.
			 */
			bool _isNddlModelFileWritten;

			/**
			 * Workflow control flag to keep track if the NDDL initial state file was written.
			 */
			bool _isNddlInitialStateFileWritten;


			/**
			 * Object holding controller meta data to make it accessible for other classes.
			 */
			nddlgen::utilities::WorkflowControllerConfig* _config;

			/**
			 * Root of the parsed SDF data structure.
			 */
			nddlgen::types::SdfRoot _sdfRoot;

			/**
			 * Root of the parsed ISD data structure.
			 */
			nddlgen::types::IsdRoot _isdRoot;

			/**
			 * Domain description model.
			 */
			nddlgen::models::DomainDescriptionModel* _domainDescription;


			/**
			 * Stringstream to override the default cerr buffer.
			 */
			std::stringstream _cerrOvRdBuf;

			/**
			 * Default cerr buffer.
			 */
			std::streambuf* _cerrStdRdBuf;


			/**
			 * Helper function to assure that all preconditions are met to execute the
			 * parseSdfInputFile function.
			 */
			void assertParseSdfInputFilePreconditions();

			/**
			 * Helper function to assure that all preconditions are met to execute the
			 * parseIsdInputFile function.
			 */
			void assertParseIsdInputFilePreconditions();

			/**
			 * Helper function to assure that all preconditions are met to execute the
			 * buildDomainDescription function.
			 */
			void assertBuildDomainDescriptionPreconditions();

			/**
			 * Helper function to assure that all preconditions are met to execute the
			 * writeNddlModelFile function.
			 *
			 * @param forceOverwrite If set to true, no exception will be thrown if a file with the
			 * 		same name already exists
			 */
			void assertWriteNddlModelFilePreconditions(bool forceOverwrite);

			/**
			 * Helper function to assure that all preconditions are met to execute the
			 * writeNddlInitialStateFile function.
			 *
			 * @param forceOverwrite If set to true, no exception will be thrown if a file with the
			 * 		same name already exists
			 */
			void assertWriteNddlInitialStateFilePreconditions(bool forceOverwrite);


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
			WorkflowController(nddlgen::utilities::WorkflowControllerConfig* config);

			/**
			 * Destructor to destroy the object and free resources.
			 */
			virtual ~WorkflowController();

			/**
			 * Parses the SDF into a data structure where possible collisions and
			 * blocks can be computed.
			 */
			void parseSdfInputFile();

			/**
			 * Parses the ISD into a data structure where possible collisions and
			 * blocks can be computed.
			 */
			void parseIsdInputFile();

			/**
			 * Uses parsed information from either the SDF or the SDF and ISD to
			 * build a DomainDescription model which can be used to generate NDDL files.
			 */
			void buildDomainDescription();

			/**
			 * Uses the DomainDescription model to generate the NDDL model file.
			 * This function calls writeNddlModelFile(forceOverwrite) with forceOverwrite
			 * set to false.
			 */
			void writeNddlModelFile();

			/**
			 * Uses the DomainDescription model to generate the NDDL model file.
			 *
			 * @param forceOverwrite If set to true, all existing files will silently be overwritten
			 */
			void writeNddlModelFile(bool forceOverwrite);

			/**
			 * Uses the DomainDescription model to generate the NDDL initial state file.
			 * This function calls writeNddlInitialStateFile(forceOverwrite) with forceOverwrite
			 * set to false.
			 */
			void writeNddlInitialStateFile();

			/**
			 * Uses the DomainDescription model to generate the NDDL initial state file.
			 *
			 * @param forceOverwrite If set to true, all existing files will silently be overwritten
			 */
			void writeNddlInitialStateFile(bool forceOverwrite);

	};

}}

#endif
