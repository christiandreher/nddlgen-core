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

		// Initialize model workflow indicators
		this->_isSdfChecked = false;
		this->_isSdfParsed = false;
		this->_isNddlModelGenerated = false;

		// Initialize initial state workflow indicators
		this->_isIsdChecked = false;
		this->_isIsdParsed = false;
		this->_isNddlInitialStateGenerated = false;

		// Initialize as empty strings
		this->_inputSdfFile = "";
		this->_inputIsdFile = "";
		this->_outputFilesPath = "";

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


	void Controller::checkSdfInput()
	{
		sdf::SDFPtr sdf(new sdf::SDF);

		// Check if SDF has already been checked
		if (this->_isSdfChecked)
		{
			throw nddlgen::exceptions::SdfAlreadyCheckedException();
		}

		// Check if input SDF file has been set
		if (this->_inputSdfFile == "")
		{
			throw nddlgen::exceptions::InputSdfFileNotSetException();
		}

		// Check if input SDF file is an .sdf file
		if (boost::filesystem::path(this->_inputSdfFile).extension().string() != ".sdf")
		{
			throw nddlgen::exceptions::FileMustBeSdfException();
		}

		// Check if SDF file exists
		if (!boost::filesystem::exists(this->_inputSdfFile))
		{
			throw nddlgen::exceptions::FileDoesNotExistException(this->_inputSdfFile);
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
		if (!sdf::readFile(this->_inputSdfFile, sdf))
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
		this->_isSdfChecked = true;
	}

	void Controller::parseSdf()
	{
		// Check if file has already been parsed
		if (this->_isSdfParsed)
		{
			throw nddlgen::exceptions::SdfAlreadyParsedException();
		}

		// Check if file is parsable
		this->isSdfParsable();

		// Initialize the parser with the already initialized Arm model
		nddlgen::core::SdfParser* sdfParser = new nddlgen::core::SdfParser(this->_armModel);

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

	void Controller::generateNddlModel()
	{
		this->generateNddlModel(false);
	}

	void Controller::generateNddlModel(bool forceOverwrite)
	{
		// Check if NDDL has already been generated
		if (this->_isNddlModelGenerated)
		{
			throw nddlgen::exceptions::NddlModelAlreadyGeneratedException();
		}

		// Check if files are generatable
		this->isNddlModelGeneratable();

		std::string nddlOutputModelFile = this->getOutputFilesPath() + "/" + this->getModelsOutputFileName();

		// Check if file already exists
		if (!forceOverwrite && boost::filesystem::exists(nddlOutputModelFile))
		{
			throw nddlgen::exceptions::FileAlreadyExists(nddlOutputModelFile);
		}

		// Initialize the NDDL generator with the already initialized and populated Arm model
		nddlgen::core::NddlGenerator* nddlgen = new nddlgen::core::NddlGenerator(this->_armModel, this->_controllerMeta);

		// Try to generate domain models, write it to a file and check if it was successful
		if (!nddlgen->generateModels(nddlOutputModelFile))
		{
			throw nddlgen::exceptions::GeneratingModelsException();
		}

		// Delete NDDL generator
		boost::checked_delete(nddlgen);

		// Check workflow control variable
		this->_isNddlModelGenerated = true;
	}


	void Controller::checkIsdInput()
	{
		sdf::SDFPtr sdf(new sdf::SDF);

		// Check if ISD has already been checked
		if (this->_isIsdChecked)
		{
			throw nddlgen::exceptions::IsdAlreadyCheckedException();
		}

		// Check if input ISD file has been set
		if (this->_inputIsdFile == "")
		{
			throw nddlgen::exceptions::InputInitialStateFileNotSetException();
		}

		// Check if input ISD file is an .isd file
		if (boost::filesystem::path(this->_inputIsdFile).extension().string() != ".isd")
		{
			throw nddlgen::exceptions::FileMustBeIsdException();
		}

		// Check if file exists
		if (!boost::filesystem::exists(this->_inputIsdFile))
		{
			throw nddlgen::exceptions::FileDoesNotExistException(this->_inputIsdFile);
		}

		// todo: get contents from isd file with tinyxml

		// Check workflow control variable
		this->_isIsdChecked = true;
	}

	void Controller::parseIsd()
	{
		// Check if file has already been parsed
		if (this->_isIsdParsed)
		{
			throw nddlgen::exceptions::IsdAlreadyParsedException();
		}

		// Check if file is parsable
		this->isIsdParsable();

		// todo: parse xml from tinyxml

		// Check workflow control variable
		this->_isIsdParsed = true;
	}

	void Controller::generateNddlInitialState()
	{
		this->generateNddlInitialState(false);
	}

	void Controller::generateNddlInitialState(bool forceOverwrite)
	{
		// Check if NDDL has already been generated
		if (this->_isNddlInitialStateGenerated)
		{
			throw nddlgen::exceptions::NddlInitialStateAlreadyGeneratedException();
		}

		// Check if files are generatable
		this->isNddlInitialStateGeneratable();

		std::string nddlOutputInitialStateFile = this->getOutputFilesPath() + "/" + this->getInitialStateOutputFileName();

		// Check if file already exists
		if (!forceOverwrite && boost::filesystem::exists(nddlOutputInitialStateFile))
		{
			throw nddlgen::exceptions::FileAlreadyExists(nddlOutputInitialStateFile);
		}

		// Initialize the NDDL generator with the already initialized and populated Arm model
		nddlgen::core::NddlGenerator* nddlgen = new nddlgen::core::NddlGenerator(this->_armModel, this->_controllerMeta);

		// Try to generate domain initial state and check if it was successful
		if (!nddlgen->generateInitialState(nddlOutputInitialStateFile))
		{
			throw nddlgen::exceptions::GeneratingInitialStateException();
		}

		// Delete NDDL generator
		boost::checked_delete(nddlgen);

		// Check workflow control variable
		this->_isNddlInitialStateGenerated = true;
	}


	void Controller::setAdapter(std::string adapter)
	{
		this->_controllerMeta->adapter = adapter;
	}

	void Controller::setInputSdfFile(std::string inputSdfFile)
	{
		if (this->_inputSdfFile == "")
		{
			this->_inputSdfFile = inputSdfFile;
			this->_controllerMeta->inputSdfFileName = this->getInputSdfFileName();
			this->_controllerMeta->inputSdfFilePath = this->getInputSdfFilePath();
		}
		else
		{
			// todo: throw exception
		}
	}

	void Controller::setInputIsdFile(std::string inputIsdFile)
	{
		if (this->_inputIsdFile == "")
		{
			this->_inputIsdFile = inputIsdFile;
			this->_controllerMeta->inputIsdFileName = this->getInputIsdFileName();
			this->_controllerMeta->inputIsdFilePath = this->getInputIsdFilePath();
		}
		else
		{
			// todo: throw exception
		}
	}

	void Controller::setOutputFilesPath(std::string outputFilesPath)
	{
		if (this->_outputFilesPath == "")
		{
			this->_outputFilesPath = outputFilesPath;
			this->_controllerMeta->outputFilePath = this->getOutputFilesPath();
			this->_controllerMeta->outputFileModels = this->getModelsOutputFileName();
			this->_controllerMeta->outputFileInitialState = this->getInitialStateOutputFileName();
		}
		else
		{
			// todo: throw exception
		}
	}


	std::string Controller::getInputSdfFilePath()
	{
		std::string filePath = boost::filesystem::path(this->_inputSdfFile).parent_path().string();
		return filePath;
	}

	std::string Controller::getInputIsdFilePath()
	{
		std::string filePath = boost::filesystem::path(this->_inputIsdFile).parent_path().string();
		return filePath;
	}

	std::string Controller::getInputSdfFileName()
	{
		std::string fileName = boost::filesystem::path(this->_inputSdfFile).filename().string();
		return fileName;
	}

	std::string Controller::getInputIsdFileName()
	{
		std::string fileName = boost::filesystem::path(this->_inputIsdFile).filename().string();
		return fileName;
	}

	std::string Controller::getOutputFilesPath()
	{
		// Standard output path is the path of the input file
		std::string outputFilesPath = this->getInputSdfFilePath();

		// If a custom output path was set, override local variable
		if (this->_outputFilesPath != "")
		{
			outputFilesPath = this->_outputFilesPath;
		}

		return outputFilesPath;
	}

	std::string Controller::getModelsOutputFileName()
	{
		std::string fileStem = boost::filesystem::path(this->_inputSdfFile).stem().string();
		fileStem += "-model";

		return fileStem + ".nddl";
	}

	std::string Controller::getInitialStateOutputFileName()
	{
		std::string fileStem = boost::filesystem::path(this->_inputSdfFile).stem().string();
		fileStem += "-initial-state";

		return fileStem + ".nddl";
	}


	void Controller::isSdfParsable()
	{
		// Check if SDF file was checked
		if (!this->_isSdfChecked)
		{
			throw nddlgen::exceptions::CheckSdfFirstException();
		}
	}

	void Controller::isNddlModelGeneratable()
	{
		// Check if SDF is parsable
		this->isSdfParsable();

		// Check if SDF was parsed
		if (!this->_isSdfParsed)
		{
			throw nddlgen::exceptions::ParseSdfFirstException();
		}
	}


	void Controller::isIsdParsable()
	{
		// Check if ISD file was checked
		if (!this->_isIsdChecked)
		{
			throw nddlgen::exceptions::CheckIsdFirstException();
		}
	}

	void Controller::isNddlInitialStateGeneratable()
	{
		// Check if ISD is parsable
		this->isIsdParsable();

		// Check if ISD was parsed
		if (!this->_isIsdParsed)
		{
			throw nddlgen::exceptions::ParseIsdFirstException();
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
