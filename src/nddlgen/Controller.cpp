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

#include <nddlgen/Controller.h>

namespace nddlgen
{

	Controller::Controller()
	{
		// Save standard cerr buffer to be able to restore it
		this->_cerrStdRdBuf = std::cerr.rdbuf();

		// Initialize workflow indicators
		this->_isFileIdentifierSet = false;
		this->_isFileChecked = false;
		this->_isSdfParsed = false;
		this->_isNddlGenerated = false;

		// Instantiate controller meta data object
		this->_controllerMeta = new nddlgen::utilities::ControllerMeta();

		// Instantiate arm model
		this->_armModel = new nddlgen::models::Arm();
	}

	Controller::~Controller()
	{
		boost::checked_delete(this->_controllerMeta);
		boost::checked_delete(this->_armModel);

		// Check if SDF was parsed before calling member functions on SDF root
		if (this->_isSdfParsed)
		{
			this->_sdfRoot->ClearElements();
		}
	}


	void Controller::setFileIdentifier(std::string fileIdentifier)
	{
		// Check if file identifier has already been set
		if (this->_isFileIdentifierSet)
		{
			throw nddlgen::exceptions::FileIdAlreadySetException();
		}

		// Set file identifier and check workflow control variable
		this->_fileIdentifier = fileIdentifier;
		this->_isFileIdentifierSet = true;

		// Initialize controller meta data object
		this->_controllerMeta->inputFile = this->getInputFileName();
		this->_controllerMeta->inputFilePath = this->getInputFilePath();
		this->_controllerMeta->outputFilePath = this->getOutputFilesPath();
		this->_controllerMeta->outputFileModels = this->getModelsOutputFileName();
		this->_controllerMeta->outputFileInitialState = this->getInitialStateOutputFileName();
	}

	void Controller::checkFile()
	{
		sdf::SDFPtr sdf(new sdf::SDF);

		// Check if file has already been checked
		if (this->_isFileChecked)
		{
			throw nddlgen::exceptions::FileAlreadyCheckedException();
		}

		// Check if file is checkable
		this->isCheckable();

		// Check if file is an .sdf file
		if (boost::filesystem::path(this->_fileIdentifier).extension().string() != ".sdf")
		{
			throw nddlgen::exceptions::FileMustBeSdfException();
		}

		// Check if file exists
		if (!boost::filesystem::exists(this->_fileIdentifier))
		{
			throw nddlgen::exceptions::FileDoesNotExistException();
		}

		// Disable standard cerr output, since the output of the SDF library can't be suppressed otherwise
		this->disableCerr();

		// Init .sdf based on installed sdf_format.xml file
		if (!sdf::init(sdf))
		{
			// Re-enable standard cerr
			this->enableCerr();
			throw nddlgen::exceptions::InitializingSdfException(this->getBufferedCerrOutput());
		}

		// Try to read the file and generate SDF
		if (!sdf::readFile(this->_fileIdentifier, sdf))
		{
			// Re-enable cerr
			this->enableCerr();
			throw nddlgen::exceptions::ReadingSdfFileException(this->getBufferedCerrOutput());
		}

		// Save root to member
		this->_sdfRoot = sdf->root;

		// Re-enable cerr
		this->enableCerr();

		// Check workflow control variable
		this->_isFileChecked = true;
	}

	void Controller::parseSdf()
	{
		// Initialize the parser with the already initialized Arm model
		nddlgen::core::SdfParser* sdfParser = new nddlgen::core::SdfParser(this->_armModel);

		// Check if file has already been parsed
		if (this->_isSdfParsed)
		{
			throw nddlgen::exceptions::FileAlreadyParsedException();
		}

		// Check if file is parsable
		this->isParsable();

		// Parse the SDF into the defined data structure and check if it was successful
		if (!sdfParser->parseDataStructure(this->_sdfRoot))
		{
			throw nddlgen::exceptions::ParseDataStructureException();
		}

		// Delete SDF parser
		boost::checked_delete(sdfParser);

		// Check workflow control variable
		this->_isSdfParsed = true;
	}

	void Controller::generateNddl()
	{
		// Initialize the NDDL generator with the already initialized and populated Arm model
		nddlgen::core::NddlGenerator* nddlgen = new nddlgen::core::NddlGenerator(this->_armModel, this->_controllerMeta);

		// Check if NDDL has already been generated
		if (this->_isNddlGenerated)
		{
			throw nddlgen::exceptions::NddlAlreadyGeneratedException();
		}

		// Check if files are generatable
		this->isGeneratable();

		// Try to generate domain models, write it to a file and check if it was successful
		if (!nddlgen->generateModels(this->getOutputFilesPath() + "/" + this->getModelsOutputFileName()))
		{
			throw nddlgen::exceptions::GeneratingModelsException();
		}

		// Try to generate domain initial state and check if it was successful
		if (!nddlgen->generateInitialState(this->getOutputFilesPath() + "/" + this->getInitialStateOutputFileName()))
		{
			throw nddlgen::exceptions::GeneratingInitialStateException();
		}

		// Delete NDDL generator
		boost::checked_delete(nddlgen);

		// Check workflow control variable
		this->_isNddlGenerated = true;
	}


	void Controller::setAdapter(std::string adapter)
	{
		this->_controllerMeta->adapter = adapter;
	}

	void Controller::setOutputFilesPath(std::string outputFilesPath)
	{
		this->_outputFilesPath = outputFilesPath;
	}


	std::string Controller::getInputFilePath()
	{
		std::string filePath = boost::filesystem::path(this->_fileIdentifier).parent_path().string();
		return filePath;
	}

	std::string Controller::getInputFileName()
	{
		std::string fileName = boost::filesystem::path(this->_fileIdentifier).filename().string();
		return fileName;
	}

	std::string Controller::getOutputFilesPath()
	{
		// Standard output path is the path of the input file
		std::string outputFilesPath = this->getInputFilePath();

		// If a custom output path was set, override local variable
		if (this->_outputFilesPath != "")
		{
			outputFilesPath = this->_outputFilesPath;
		}

		return outputFilesPath;
	}

	std::string Controller::getModelsOutputFileName()
	{
		std::string fileStem = boost::filesystem::path(this->_fileIdentifier).stem().string();
		fileStem += "-model";

		return fileStem + ".nddl";
	}

	std::string Controller::getInitialStateOutputFileName()
	{
		std::string fileStem = boost::filesystem::path(this->_fileIdentifier).stem().string();
		fileStem += "-initial-state";

		return fileStem + ".nddl";
	}


	void Controller::isCheckable()
	{
		// Check if file identifier was set
		if (!this->_isFileIdentifierSet)
		{
			throw nddlgen::exceptions::SetFileIdFirstException();
		}
	}

	void Controller::isParsable()
	{
		// Check if file is checkable
		this->isCheckable();

		// Check if file was checked
		if (!this->_isFileChecked)
		{
			throw nddlgen::exceptions::CheckFileFirstException();
		}
	}

	void Controller::isGeneratable()
	{
		// Check if file is parsable
		this->isParsable();

		// Check if file was parsed
		if (!this->_isSdfParsed)
		{
			throw nddlgen::exceptions::ParseFileFirstException();
		}
	}


	void Controller::disableCerr()
	{
		std::cerr.rdbuf(this->_cerrOvRdBuf.rdbuf());
	}

	void Controller::enableCerr()
	{
		std::cerr.rdbuf(this->_cerrStdRdBuf);
	}

	std::string Controller::getBufferedCerrOutput()
	{
		return this->_cerrOvRdBuf.str();
	}

}
