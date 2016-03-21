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

#include <nddlgen/controllers/WorkflowController.h>

nddlgen::controllers::WorkflowController::WorkflowController(nddlgen::utilities::WorkflowControllerConfigPtr config)
{
	// Mark config object as read only and write to member
	config->setReadOnly();
	this->_config = config;

	// Workflow control flags
	this->_isSdfInputFileParsed = false;
	this->_isIsdInputFileParsed = false;
	this->_isDomainDescriptionBuilt = false;
	this->_isNddlModelFileWritten = false;
	this->_isNddlInitialStateFileWritten = false;
}

nddlgen::controllers::WorkflowController::~WorkflowController()
{

}

void nddlgen::controllers::WorkflowController::parseSdfInputFile()
{
	// Assert that the SDF input file has not been parsed yet
	if (this->_isSdfInputFileParsed)
	{
		throw nddlgen::exceptions::WorkflowException("SDF input file has already been parsed.");
	}

	// Instantiate SdfParser and pass WorkflowControllerConfig object
	nddlgen::controllers::SdfParserPtr parser(new nddlgen::controllers::SdfParser(this->_config));

	// Parse SDF and write root to member
	this->_sdfRoot = parser->parseSdf();

	// Set workflow control flag
	this->_isSdfInputFileParsed = true;
}

void nddlgen::controllers::WorkflowController::parseIsdInputFile()
{
	// Assert that the ISD input file has not been parsed yet
	if (this->_isIsdInputFileParsed)
	{
		throw nddlgen::exceptions::WorkflowException("ISD input file has already been parsed.");
	}

	// Instantiate IsdParser and pass WorkflowControllerConfig object
	nddlgen::controllers::IsdParserPtr parser(new nddlgen::controllers::IsdParser(this->_config));

	// Parse ISD and write root to member
	this->_isdRoot = parser->parseIsd();

	// Set workflow control flag
	this->_isIsdInputFileParsed = true;
}

void nddlgen::controllers::WorkflowController::buildDomainDescription()
{
	// Assert that at least the SDF input file has been parsed
	if (!this->_isSdfInputFileParsed)
	{
		throw nddlgen::exceptions::WorkflowException("Neither an SDF nor an ISD input file has been parsed.");
	}

	// Assert that domain description was not built yet
	if (this->_isDomainDescriptionBuilt)
	{
		throw nddlgen::exceptions::WorkflowException("Domain description already built.");
	}

	// Instantiate and initialize DomainDescriptionFactory
	nddlgen::controllers::DomainDescriptionFactoryPtr factory(new nddlgen::controllers::DomainDescriptionFactory());
	factory->setObjectFactory(this->_config->getObjectFactory());

	// Build the domain description model
	this->_domainDescription = factory->build(this->_sdfRoot, this->_isdRoot);

	// Set workflow control flag
	this->_isDomainDescriptionBuilt = true;
}

void nddlgen::controllers::WorkflowController::writeNddlModelFile()
{
	// Call overloaded function with forceOverwrite set to false
	this->writeNddlModelFile(false);
}

void nddlgen::controllers::WorkflowController::writeNddlModelFile(bool forceOverwrite)
{
	// Assert that the domain description was built
	if (!this->_isDomainDescriptionBuilt)
	{
		throw nddlgen::exceptions::WorkflowException("Domain description was not built.");
	}

	// Assert that the NDDL model output file was not written yet
	if (this->_isNddlModelFileWritten)
	{
		throw nddlgen::exceptions::WorkflowException("NDDL model output file was already written.");
	}

	// Write model file
	nddlgen::controllers::NddlGenerationController::writeModelFile(this->_domainDescription, this->_config, forceOverwrite);

	// Set workflow control flag
	this->_isNddlModelFileWritten = true;
}

void nddlgen::controllers::WorkflowController::writeNddlInitialStateFile()
{
	// Call overloaded function with forceOverwrite set to false
	this->writeNddlInitialStateFile(false);
}

void nddlgen::controllers::WorkflowController::writeNddlInitialStateFile(bool forceOverwrite)
{
	// Assert that an ISD input file has been set and parsed
	if (!this->_isIsdInputFileParsed)
	{
		throw nddlgen::exceptions::WorkflowException("An NDDL initial state file cannot be generated"
				" without an ISD input file being set and parsed.");
	}

	// Assert that the domain description was built
	if (!this->_isDomainDescriptionBuilt)
	{
		throw nddlgen::exceptions::WorkflowException("Domain description was not built.");
	}

	// Assert that the NDDL initial state output file was not written yet
	if (this->_isNddlInitialStateFileWritten)
	{
		throw nddlgen::exceptions::WorkflowException("NDDL initial state output file was already written.");
	}

	// Write initial state file
	nddlgen::controllers::NddlGenerationController::writeInitialStateFile(this->_domainDescription, this->_config, forceOverwrite);

	// Set workflow control flag
	this->_isNddlInitialStateFileWritten = true;
}
