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

#ifndef NDDLGEN_CONTROLLER_ISDPARSER_H_
#define NDDLGEN_CONTROLLER_ISDPARSER_H_

#include <boost/shared_ptr.hpp>
#include <tinyxml.h>

#include <nddlgen/exceptions/ReadingIsdFileException.hpp>
#include <nddlgen/exceptions/IsdInputFileNotSetException.hpp>
#include <nddlgen/exceptions/FileMustBeIsdException.hpp>
#include <nddlgen/exceptions/FileDoesNotExistException.hpp>
#include <nddlgen/utilities/WorkflowControllerConfig.h>
#include <nddlgen/utilities/Types.hpp>

namespace nddlgen
{
	namespace controllers
	{
		class IsdParser;
		typedef boost::shared_ptr<nddlgen::controllers::IsdParser> IsdParserPtr;
	}
}

/**
 * Parser to handle a ISD file.
 *
 * @author Christian Dreher
 */
class nddlgen::controllers::IsdParser
{

	private:

		/**
		 * Workflow controller configuration.
		 */
		nddlgen::utilities::WorkflowControllerConfigPtr _config;

		/**
		 * Helper to ensure that all assertions are met.
		 */
		void checkAssertions();

	public:

		/**
		 * Instantiates a new ISD parser with required workflow controller configuration.
		 *
		 * @param config Workflow controller configuration
		 */
		IsdParser(nddlgen::utilities::WorkflowControllerConfigPtr config);

		/**
		 * Destructor to free memory.
		 */
		virtual ~IsdParser();

		/**
		 * Parses the ISD file as specified in workflow controller configuration object.
		 *
		 * @return ISD document root
		 */
		nddlgen::types::IsdRoot parseIsd();

};

#endif
