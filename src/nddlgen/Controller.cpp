/**
 * Copyright 2015 Christian Dreher (christian.dreher@student.kit.edu)
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

#include <sys/stat.h>
#include <boost/filesystem.hpp>

#include "nddlgen/Controller.h"

namespace nddlgen
{

	const std::string Controller::ERR_FILE_ID_ALREADY_SET =
			"A file identifier has already been set. Create a new instance if necessary.";
	const std::string Controller::ERR_FILE_ALREADY_CHECKED =
			"The file has already been checked.";
	const std::string Controller::ERR_FILE_ALREADY_PARSED =
			"The file has already been parsed.";
	const std::string Controller::ERR_NDDL_ALREADY_GENERATED =
			"The NDDL-file has already been generated.";
	const std::string Controller::ERR_SET_FILE_ID_FIRST =
			"No file identifier has been set. Set one by calling Controller::setFileIdentifier(fileIdentifier).";
	const std::string Controller::ERR_CHECK_FILE_FIRST =
			"The file was not checked. Check it by calling Controller::checkFile().";
	const std::string Controller::ERR_PARSE_FILE_FIRST =
			"The file was not parsed. Parse it by calling Controller::parseFile().";
	const std::string Controller::ERR_FILE_MUST_BE_SDF =
			"File must be an .sdf file.";
	const std::string Controller::ERR_FILE_NOT_EXISTING =
			"File does not exist.";
	const std::string Controller::ERR_INITIALIZING_SDF =
			"Unable to initialize .sdf file.";
	const std::string Controller::ERR_READING_SDF_FILE =
			"Unable to read .sdf file.";


	Controller::Controller(std::string* errorText)
	{
		this->_cerrStdRdBuf = std::cerr.rdbuf();

		this->_errorText = errorText;

		this->_isFileIdentifierSet = false;
		this->_isFileChecked = false;
		this->_isSdfParsed = false;
		this->_isNddlGenerated = false;

		this->_armModel = new nddlgen::model::Arm();
	}

	Controller::Controller(std::string fileIdentifier, std::string* errorText)
	{
		this->_cerrStdRdBuf = std::cerr.rdbuf();

		this->_fileIdentifier = fileIdentifier;

		this->_errorText = errorText;

		this->_isFileIdentifierSet = true;
		this->_isFileChecked = false;
		this->_isSdfParsed = false;
		this->_isNddlGenerated = false;

		this->_armModel = new nddlgen::model::Arm();
	}

	Controller::~Controller()
	{
		delete this->_armModel;
	}


	bool Controller::setFileIdentifier(std::string fileIdentifier)
	{
		// Check if file identifier has already been set
		if (this->_isFileIdentifierSet)
		{
			*this->_errorText = Controller::ERR_FILE_ID_ALREADY_SET;
			return false;
		}

		this->_fileIdentifier = fileIdentifier;
		this->_isFileIdentifierSet = true;

		return true;
	}

	std::string Controller::getOutputFilesPath()
	{
		std::string filePath = boost::filesystem::path(this->_fileIdentifier).parent_path().string();
		return filePath;
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

	bool Controller::checkFile()
	{
		sdf::SDFPtr sdf(new sdf::SDF);

		// Check if file has already been checked
		if (this->_isFileChecked)
		{
			*this->_errorText = Controller::ERR_FILE_ALREADY_CHECKED;
			return false;
		}

		// Check if file is checkable
		if (!this->isCheckable())
		{
			return false;
		}

		// Check if file is a .sdf file
		if (boost::filesystem::path(this->_fileIdentifier).extension().string() != ".sdf")
		{
			*this->_errorText = Controller::ERR_FILE_MUST_BE_SDF;
			return false;
		}

		// Check if file exists
		if (!boost::filesystem::exists(this->_fileIdentifier))
		{
			*this->_errorText = Controller::ERR_FILE_NOT_EXISTING;
			return false;
		}

		this->disableCerr();

		// Init .sdf based on installed sdf_format.xml file
		if (!sdf::init(sdf))
		{
			this->enableCerr();
			*this->_errorText = Controller::ERR_INITIALIZING_SDF + "\n" + this->getBufferedCerrOutput();
			return false;
		}

		// Try to read the file and generate SDF
		if (!sdf::readFile(this->_fileIdentifier, sdf))
		{
			this->enableCerr();
			*this->_errorText = Controller::ERR_READING_SDF_FILE + "\n" + this->getBufferedCerrOutput();
			return false;
		}

		this->_sdfRoot = sdf->root;

		this->enableCerr();

		this->_isFileChecked = true;
		return true;
	}

	bool Controller::parseSdf()
	{
		// Initialize the parser with the already initialized Arm model
		nddlgen::core::SdfParser* sdfParser = new nddlgen::core::SdfParser(this->_armModel);

		// Check if file has already been parsed
		if (this->_isSdfParsed)
		{
			*this->_errorText = Controller::ERR_FILE_ALREADY_PARSED;
			return false;
		}

		// Check if file is parsable
		if (!this->isParsable())
		{
			return false;
		}

		// Parse the SDF into the defined data structure and check if it was successful
		if (!sdfParser->parseDataStructure(this->_sdfRoot))
		{
			*this->_errorText = "todo";
			return false;
		}

		delete sdfParser;

		this->_isSdfParsed = true;
		return true;
	}

	bool Controller::generateNddl()
	{
		// Initialize the NDDL generator with the already initialized and populated Arm model
		nddlgen::core::NddlGenerator* nddlGen = new nddlgen::core::NddlGenerator(this->_armModel);

		// Check if nddl has already been generated
		if (this->_isNddlGenerated)
		{
			*this->_errorText = Controller::ERR_NDDL_ALREADY_GENERATED;
			return false;
		}

		// Check if files are generatable
		if (!this->isGeneratable())
		{
			return false;
		}

		// Try to generate domain models and check if it was successful
		if (!nddlGen->generateModels())
		{
			*this->_errorText = "todo";
			return false;
		}

		// Try to create domain models output file and write generated domain models NDDL into it
		if (!nddlGen->writeModelsToFile())
		{
			*this->_errorText = "todo";
			return false;
		}

		// Try to generate domain initial state and check if it was successful
		if (!nddlGen->generateInitialState())
		{
			*this->_errorText = "todo";
			return false;
		}

		// Try to create domain initial state output file and  write generated domain initial state NDDL into it
		if (!nddlGen->writeInitialStateToFile())
		{
			*this->_errorText = "todo";
			return false;
		}

		delete nddlGen;

		this->_isNddlGenerated = true;
		return true;
	}


	bool Controller::isCheckable()
	{
		// Check if file identifier was set
		if (!this->_isFileIdentifierSet)
		{
			*this->_errorText = Controller::ERR_SET_FILE_ID_FIRST;
			return false;
		}

		return true;
	}

	bool Controller::isParsable()
	{
		// Check if file is checkable
		if (!this->isCheckable())
		{
			return false;
		}

		// Check if file was checked
		if (!this->_isFileChecked)
		{
			*this->_errorText = Controller::ERR_CHECK_FILE_FIRST;
			return false;
		}

		return true;
	}

	bool Controller::isGeneratable()
	{
		// Check if file is parsable
		if (!this->isParsable())
		{
			return false;
		}

		// Check if file was parsed
		if (!this->_isSdfParsed)
		{
			*this->_errorText = Controller::ERR_PARSE_FILE_FIRST;
			return false;
		}

		return true;
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
