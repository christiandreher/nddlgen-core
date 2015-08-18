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

#include <nddlgen/controller/WorkflowController.h>

namespace nddlgen { namespace controller
{

	WorkflowController::WorkflowController(nddlgen::utilities::WorkflowControllerConfig* config)
	{
		// Mark config object as read only and write to member
		config->setReadOnly();
		this->_config = config;

		// Save standard cerr buffer to be able to restore it when it must be changed
		this->_cerrStdRdBuf = std::cerr.rdbuf();

		// Workflow control flags
		this->_isSdfInputFileParsed = false;
		this->_isIsdInputFileParsed = false;
		this->_isDomainDescriptionBuilt = false;
		this->_isNddlModelFileWritten = false;
		this->_isNddlInitialStateFileWritten = false;

		// Domain description object will be initialized later
		this->_domainDescription = nullptr;

		// ISD root will be initialized later if an ISD file was set to be parsed
		this->_isdRoot = nullptr;
	}

	WorkflowController::~WorkflowController()
	{
		// Delete domain description object
		boost::checked_delete(this->_domainDescription);

		// Delete all instances of the SDF library if an SDF file was parsed
		if (this->_isSdfInputFileParsed)
		{
			this->_sdfRoot->ClearElements();
		}
	}


	void WorkflowController::parseSdfInputFile()
	{
		// Assert that all preconditions are met. Throw exception if not
		this->assertParseSdfInputFilePreconditions();

		// Local variable initializations
		sdf::SDFPtr sdf(new sdf::SDF);

		// Disable standard cerr output, since the output of the SDF library can't be suppressed otherwise
		this->disableCerr();

		// Init .sdf based on installed sdf_format.xml file
		if (!sdf::init(sdf))
		{
			// Re-enable standard cerr
			this->enableCerr();
			throw nddlgen::exceptions::InitializingSdfException(this->getBufferedCerrOutput());
		}

		// Try to read the file and parse SDF
		if (!sdf::readFile(this->_config->getSdfInputFile(), sdf))
		{
			// Re-enable cerr
			this->enableCerr();
			throw nddlgen::exceptions::ReadingSdfFileException(this->getBufferedCerrOutput());
		}

		// Write SDF document root to member
		this->_sdfRoot = sdf->root;

		// Re-enable cerr
		this->enableCerr();

		// Set workflow control flag
		this->_isSdfInputFileParsed = true;
	}

	void WorkflowController::parseIsdInputFile()
	{
		// Assert that all preconditions are met. Throw exception if not
		this->assertParseIsdInputFilePreconditions();

		// Parse ISD and write root to member
		this->_isdRoot = nddlgen::controller::IsdParser::parseIsd(this->_config->getIsdInputFile());

		// Set workflow control flag
		this->_isIsdInputFileParsed = true;
	}

	void WorkflowController::buildDomainDescription()
	{
		// Assert that all preconditions are met. Throw exception if not
		this->assertBuildDomainDescriptionPreconditions();

		// Build the domain description model
		this->_domainDescription = nddlgen::controller::DomainDescriptionFactory::build(this->_sdfRoot, this->_isdRoot);

		// Set workflow control flag
		this->_isDomainDescriptionBuilt = true;
	}

	void WorkflowController::writeNddlModelFile(bool forceOverwrite)
	{
		// Assert that all preconditions are met. Throw exception if not
		this->assertWriteNddlModelFilePreconditions(forceOverwrite);

		// Write model file
		nddlgen::controller::NddlGenerationController::writeModelFile(this->_domainDescription, this->_config);

		// Set workflow control flag
		this->_isNddlModelFileWritten = true;
	}

	void WorkflowController::writeNddlInitialStateFile(bool forceOverwrite)
	{
		// Assert that all preconditions are met. Throw exception if not
		this->assertWriteNddlInitialStateFilePreconditions(forceOverwrite);

		// Write initial state file
		nddlgen::controller::NddlGenerationController::writeInitialStateFile(this->_domainDescription, this->_config);

		// Set workflow control flag
		this->_isNddlInitialStateFileWritten = true;
	}

	void WorkflowController::writeNddlModelFile()
	{
		// Call overloaded function with forceOverwrite set to false
		this->writeNddlModelFile(false);
	}

	void WorkflowController::writeNddlInitialStateFile()
	{
		// Call overloaded function with forceOverwrite set to false
		this->writeNddlInitialStateFile(false);
	}


	void WorkflowController::assertParseSdfInputFilePreconditions()
	{
		// Assert that the SDF input file has not been parsed yet
		if (this->_isSdfInputFileParsed)
		{
			throw nddlgen::exceptions::WorkflowException("SDF input file has already been parsed.");
		}

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

	void WorkflowController::assertParseIsdInputFilePreconditions()
	{
		// Assert that the ISD input file has not been parsed yet
		if (this->_isIsdInputFileParsed)
		{
			throw nddlgen::exceptions::WorkflowException("ISD input file has already been parsed.");
		}

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

	void WorkflowController::assertBuildDomainDescriptionPreconditions()
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
	}

	void WorkflowController::assertWriteNddlModelFilePreconditions(bool forceOverwrite)
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

		// Assert that the file does not exist yet, unless an overwrite is forced
		if (!forceOverwrite && boost::filesystem::exists(this->_config->getOutputModelFile()))
		{
			throw nddlgen::exceptions::FileAlreadyExistsException(this->_config->getOutputModelFile());
		}
	}

	void WorkflowController::assertWriteNddlInitialStateFilePreconditions(bool forceOverwrite)
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

		// Assert that the file does not exist yet, unless an overwrite is forced
		if (!forceOverwrite && boost::filesystem::exists(this->_config->getOutputInitialStateFile()))
		{
			throw nddlgen::exceptions::FileAlreadyExistsException(this->_config->getOutputInitialStateFile());
		}
	}


	void WorkflowController::disableCerr()
	{
		// Disable std::cerr by setting custom read buffer
		std::cerr.rdbuf(this->_cerrOvRdBuf.rdbuf());
	}

	void WorkflowController::enableCerr()
	{
		// Re-enabling std::cerr by restoring initial value
		std::cerr.rdbuf(this->_cerrStdRdBuf);
	}

	std::string WorkflowController::getBufferedCerrOutput()
	{
		// Return contents of custom read buffer
		return this->_cerrOvRdBuf.str();
	}

}}
