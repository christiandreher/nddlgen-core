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

#ifndef NDDLGEN_CONTROLLERS_SDFPARSER_H_
#define NDDLGEN_CONTROLLERS_SDFPARSER_H_

#include <boost/shared_ptr.hpp>
#include <sdf/sdf.hh>

#include <nddlgen/exceptions/InitializingSdfException.hpp>
#include <nddlgen/exceptions/ReadingSdfFileException.hpp>
#include <nddlgen/exceptions/SdfInputFileNotSetException.hpp>
#include <nddlgen/exceptions/FileMustBeSdfException.hpp>
#include <nddlgen/exceptions/FileDoesNotExistException.hpp>
#include <nddlgen/utilities/StdCerrHandler.h>
#include <nddlgen/utilities/Types.hpp>
#include <nddlgen/utilities/WorkflowControllerConfig.h>

namespace nddlgen
{
	namespace controllers
	{
		class SdfParser;
		typedef boost::shared_ptr<nddlgen::controllers::SdfParser> SdfParserPtr;
	}
}

/**
 * Parser to handle a SDF file.
 *
 * @author Christian Dreher
 */
class nddlgen::controllers::SdfParser
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
		 * Instantiates a new SDF parser with required workflow controller configuration.
		 *
		 * @param config Workflow controller configuration
		 */
		SdfParser(nddlgen::utilities::WorkflowControllerConfigPtr config);

		/**
		 * Destructor to free memory.
		 */
		virtual ~SdfParser();

		/**
		 * Parses the SDF file as specified in workflow controller configuration object.
		 *
		 * @return SDF document root
		 */
		nddlgen::types::SdfRoot parseSdf();

};

#endif
