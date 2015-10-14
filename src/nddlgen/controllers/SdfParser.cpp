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

#include <nddlgen/controllers/SdfParser.h>

nddlgen::controllers::SdfParser::SdfParser(nddlgen::utilities::WorkflowControllerConfig* config)
{
	this->_config = config;
}

nddlgen::controllers::SdfParser::~SdfParser()
{

}

nddlgen::types::SdfRoot nddlgen::controllers::SdfParser::parseSdf()
{
	// Assert that all preconditions are met. Throw exception if not
	this->checkAssertions();

	// Local variable initializations
	sdf::SDFPtr sdf(new sdf::SDF);

	// Disable standard cerr output, since the output of the SDF library can't be suppressed otherwise
	nddlgen::utilities::StdCerrHandler::disableCerr();

	// Init .sdf based on installed sdf_format.xml file
	if (!sdf::init(sdf))
	{
		// Re-enable standard cerr
		nddlgen::utilities::StdCerrHandler::enableCerr();
		throw nddlgen::exceptions::InitializingSdfException(nddlgen::utilities::StdCerrHandler::getBufferedCerrOutput());
	}

	// Try to read the file and parse SDF
	if (!sdf::readFile(this->_config->getSdfInputFile(), sdf))
	{
		// Re-enable cerr
		nddlgen::utilities::StdCerrHandler::enableCerr();
		throw nddlgen::exceptions::ReadingSdfFileException(nddlgen::utilities::StdCerrHandler::getBufferedCerrOutput());
	}

	// Re-enable cerr
	nddlgen::utilities::StdCerrHandler::enableCerr();

	// Return SdfRoot
	return sdf->root;
}


void nddlgen::controllers::SdfParser::checkAssertions()
{
	// Assert that an SDF input file has been set
	if (this->_config->getSdfInputFile() == "")
	{
		throw nddlgen::exceptions::SdfInputFileNotSetException();
	}

	// Assert that the SDF input file has a .sdf extention
	if (this->_config->getSdfInputFileExt() != ".sdf")
	{
		throw nddlgen::exceptions::FileMustBeSdfException();
	}

	// Assert that the SDF input file exists
	if (!boost::filesystem::exists(this->_config->getSdfInputFile()))
	{
		throw nddlgen::exceptions::FileDoesNotExistException(this->_config->getSdfInputFile());
	}
}
