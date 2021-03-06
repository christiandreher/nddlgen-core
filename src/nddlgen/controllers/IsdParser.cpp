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

#include <nddlgen/controllers/IsdParser.h>

nddlgen::controllers::IsdParser::IsdParser(nddlgen::utilities::WorkflowControllerConfigPtr config)
{
	// Assign config to member variable
	this->_config = config;
}

nddlgen::controllers::IsdParser::~IsdParser()
{

}

nddlgen::types::IsdRoot nddlgen::controllers::IsdParser::parseIsd()
{
	// Assert that all preconditions are met. Throw exception if not
	this->checkAssertions();

	// Local variable initializations
	nddlgen::types::IsdRoot doc(new TiXmlDocument());

	// Try to read the file and parse ISD
	if (!doc->LoadFile(this->_config->getIsdInputFile()))
	{
		throw nddlgen::exceptions::ReadingIsdFileException();
	}

	// Return document
	return doc;
}

void nddlgen::controllers::IsdParser::checkAssertions()
{
	// Assert that an ISD input file has been set
	if (this->_config->getIsdInputFile() == "")
	{
		throw nddlgen::exceptions::IsdInputFileNotSetException();
	}

	// Assert that the ISD input file has a .isd extention
	if (this->_config->getIsdInputFileExt() != ".isd")
	{
		throw nddlgen::exceptions::FileMustBeIsdException();
	}

	// Assert that the ISD input file exists
	if (!boost::filesystem::exists(this->_config->getIsdInputFile()))
	{
		throw nddlgen::exceptions::FileDoesNotExistException(this->_config->getIsdInputFile());
	}
}
